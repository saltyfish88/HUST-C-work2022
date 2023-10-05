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
	printf("�ļ���ʧ�ܡ�");
	exit(-1);
}
if(!Token)
{
	printf("�ļ����ʧ�ܡ�");
	exit(-1);
}
wordscanner(Code,file);
fclose(Code);
present=next=file[0];
while(nextstep(file,i++,&present,&next)!=0)//����0���ļ�����������ѭ����
{
	if(present=='	'||present==' '){continue;}
	if(present=='\n')
	{
	    lin++;
		continue;
	}//����ո�ͻس���
	else if(present=='/')//���ע�͡�
	{
		if(next=='/')////��ע�͡�
		{
			while(next!='\n'){nextstep(file,i++,&present,&next);}
			nextstep(file,i++,&present,&next);
		}
		else if(next=='*')///*��ע�͡� 
		{
			while(1)
			{
				nextstep(file,i++,&present,&next);
				if(present=='*'&&next=='/')
				{
					nextstep(file,i++,&present,&next);
					exi=1;//ע�ͽ���������ѭ���� 
					break;
				}
			}
			if(exi==1)//ע�ͽ���������ѭ����
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
	else if(present=='#')//�жϺ� 
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
	else if(isalpha(present)!=0||present=='_')//�ж��Ƿ��Ǳ�ʶ���� 
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
		while(keywords[k]!=NULL)//�ж��Ƿ��ǹؼ��֡� 
		{
			k++;
			if(strcmp(keywords[k-1],tokenarray[j-1].value)==0)//�ǣ���type���ó���Ӧ�Ĺؼ��֡� 
			{
				if(k-1<=5){tokenarray[j-1].type=INT+k-1;}
				else{tokenarray[j-1].type=IF+k-7;}
				break;
			}
		}
		k=0;
		continue;
	}
	else if(isdigit(present)!=0)//�ж��Ƿ������ֳ����� 
	{
		tokenarray[j].type=NUM;
		tokenarray[j].loc=lin;
		j++;
		k=0;
		if(present!='0'||(present=='0'&&next=='.'))//�ж��Ƿ��Ƿ��Ƿ���ʮ�������ֳ����� 
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
		else if(next<='7'&&next>='0')//�ж��Ƿ��Ƿ��Ƿ���˽������ֳ�����
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
		else if(next=='b')//�ж��Ƿ��Ƿ��Ƿ�����������ֳ�����
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
		else if(next=='x')//�ж��Ƿ��Ƿ��Ƿ���ʮ���������ֳ�����
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
		else//�ж��Ƿ����㡣 
		{
		    tokenarray[j-1].value[0]='0';
		    tokenarray[j-1].value[1]='\0';
		    continue;
		} 
	}
	else if(present=='\'')//�ж��Ƿ����ַ������� 
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
	else if(present=='"')//�ж��Ƿ����ַ��������� 
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
	else//�жϷָ������������ 
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
