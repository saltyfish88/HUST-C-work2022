#include"lexer_def.h"
int main()
{int i=0,j=0,k=0,exi=0;
char present='0';
char next='0';
char file[MAXLEN];
Token tokenarray[MAXLEN];
FILE*Token=fopen("temp_token.txt","w");
FILE*Code=fopen("../input.txt","r");
if(!Code)
{
	printf("文件打开失败。");
	exit(-1);
}
if(!Token)
{
	printf("文件输出失败。");
	exit(-1);
}
wordscanner(Code,file);
fclose(Code);
present=next=file[0];
while(nextstep(file,i++,&present,&next)!=0)//等于0则文件结束，跳出循环。
{
	if(present=='	'||present==' '){continue;}
	if(present=='\n')
	{
	    lin++;
		continue;
	}//清除空格和回车。
	else if(present=='/')//清除注释。
	{
		if(next=='/')////型注释。
		{
			while(next!='\n'){nextstep(file,i++,&present,&next);}
			nextstep(file,i++,&present,&next);
		}
		else if(next=='*')///*型注释。 
		{
			while(1)
			{
				nextstep(file,i++,&present,&next);
				if(present=='*'&&next=='/')
				{
					nextstep(file,i++,&present,&next);
					exi=1;//注释结束，跳出循环。 
					break;
				}
			}
			if(exi==1)//注释结束，跳出循环。
			{
				exi=0;
				continue;
			}
		}
		else
		{
			tokenarray[j].type=DIV;
			tokenarray[j].loc=lin;
			j++;
		} 
	}
	else if(present=='#')//判断宏 
	{
		tokenarray[j].type=MAC;
		tokenarray[j].loc=lin;
		j++;
		k=0;
		while((present=='\\'&&next=='\n')||next!='\n')
		{
			tokenarray[j-1].value[k]=present;
			k++;
			nextstep(file,i++,&present,&next);
		}
		tokenarray[j-1].value[k]=present;
		k++;
		tokenarray[j-1].value[k]='\0';
		k=0;
	}
	else if(isalpha(present)!=0||present=='_')//判断是否是标识符。 
	{
		k=0;
		tokenarray[j].type=ID;
		tokenarray[j].loc=lin;
		j++;
		while(isalnum(next)!=0||next=='_')
		{
			tokenarray[j-1].value[k]=present;
			k++;
			nextstep(file,i++,&present,&next);
		}
		tokenarray[j-1].value[k]=present;
		k++;
		tokenarray[j-1].value[k]='\0';
		k=0;
		while(keywords[k]!=NULL)//判断是否是关键字。 
		{
			k++;
			if(strcmp(keywords[k-1],tokenarray[j-1].value)==0)//是，把type设置成相应的关键字。 
			{
				if(k-1<=5){tokenarray[j-1].type=INT+k-1;}
				else{tokenarray[j-1].type=IF+k-7;}
				break;
			}
		}
		k=0;
		continue;
	}
	else if(isdigit(present)!=0)//判断是否是数字常量。 
	{
		tokenarray[j].type=NUM;
		tokenarray[j].loc=lin;
		j++;
		k=0;
		if(present!='0'||(present=='0'&&next=='.'))//判断是否是否是非零十进制数字常量。 
		{
			while(isdigit(next)!=0||next=='.')
			{
				tokenarray[j-1].value[k++]=present;
				nextstep(file,i++,&present,&next);
			}
			tokenarray[j-1].value[k]=present;
			k++;
			tokenarray[j-1].value[k]='\0';
			continue;
		}
		else if(next<='7'&&next>='0')//判断是否是否是非零八进制数字常量。
		{
			nextstep(file,i++,&present,&next);
			while((next<='7'&&next>='0')||next=='.')
			{
				tokenarray[j-1].value[k]=present;
				k++;
				nextstep(file,i++,&present,&next);
			}
			tokenarray[j-1].value[k]=present;
			k++;
			tokenarray[j-1].value[k]='\0';
			continue;
		}
		else if(next=='b')//判断是否是否是非零二进制数字常量。
		{
			nextstep(file,i++,&present,&next);
			if(next!='0'&&next!='1')
			{
				tokenarray[j-1].type=ERR;
			    lexerr(NUM_BIN_TYPE);
			    continue;
			}
			nextstep(file,i++,&present,&next);
			while(next=='0'||next=='1'||next=='.')
			{
				tokenarray[j-1].value[k++]=present;
				nextstep(file,i++,&present,&next);
			}
			tokenarray[j-1].value[k++]=present;
			tokenarray[j-1].value[k]='\0';
			continue;
		}
		else if(next=='x')//判断是否是否是非零十六进制数字常量。
		{
			nextstep(file,i++,&present,&next);
			if(!((next<='F'&&next>='A')||(next>='a'&&next<='f')||isdigit(next)!=0))
			{
				tokenarray[j-1].type=ERR;
			    lexerr(NUM_HEX_TYPE);
			    continue;
			}
			nextstep(file,i++,&present,&next);
			while((next<='F'&&next>='A')||(next>='a'&&next<='f')||isdigit(next)!=0||next=='.')
			{
				tokenarray[j-1].value[k++]=present;
				nextstep(file,i++,&present,&next);
			}
			tokenarray[j-1].value[k++]=present;
			tokenarray[j-1].value[k]='\0';
			continue;
		}
		else//判断是否是零。 
		{
		    tokenarray[j-1].value[0]='0';
		    tokenarray[j-1].value[1]='\0';
		    continue;
		} 
	}
	else if(present=='\'')//判断是否是字符常量。 
	{
		tokenarray[j].type=CH;
		tokenarray[j].loc=lin;
		j++;
		if(next=='\'')
		{
			tokenarray[j-1].type=ERR;
			lexerr(CHAR_NO_DATA);
			continue;
		}
		else
		{
			tokenarray[j-1].value[0]=next;
			tokenarray[j-1].value[1]='\0';
			nextstep(file,i++,&present,&next);
			nextstep(file,i++,&present,&next);
			if(present!='\'')
			{
				tokenarray[j-1].type=ERR;
			    lexerr(CHAR_NO_R_QUTION);
			    while(present!='\''||present!=' '||present!='\n'){nextstep(file,i++,&present,&next);}
			}
			continue;
		}
	}
	else if(present=='"')//判断是否是字符串常量。 
	{
		tokenarray[j].type=STR;
		tokenarray[j].loc=lin;
		j++;
		nextstep(file,i++,&present,&next);
		k=0;
		while(present!='"')
		{
			tokenarray[j-1].value[k++]=present;
			nextstep(file,i++,&present,&next);
			if(present=='\n')
			{
				tokenarray[j-1].type=ERR;
				lexerr(STR_NO_R_QUTION);
				break;
			}
		}
		tokenarray[j-1].value[k]='\0';
		continue;
	}
	else//判断分隔符和运算符。 
	{
		switch(present)
		{
			case '+':
				tokenarray[j].type=ADD;
				tokenarray[j].loc=lin;
				j++;
				if(next=='+')
				{
					tokenarray[j-1].type=INC;
					nextstep(file,i++,&present,&next);
				}
				break;
			case '-':
				tokenarray[j].type=SUB;
				tokenarray[j].loc=lin;
				j++;
				if(next=='-')
				{
					tokenarray[j-1].type=DEC;
					nextstep(file,i++,&present,&next);
				}
				break;
			case '*':
				tokenarray[j].type=MUL;
				tokenarray[j].loc=lin;
				j++;
				break;
			case '/':
				tokenarray[j].type=DIV;
				tokenarray[j].loc=lin;
				j++;
				break;
			case '%':
				tokenarray[j].type=MOD;
				tokenarray[j].loc=lin;
				j++;
				break;
			case '>':
				tokenarray[j].type=GT;
				tokenarray[j].loc=lin;
				j++;
				if(next=='=')
				{
					tokenarray[j-1].type=GE;
					nextstep(file,i++,&present,&next);
				}
				break;
			case '<':
				tokenarray[j].type=LT;
				tokenarray[j].loc=lin;
				j++;
				if(next=='-')
				{
					tokenarray[j-1].type=LE;
					nextstep(file,i++,&present,&next);
				}
				break;
			case '=':
				tokenarray[j].type=ASSIGN;
				tokenarray[j].loc=lin;
				j++;
				if(next=='=')
				{
					tokenarray[j-1].type=EQU;
					nextstep(file,i++,&present,&next);
				}
				break;
			case '&':
				tokenarray[j].type=LEA;
				tokenarray[j].loc=lin;
				j++;
				if(next=='&')
				{
					tokenarray[j-1].type=AND;
					nextstep(file,i++,&present,&next);
				}
				break;
			case '|':
				if(next=='|')
				{
					tokenarray[j].type=OR;
					tokenarray[j].loc=lin;
					j++;
					nextstep(file,i++,&present,&next);
				}
				else
				{
					tokenarray[j++].type=ERR;
					lexerr(OR_NO_PAIR);
				}
				break;
			case '!':
				tokenarray[j].type=NOT;
				tokenarray[j].loc=lin;
				j++;
				if(next=='=')
				{
					tokenarray[j-1].type=NEQU;
					nextstep(file,i++,&present,&next);
				}
				break;
			case ',':
				tokenarray[j].type=COMMA;
				tokenarray[j].loc=lin;
				j++;
				break;
			case ':':
				tokenarray[j].type=COLON;
				tokenarray[j].loc=lin;
				j++;
				break;
			case ';':
				tokenarray[j].type=SEMICON;
				tokenarray[j].loc=lin;
				j++;
				break;
			case '(':
				tokenarray[j].type=LPAREN;
				tokenarray[j].loc=lin;
				j++;
				break;
			case ')':
				tokenarray[j].type=RPAREN;
				tokenarray[j].loc=lin;
				j++;
				break;
			case '[':
				tokenarray[j].type=LBRACK;
				tokenarray[j].loc=lin;
				j++;
				break;
			case ']':
				tokenarray[j].type=RBRACK;
				tokenarray[j].loc=lin;
				j++;
				break;
			case '{':
				tokenarray[j].type=LBRACE;
				tokenarray[j].loc=lin;
				j++;
				break;
			case '}':
				tokenarray[j].type=RBRACE;
				tokenarray[j].loc=lin;
				j++;
				break;
			default:
				tokenarray[j++].type=ERR;
				lexerr(TOKEN_NO_EXIST);
				break;
		}
	}
}
tokenarray[j].type=END;
tokenarray[j].loc=lin;
token_print_to_stdout(tokenarray);
token_print_to_file(Token,tokenarray);
fclose(Token);
return 0; 
}
