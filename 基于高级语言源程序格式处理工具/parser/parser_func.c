#ifndef __PARSER_FUNC__
#define __PARSER_FUNC__
//***********控制函数************// 
/**
 * 函数名称: readtokenarray
 * 函数功能：从文件中读取词法记号数组的内容，并将其存储在全局的tokenarray数组中
 * 函数输入: fp - 文件指针，指向包含词法记号的输入文件
 * 函数输出：无
 */
void readtokenarray(FILE*fp)
{
	int i=0;
	do
	{
		fscanf(fp,"%d",&tokenarray[i].type);
		if(tokenarray[i].type==ID||tokenarray[i].type==NUM||tokenarray[i].type==CH
		||tokenarray[i].type==STR||tokenarray[i].type==MAC)
		{
		    fgetc(fp);//去除\n字符。 
		    fgets(tokenarray[i].value,MAXLEN_OF_CONTENT,fp);
		    tokenarray[i].value[strlen(tokenarray[i].value)-1]='\0';//删除末尾的空格。 
		}
		fscanf(fp,"%d",&tokenarray[i].loc);
		i++;
	}while(tokenarray[i-1].type!=END);
}
/**
 * 函数名称: gonext
 * 函数功能：将全局变量noft指向的tokenarray中的词法记号信息更新到全局变量nexttype和loc中
 * 函数输入: 无
 * 函数输出：无
 */
void gonext()
{
	nexttype=tokenarray[noft].type;
	loc=tokenarray[noft].loc;
	noft++;
}
/**
 * 函数名称: in
 * 函数功能：维护AST的层数，增加layer和cnt计数
 * 函数输入: 无
 * 函数输出：无
 */
void in()
{
	layer++;
	cnt++;
}//维护AST的层数。 

/**
 * 函数名称: out
 * 函数功能：减少AST的层数，将layer计数减少
 * 函数输入: 无
 * 函数输出：无
 */
void out(){
	layer--;
}
/**
 * 函数名称: block_in
 * 函数功能：维护当前所处块的层数，增加blocknum计数
 * 函数输入: 无
 * 函数输出：无
 */
void block_in(){
	blocknum++;
}//维护所处块的层数。
/**
 * 函数名称: block_out
 * 函数功能：减少当前所处块的层数，将blocknum计数减少
 * 函数输入: 无
 * 函数输出：无
 */
void block_out(){
	blocknum--;
} 
/**
 * 函数名称: print_blank
 * 函数功能：根据当前AST的层数，打印相应数量的空格到标准输出
 * 函数输入: 无
 * 函数输出：无
 */
void print_blank()//打印AST中的空格。 
{
	int i=0;
	for(i=0;i<layer;i++){printf("  ");}
}
/**
 * 函数名称: fprint_token
 * 函数功能：根据当前词法记号的类型，将其格式化输出到指定文件
 * 函数输入: fp - 文件指针，指向输出文件
 * 函数输出：无
 */
void fprint_token(FILE*fp)
{
	int i=0;
	switch(tokenarray[noft-1].type)
	{
		case ID:
			fprintf(fp,"%s ",tokenarray[noft-1].value);
			break;
		case INT:
			fprintf(fp,"int ");
			break;
		case CHAR:
			fprintf(fp,"char ");
			break;
		case FLOAT:
			fprintf(fp,"float ");
			break;
		case DOUBLE:
			fprintf(fp,"double ");
			break;
		case VOID:
			fprintf(fp,"void ");
			break;
		case EXTERN:
			fprintf(fp,"extern ");
			break;
		case NUM:
			fprintf(fp,"%s ",tokenarray[noft-1].value);
			break;
		case CH:
			fprintf(fp,"\'%s\' ",tokenarray[noft-1].value);
			break;
		case STR:
			fprintf(fp,"\"%s\" ",tokenarray[noft-1].value);
			break;
		case NOT:
			fprintf(fp,"! ");
			break;
		case LEA:
			fprintf(fp,"& ");
			break;
		case ADD:
			fprintf(fp,"+ ");
			break;
		case SUB:
			fprintf(fp,"- ");
			break;
		case MUL:
			fprintf(fp,"* ");
			break;
		case DIV:
			fprintf(fp,"/ ");
			break;
		case MOD:
			fprintf(fp,"%% ");
			break;
		case INC:
			fprintf(fp,"++ ");
			break;
		case DEC:
			fprintf(fp,"-- ");
			break;
		case GT:
			fprintf(fp,"> ");
			break;
		case GE:
			fprintf(fp,">= ");
			break;
		case LT:
			fprintf(fp,"< ");
			break;
		case LE:
			fprintf(fp,"<= ");
			break;
		case EQU:
			fprintf(fp,"== ");
			break;
		case NEQU:
			fprintf(fp,"!= ");
			break;
		case AND:
			fprintf(fp,"&& ");
			break;
		case OR:
			fprintf(fp,"|| ");
			break;
		case LPAREN:
			fprintf(fp,"( ");
			break;
		case RPAREN:
			fprintf(fp,") ");
			if(tokenarray[noft].type!=RBRACE&&tokenarray[noft].type!=SEMICON&&tokenarray[noft].type!=ADD&&tokenarray[noft].type!=SUB&&tokenarray[noft].type!=MUL&&tokenarray[noft].type!=MOD&&tokenarray[noft].type!=DIV)
			{
				fprintf(fp,"\n");
				for(i=0;i<1+blocknum;i++){fprintf(fp,"	");}
			}
			break;
		case LBRACK:
			fprintf(fp,"[ ");
			break;
		case RBRACK:
			fprintf(fp,"] ");
			break;
		case LBRACE:
			fprintf(fp,"\n");
			for(i=0;i<blocknum-1;i++){fprintf(fp,"	");}
			fprintf(fp,"{\n");
			for(i=0;i<blocknum;i++){fprintf(fp,"	");}
			break;
		case RBRACE:
			for(i=0;i<blocknum-1;i++){fprintf(fp,"	");}
			fprintf(fp,"}\n");
			if(tokenarray[noft].type!=RBRACE){for(i=0;i<blocknum-1;i++){fprintf(fp,"	");}}
			break;
		case COMMA:
			fprintf(fp,", ");
			break;
		case COLON:
			fprintf(fp,":\n");
			for(i=0;i<blocknum;i++){fprintf(fp,"	");}
			fprintf(fp,"  ");
			break;
		case SEMICON:
			fprintf(fp,";");
			if(isinfor!=1)
			{
				fprintf(fp,"\n");
				if(if2nd==1)
				{
					if(tokenarray[noft].type!=RBRACE){for(i=0;i<blocknum-1;i++){fprintf(fp,"	");}}
					if2nd=0;
				}
				else
				{
					if(tokenarray[noft].type!=RBRACE){for(i=0;i<blocknum;i++){fprintf(fp,"	");}}
				}
			}
			else{fprintf(fp," ");}
			break;
		case ASSIGN:
			fprintf(fp,"= ");
			break;
		case IF:
			fprintf(fp,"if ");
			break;
		case ELSE:
			fprintf(fp,"else ");
			if(tokenarray[noft].type!=RBRACE)
			{
				fprintf(fp,"\n");
				for(i=0;i<1+blocknum;i++){fprintf(fp,"	");}
			}
			break;
		case SWITCH:
			fprintf(fp,"switch ");
			break;
		case CASE:
			fprintf(fp,"case ");
			break;
		case DEFAULT:
			fprintf(fp,"default ");
			break;
		case WHILE:
			fprintf(fp,"while ");
			break;
		case DO:
			fprintf(fp,"do ");
			break;
		case FOR:
			fprintf(fp,"for ");
			break;
		case BREAK:
			fprintf(fp,"break ");
			break;
		case CONTINUE:
			fprintf(fp,"continue ");
			break;
		case RETURN:
			fprintf(fp,"return ");
			break;
		case MAC:
			fprintf(fp,"%s\n ",tokenarray[noft-1].value);
			for(i=0;i<blocknum;i++){fprintf(fp,"	");}
			break;
		default:
			printf("无法识别的词法记号！\n");
	}
}

//***********绘制AST的函数************//
void init_ast()
{
	graph=fopen("AST.dot","w");
	fprintf(graph,"digraph AST {\n");
	fprintf(graph,"node [shape=ellipse, fontname=\"KaiTi\"];\n");
	fprintf(graph,"{\n");
}
void end_ast()
{
	fprintf(graph,"}\n");
	fprintf(graph,"}\n");
	fclose(graph);
}
void print_ast(int from,const char*from_name,int to,const char*to_name,int is_terminal)
{
	if(setted[from]==0)//未设置
	{
		setted[from]=1;
		if(is_terminal==1)//是终结符
		{
			fprintf(graph,"%d[label=\"%s\",shape=box];\n",from,from_name);
		}
		else
		{
			fprintf(graph,"%d[label=\"%s\"];\n",from,from_name);
		}
	}
	if(setted[to]==0)
	{
		setted[to]=1;
		if(is_terminal==1)
		{
			fprintf(graph,"%d[label=\"%s\",shape=box];\n",to,to_name);
		}
		else
		{
			fprintf(graph,"%d[label=\"%s\"];\n",to,to_name);
		}
	}
	fprintf(graph,"%d->%d;\n",from,to);
}

//**********变量声明函数***********// 
/**
 * 函数名称: program
 * 函数功能：解析源代码的程序结构，递归地解析segment和program
 * 函数输入: 无
 * 函数输出：无
 */
void program()
{
	int from=cnt;
	if(nexttype==END)
	{
		return;
	}
	cnt++;
	print_ast(from,"program",cnt,"segment",0);
	segment();
	cnt++;
	print_ast(from,"program",cnt,"program",0);
	program();	
}
/**
 * 函数名称: segment
 * 函数功能：解析变量声明或宏定义的片段
 * 函数输入: 无
 * 函数输出：无
 */
void segment()
{
	int from=cnt;
	if(nexttype==MAC)
	{
		cnt++;
		print_ast(from,"segment",cnt,tokenarray[noft-1].value,1);
		fprint_token(output);
		printf("宏：%s\n",tokenarray[noft-1].value);
		gonext();
	}
	else if(nexttype==EXTERN)
	{
		cnt++;
		print_ast(from,"segment",cnt,"extern",1);
		fprint_token(output);
		printf("外部变量:\n");
		gonext();
	}
	else
	{
		printf("变量声明：\n");
		in();
		print_ast(from,"segment",cnt,"type",0);
		type();
		out();
		in();
		print_ast(from,"segment",cnt,"def",0);
		def();
		out();
	}
}
/**
 * 函数名称: type
 * 函数功能：解析变量类型
 * 函数输入: 无
 * 函数输出：无
 */
void type()
{
	int from=cnt;
	print_blank();
	switch(nexttype)
	{
		case INT:
			cnt++;
			print_ast(from,"type",cnt,"int",1);
			fprint_token(output);
			printf("类型：int\n");
			gonext();
			break;
		case CHAR:
			cnt++;
			print_ast(from,"type",cnt,"char",1);
			fprint_token(output);
			printf("类型：char\n");
			gonext();
			break;
		case FLOAT:
			cnt++;
			print_ast(from,"type",cnt,"float",1);
			fprint_token(output);
			printf("类型：float\n");
			gonext();
			break;
		case DOUBLE:
			cnt++;
			print_ast(from,"type",cnt,"double",1);
			fprint_token(output);
			printf("类型：double\n");
			gonext();
			break;
		case VOID:
			cnt++;
			print_ast(from,"type",cnt,"void",1);
			fprint_token(output);
			printf("类型：void\n");
			gonext();
			break;
		default:
			synerr(nexttype,3,INT,CHAR,FLOAT,DOUBLE,VOID);
			break;
	}
}
/**
 * 函数名称: def
 * 函数功能：解析变量定义
 * 函数输入: 无
 * 函数输出：无
 */
void def()
{
	int from=cnt;
	if(nexttype==MUL)
	{
		cnt++;
		print_ast(from,"def",cnt,"*",1);
		fprint_token(output);
		print_blank();
		printf("指针\n");
		gonext();
		if(nexttype==ID)
		{
			cnt++;
			print_ast(from,"def",cnt,tokenarray[noft-1].value,1);
			fprint_token(output);
			print_blank();
			printf("名称：%s\n",tokenarray[noft-1].value);
			gonext();
			in();
			print_ast(from,"def",cnt,"init",0);
			init();
			out();
			in();
			print_ast(from,"def",cnt,"deflist",0);
			deflist();
			out();
		}
		else
		{
			synerr(nexttype,1,ID);
		}
	}
	else if(nexttype==ID)
	{
		cnt++;
		print_ast(from,"def",cnt,tokenarray[noft-1].value,1);
		fprint_token(output);
		print_blank();
		printf("名称：%s\n",tokenarray[noft-1].value);
		gonext();
		in();
		print_ast(from,"def",cnt,"idtail",0);
		idtail();
		out();
	}
	else
	{
		synerr(nexttype,1,ID);
	}
}
/**
 * 函数名称: init
 * 函数功能：解析变量初始化
 * 函数输入: 无
 * 函数输出：无
 */
void init()
{
	int from=cnt;
	if(nexttype==ASSIGN)
	{
		cnt++;
		print_ast(from,"init",cnt,"=",1);
		fprint_token(output);
		print_blank();
		printf("赋值\n"); 
		gonext();
		in();
		print_ast(from,"init",cnt,"expr",0);
		expr();
		out();
	}
}
/**
 * 函数名称: deflist
 * 函数功能：解析变量定义列表
 * 函数输入: 无
 * 函数输出：无
 */
void deflist()
{
	int from=cnt;
	if(nexttype==COMMA)
	{
		cnt++;
		print_ast(from,"deflist",cnt,",",1);
		fprint_token(output);
		gonext();
		in();
		print_ast(from,"deflist",cnt,"defdata",0);
		defdata();
		out();
		in();
		print_ast(from,"deflist",cnt,"deflist",0);
		deflist();
		out();
	}
	else if(nexttype==SEMICON)
	{
		cnt++;
		print_ast(from,"deflist",cnt,";",1);
		fprint_token(output);
		gonext();
	}
	else
	{
		synerr(nexttype,2,COMMA,SEMICON);
	}
}
/**
 * 函数名称: idtail
 * 函数功能：解析标识符的后续部分，可能是函数参数列表或变量定义列表
 * 函数输入: 无
 * 函数输出：无
 */
void idtail()
{
	int from=cnt;
	if(nexttype==LPAREN)
	{
		cnt++;
		print_ast(from,"idtail",cnt,"(",1);
		fprint_token(output);
		gonext();
		in();
		print_ast(from,"idtail",cnt,"para",0);
		para();
		out();
		if(nexttype==RPAREN)
		{
			cnt++;
			print_ast(from,"idtail",cnt,")",1);
			fprint_token(output);
			gonext();
			in();
			print_ast(from,"idtail",cnt,"funtail",0);
			funtail();
			out();
		}
		else
		{
			synerr(nexttype,1,RPAREN);
		}
	}
	else
	{
		in();
		print_ast(from,"idtail",cnt,"varrdef",0);
		varrdef();
		out();
		in();
		print_ast(from,"idtail",cnt,"deflist",0);
		deflist();
		out();
	}
} 
/**
 * 函数名称: defdata
 * 函数功能：解析变量定义数据
 * 函数输入: 无
 * 函数输出：无
 */
void defdata()
{
	int from=cnt;
	if(nexttype==MUL)
	{
		cnt++;
		print_ast(from,"defdata",cnt,"*",1);
		fprint_token(output);
		print_blank();
		printf("指针\n");
		gonext();
		if(nexttype==ID)
		{
			cnt++;
			print_ast(from,"defdata",cnt,tokenarray[noft-1].value,1);
			fprint_token(output);
			print_blank();
			printf("名称：%s\n",tokenarray[noft-1].value);
			gonext();
			in();
			print_ast(from,"defdata",cnt,"init",0);
			init();
			out();
		}
		else
		{
			synerr(nexttype,1,ID);
		}
	}
	else if(nexttype==ID)
	{
		cnt++;
		print_ast(from,"defdata",cnt,tokenarray[noft-1].value,1);
		fprint_token(output);
		print_blank();
		printf("名称：%s\n",tokenarray[noft-1].value);
		gonext();
		in();
		print_ast(from,"defdata",cnt,"varrdef",0);
		varrdef();
		out();
	}
	else
	{
		synerr(nexttype,2,ID,MUL);
	}
}
/**
 * 函数名称: varrdef
 * 函数功能：解析变量的数组定义
 * 函数输入: 无
 * 函数输出：无
 */
void varrdef()
{
	int from=cnt;
	if(nexttype==LBRACK)
	{
		cnt++;
		print_ast(from,"varrdef",cnt,"[",1);
		fprint_token(output);
		gonext();
		if(nexttype==NUM)
		{
			cnt++;
			print_ast(from,"varrdef",cnt,tokenarray[noft-1].value,1);
			fprint_token(output);
			print_blank();
			printf("数组下标：%s\n",tokenarray[noft-1].value); 
			gonext();
			if(nexttype==RBRACK)
			{
				cnt++;
				print_ast(from,"varrdef",cnt,"]",1);
				fprint_token(output);
				gonext();
			}
			else
			{
				synerr(nexttype,1,RBRACK);
			}
		}
		else
		{
			synerr(nexttype,1,NUM);
		}
	}
	else
	{
		in();
		print_ast(from,"varrdef",cnt,"init",0);
		init();
		out();
	}
}

//*********函数声明函数*********//

void funtail()
{
	int from=cnt;
	if(nexttype==SEMICON)
	{
		cnt++;
		print_ast(from,"funtail",cnt,";",1);
		fprint_token(output);
		gonext();
	}
	else
	{
		print_blank();
		printf("作用域内容：\n"); 
		block_in();
		in();
		print_ast(from,"funtail",cnt,"block",0);
		block();
		out();
		block_out();
	}
}

void para()
{
	int from=cnt;
	print_blank();
	printf("函数形参：\n"); 
	if(nexttype==INT||nexttype==DOUBLE||nexttype==FLOAT||nexttype==VOID||nexttype==CHAR)
	{
		in();
		print_ast(from,"para",cnt,"type",0);
		type();
		out();
		in();
		print_ast(from,"para",cnt,"paradata",0);
		paradata();
		out();
		in();
		print_ast(from,"para",cnt,"paralist",0);
		paralist();
		out();
	}
}

void paradata()
{
	int from=cnt;
	if(nexttype==MUL)
	{
		cnt++;
		print_ast(from,"paradata",cnt,"*",1);
		fprint_token(output);
		print_blank();
		printf("指针\n");
		gonext();
		if(nexttype==ID)
		{
			cnt++;
			print_ast(from,"paradata",cnt,tokenarray[noft-1].value,1);
			fprint_token(output);
			print_blank();
			printf("名称：%s\n",tokenarray[noft-1].value);
			gonext();
		}
		else
		{
			synerr(nexttype,1,ID);
		}
	}
	else if(nexttype==ID)
	{
		cnt++;
		print_ast(from,"paradata",cnt,tokenarray[noft-1].value,1);
		fprint_token(output);
		print_blank();
		printf("名称：%s\n",tokenarray[noft-1].value);
		gonext();
		in();
		paradatatail();
		out();
	}
	else
	{
		synerr(nexttype,2,ID,MUL);
	}
}

void paralist()
{
	int from=cnt;
	if(nexttype==COMMA)
	{
		cnt++;
		print_ast(from,"paralist",cnt,",",1);
		fprint_token(output);
		gonext();
		in();
		print_ast(from,"paralist",cnt,"type",0);
		type();
		out();
		in();
		print_ast(from,"paralist",cnt,"paradata",0);
		paradata();
		out();
		in();
		print_ast(from,"paralist",cnt,"paralist",0);
		paralist();
		out();
	}
}

void paradatatail()
{
	int from=cnt;
	if(nexttype==LBRACK)
	{
		cnt++;
		print_ast(from,"paradatatail",cnt,"[",1);
		fprint_token(output);
		gonext();
		if(nexttype==NUM)
		{
			cnt++;
			print_ast(from,"paradatatail",cnt,tokenarray[noft-1].value,1);
			fprint_token(output);
			print_blank();
			printf("数组下标：%s\n",tokenarray[noft-1].value);
			gonext();
			if(nexttype==RBRACK)
			{
				cnt++;
				print_ast(from,"paradatatail",cnt,"]",1);
				fprint_token(output);
				gonext();
			}
			else
			{
				synerr(nexttype,1,RBRACK);
			}
		}
		else
		{
			synerr(nexttype,1,NUM);
		}
	}
}

//*************函数定义函数************//
void block()
{
	int from=cnt;
	if(nexttype==LBRACE)
	{
		cnt++;
		print_ast(from,"block",cnt,"{",1);
		fprint_token(output);
		gonext();
		in();
		print_ast(from,"block",cnt,"subprogram",0);
		subprogram();
		out();
		if(nexttype==RBRACE)
		{
			cnt++;
			print_ast(from,"block",cnt,"}",1);
			fprint_token(output);
			gonext();
		}
		else
		{
			synerr(nexttype,1,RBRACE);
		}
	}
	else
	{
		synerr(nexttype,1,LBRACE);
	}
} 
void subprogram()
{
	int from=cnt;
	if(nexttype==INT||nexttype==DOUBLE||nexttype==FLOAT||nexttype==CHAR||nexttype==VOID)//进入变量声明。 
	{
		in();
		cnt++;
		print_ast(from,"subprogram",cnt,"localdef",0);
		localdef();
		out();
		in();
		print_ast(from,"subprogram",cnt,"subprogram",0);
		subprogram();
		out();
	}
	else if(nexttype==ID||nexttype==MUL||(nexttype<=RETURN&&nexttype>=IF&&nexttype!=CASE&&nexttype!=DEFAULT))//进入语句。
	{
		in();
		print_ast(from,"subprogram",cnt,"statement",0);
		statement();
		out();
		in();
		print_ast(from,"subprogram",cnt,"subprogram",0);
		subprogram();
		out();
	}
}
void localdef()
{
	int from=cnt;
	print_blank();
	printf("自动变量：\n"); 
	in();
	print_ast(from,"localdef",cnt,"type",0);
	type();
	out();
	in();
	print_ast(from,"localdef",cnt,"defdata",0);
	defdata();
	out();
	in();
	print_ast(from,"localdef",cnt,"deflist",0);
	deflist();
	out();
}
//************语句函数**************//
void statement()
{
	int from=cnt;
	switch(nexttype)
	{
		case WHILE:
			cnt++;
			print_ast(from,"statement",cnt,"while",1);
			fprint_token(output);
			print_blank();
			printf("while语句:\n");
			gonext();
			in();
			print_ast(from,"statement",cnt,"whilestat",0);
			whilestat();
			out();
			break;
		case FOR:
			cnt++;
			print_ast(from,"statement",cnt,"for",1);
			fprint_token(output);
			print_blank();
			printf("for语句:\n");
			gonext();
			in();
			print_ast(from,"statement",cnt,"forstat",0);
			forstat();
			out();
			break;
		case DO:
			cnt++;
			print_ast(from,"statement",cnt,"do",1);
			fprint_token(output);
			print_blank();
			printf("do-while语句:\n");
			gonext();
			in();
			print_ast(from,"statement",cnt,"dowhilestat",0);
			dowhilestat();
			out();
			break;
		case IF:
			cnt++;
			print_ast(from,"statement",cnt,"if",1);
			fprint_token(output);
			print_blank();
			printf("if语句:\n");
			gonext();
			in();
			print_ast(from,"statement",cnt,"ifstat",0);
			ifstat();
			out();
			break;
		case SWITCH:
			cnt++;
			print_ast(from,"statement",cnt,"switch",1);
			fprint_token(output);
			print_blank();
			printf("switch语句:\n");
			gonext();
			in();
			print_ast(from,"statement",cnt,"switchstat",0);
			switchstat();
			out();
			break;
		case BREAK:
			cnt++;
			print_ast(from,"statement",cnt,"break",1);
			fprint_token(output);
			print_blank();
			printf("break语句:\n");
			gonext();
			if(nexttype==SEMICON)
			{
				cnt++;
				print_ast(from,"statement",cnt,";",1);
				fprint_token(output);
				gonext();
			}
			else
			{
				synerr(nexttype,1,SEMICON);
			}
			break;
		case CONTINUE:
			cnt++;
			print_ast(from,"statement",cnt,"continue",1);
			fprint_token(output);
			print_blank();
			printf("continue语句:\n");
			gonext();
			if(nexttype==SEMICON)
			{
				cnt++;
				print_ast(from,"statement",cnt,";",1);
				fprint_token(output);
				gonext();
			}
			else
			{
				synerr(nexttype,1,SEMICON);
			}
			break;
		case RETURN:
			cnt++;
			print_ast(from,"statement",cnt,"return",1);
			fprint_token(output);
			print_blank();
			printf("return语句:\n");
			gonext();
			in();
			print_ast(from,"statement",cnt,"altexpr",0);
			altexpr();
			out();
			if(nexttype==SEMICON)
			{
				cnt++;
				print_ast(from,"statement",cnt,";",1);
				fprint_token(output);
				gonext();
			}
			else
			{
				synerr(nexttype,1,SEMICON);
			}
			break;
		default:
			{
				in();
				print_ast(from,"statement",cnt,"altexpr",0);
				altexpr();
				out();
				if(nexttype==SEMICON)
				{
					cnt++;
					print_ast(from,"statement",cnt,";",1);
					fprint_token(output);
					gonext();
				}
				else
				{
					synerr(nexttype,1,SEMICON);
				}
			}
	}
} 

void whilestat()
{
	int from=cnt;
	if(nexttype==LPAREN)
	{
		cnt++;
		print_ast(from,"whilestat",cnt,"(",1);
		fprint_token(output);
		print_blank();
		printf("循环条件：\n");
		gonext();
		in();
		print_ast(from,"whilestat",cnt,"altexpr",0);
		altexpr();
		out();
		if(nexttype==RPAREN)
		{
			cnt++;
			print_ast(from,"whilestat",cnt,")",1);
			fprint_token(output);
			gonext();
			block_in();
			in();
			print_ast(from,"whilestat",cnt,"block",0);
			block();
			out();
			block_out();
		}
		else
		{
			synerr(nexttype,1,RPAREN);
		}
	}
	else
	{
		synerr(nexttype,1,LPAREN);
	}
}
void forstat()
{
	int from=cnt;
	print_blank();
	printf("复合语句：\n");
	if(nexttype==LPAREN)
	{
		cnt++;
		print_ast(from,"forstat",cnt,"(",1);
		isinfor=1;
		fprint_token(output);
		gonext();
		in();
		print_ast(from,"forstat",cnt,"forinit",0);
		forinit();
		out();
		in();
		print_ast(from,"forstat",cnt,"altexpr",0);
		altexpr();
		out();
		if(nexttype==SEMICON)
		{
			cnt++;
			print_ast(from,"forstat",cnt,";",1);
			fprint_token(output);
			gonext();
			in();
			print_ast(from,"forstat",cnt,"altexpr",0);
			altexpr();
			out();
			if(nexttype==RPAREN)
			{
				cnt++;
				print_ast(from,"forstat",cnt,")",1);
				isinfor=0;
				fprint_token(output);
				gonext();
				block_in();
				in();
				print_ast(from,"forstat",cnt,"block",0);
				block();
				out();
				block_out();
			}
			else
			{
				synerr(nexttype,1,RPAREN);
			}
		}
		else
		{
			synerr(nexttype,1,SEMICON);
		}
	}
	else
	{
		synerr(nexttype,1,LPAREN);
	}
}
void forinit()
{
	int from=cnt;
	if(nexttype==INT||nexttype==FLOAT||nexttype==DOUBLE||nexttype==CHAR||nexttype==VOID)
	{
		in();
		print_ast(from,"forinit",cnt,"type",0);
		type();//应该有一个type(); 
		out();
		in();
		print_ast(from,"forinit",cnt,"def",0);
		def();
		out();
	}
	else
	{
		in();
		print_ast(from,"forinit",cnt,"altexpr",0);
		altexpr();
		out();
		if(nexttype==SEMICON)
		{
			cnt++;
			print_ast(from,"forinit",cnt,";",1);
			fprint_token(output);
			gonext();
		}
		else
		{
			synerr(nexttype,1,SEMICON);
		}
	}
}
void dowhilestat()
{
	int from=cnt;
	block_in();
	in();
	print_ast(from,"dowhilestat",cnt,"block",0);
	block();
	out();
	block_out();
	if(nexttype==WHILE)
	{
		cnt++;
		print_ast(from,"dowhilestat",cnt,"while",1);
		fprint_token(output);
		gonext();
		print_blank();
		printf("循环条件：\n"); 
		if(nexttype==LPAREN)
		{
			cnt++;
			print_ast(from,"dowhilestat",cnt,"(",1);
			fprint_token(output);
			gonext();
			in();
			print_ast(from,"dowhilestat",cnt,"altexpr",0);
			altexpr();
			out();
			if(nexttype==RPAREN)
			{
				cnt++;
				print_ast(from,"dowhilestat",cnt,")",1);
				fprint_token(output);
				gonext();
				if(nexttype==SEMICON)
				{
					cnt++;
					print_ast(from,"dowhilestat",cnt,";",1);
					fprint_token(output);
					gonext();
				}
				else
				{
					synerr(nexttype,1,SEMICON);
				}
			}
			else
			{
				synerr(nexttype,1,RPAREN);
			}
		}
		else
		{
			synerr(nexttype,1,LPAREN);
		}
	}
	else
	{
		synerr(nexttype,1,WHILE);
	}
}
void ifstat()
{
	int from=cnt;
	if(nexttype==LPAREN)
	{
		cnt++;
		print_ast(from,"ifstat",cnt,"(",1);
		fprint_token(output);
		print_blank();
		printf("条件：\n");
		gonext();
		in();
		print_ast(from,"ifstat",cnt,"expr",0);
		expr();
		out();
		if(nexttype==RPAREN)
		{
			cnt++;
			print_ast(from,"ifstat",cnt,")",1);
			fprint_token(output);
			gonext();
			block_in();
			if(nexttype==LBRACE)
			{
				in();
				print_ast(from,"ifstat",cnt,"block",0);
				block();
				out();	
			}
			else//if的第二种形式 
			{
				in();
				if2nd=1;
				print_ast(from,"ifstat",cnt,"statement",0);
				statement();
				out();
			}
			block_out();
			in();
			print_ast(from,"ifstat",cnt,"elsestat",0);
			elsestat();
			out();
		}
		else
		{
			synerr(nexttype,1,RPAREN);
		}
	}
	else
	{
		synerr(nexttype,1,LPAREN);
	}
}
void elsestat()
{
	int from=cnt;
	print_blank();
	printf("else语句：\n");
	if(nexttype==ELSE)
	{
		cnt++;
		print_ast(from,"elsestat",cnt,"else",1);
		fprint_token(output);
		gonext();
		if(nexttype==IF)//else if
		{
			cnt++;
			print_ast(from,"elsestat",cnt,"if",1);
			fprint_token(output);
			gonext();
			in();
			print_ast(from,"elsestat",cnt,"ifstat",0);
			ifstat();
			out();
		}
		else
		{
			block_in();
			if(nexttype==LBRACE)
			{
				in();
				print_ast(from,"elsestat",cnt,"block",0);
				block();
				out();	
			}
			else//if的第二种形式 
			{
				in();
				if2nd=1;
				print_ast(from,"elsestat",cnt,"statement",0);
				statement();
				out();
			}
			block_out();
		}

	}
}
void switchstat()
{
	int from=cnt;
	if(nexttype==LPAREN)
	{
		cnt++;
		print_ast(from,"switchstat",cnt,"(",1);
		fprint_token(output);
		print_blank();
		printf("switch变量：\n"); 
		gonext();
		in();
		print_ast(from,"switchstat",cnt,"expr",0);
		expr();
		out();
		if(nexttype==RPAREN)
		{
			cnt++;
			print_ast(from,"switchstat",cnt,")",1);
			fprint_token(output);
			gonext();
			block_in();
			if(nexttype==LBRACE)
			{
				cnt++;
				print_ast(from,"switchstat",cnt,"{",1);
				fprint_token(output);
				gonext();
				in();
				print_ast(from,"switchstat",cnt,"casestat",0);
				casestat();
				out();
				if(nexttype==RBRACE)
				{
					cnt++;
					print_ast(from,"switchstat",cnt,"}",1);
					fprint_token(output);
					gonext();
				}
				else
				{
					synerr(nexttype,1,RBRACE);
				}
				block_out();
			}
			else
			{
				synerr(nexttype,1,LBRACE);
			}
		}
		else
		{
			synerr(nexttype,1,RPAREN);
		}
	}
	else
	{
		synerr(nexttype,1,LPAREN);
	}
}
void casestat()
{
	int from=cnt;
	if(nexttype==CASE)
	{
		cnt++;
		print_ast(from,"casestat",cnt,"case",1);
		fprint_token(output);
		print_blank();
		printf("case语句：\n"); 
		gonext();
		print_blank();
		printf("编号：\n");
		in();
		print_ast(from,"casestat",cnt,"literal",0);
		literal();
		out();
		if(nexttype==COLON)
		{
			cnt++;
			print_ast(from,"casestat",cnt,":",1);
			fprint_token(output);
			gonext();
			in();
			print_ast(from,"casestat",cnt,"subprogram",0);
			subprogram();
			out();
			in();
			print_ast(from,"casestat",cnt,"casestat",0);
			casestat();
			out();
		}
		else
		{
			synerr(nexttype,1,COLON);
		}
	}
	else if(nexttype==DEFAULT)
	{
		cnt++;
		print_ast(from,"casestat",cnt,"default",1);
		fprint_token(output);
		print_blank();
		printf("default语句：\n");
		gonext();
		if(nexttype==COLON)
		{
			cnt++;
			print_ast(from,"casestat",cnt,":",1);
			fprint_token(output);
			gonext();
			in();
			print_ast(from,"casestat",cnt,"subprogram",0);
			subprogram();
			out();
		}
		else
		{
			synerr(nexttype,1,COLON);
		}
	}
	else if(nexttype==RBRACE){return;}//case的结束条件 
	else
	{
		synerr(nexttype,2,DEFAULT,CASE);
	}
}
//**********表达式函数*********//
void altexpr()
{
	int from=cnt;
	if(nexttype>=LPAREN&&nexttype==SEMICON)
	{
		return;
	}
	else
	{
		in();
		print_ast(from,"altexpr",cnt,"expr",0);
		expr();
		out();
	}
}
void expr()
{
	int from=cnt;
	print_blank();
	printf("表达式：\n");
	in();
	print_ast(from,"expr",cnt,"assexpr",0);
	assexpr();
	out();
}
void assexpr()
{
	int from=cnt;
	in();
	print_ast(from,"assexpr",cnt,"orexpr",0);
	orexpr();
	out();
	in();
	print_ast(from,"assexpr",cnt,"asstail",0);
	asstail();
	out();
}
void asstail()
{
	int from=cnt;
	if(nexttype==ASSIGN)
	{
		cnt++;
		print_ast(from,"asstail",cnt,"=",1);
		fprint_token(output);
		print_blank();
		printf("赋值\n"); 
		gonext();
		in();
		print_ast(from,"asstail",cnt,"orexpr",0);
		orexpr();
		out();
		in();
		print_ast(from,"asstail",cnt,"asstail",0);
		asstail();
		out();
	}
}
void orexpr()
{
	int from=cnt;
	in();
	print_ast(from,"orexpr",cnt,"andexpr",0);
	andexpr();
	out();
	in();
	print_ast(from,"orexpr",cnt,"ortail",0);
	ortail();
	out();
}
void ortail()
{
	int from=cnt;
	if(nexttype==OR)
	{
		cnt++;
		print_ast(from,"ortail",cnt,"||",1);
		fprint_token(output);
		print_blank();
		printf("逻辑或\n"); 
		gonext();
		in();
		print_ast(from,"ortail",cnt,"andexpr",0);
		andexpr();
		out();
		in();
		print_ast(from,"ortail",cnt,"ortail",0);
		ortail();
		out();
	}
}
void andexpr()
{
	int from=cnt;
	in();
	print_ast(from,"andexpr",cnt,"cmpexpr",0);
	cmpexpr();
	out();
	in();
	print_ast(from,"andexpr",cnt,"andtail",0);
	andtail();
	out();
}
void andtail()
{
	int from=cnt;
	if(nexttype==AND)
	{
		cnt++;
		print_ast(from,"andtail",cnt,"&&",1);
		fprint_token(output);
		print_blank();
		printf("逻辑与\n");
		gonext();
		in();
		print_ast(from,"andtail",cnt,"cmpexpr",0);
		cmpexpr();
		out();
		in();
		print_ast(from,"andtail",cnt,"andtail",0);
		andtail();
		out();
	}
}
void cmpexpr()
{
	int from=cnt;
	in();
	print_ast(from,"cmpexpr",cnt,"aloexpr",0);
	aloexpr();
	out();
	in();
	print_ast(from,"cmpexpr",cnt,"cmptail",0);
	cmptail();
	out();
}
void cmptail()
{
	int from=cnt;
	if(nexttype<=NEQU&&nexttype>=GT)
	{
		fprint_token(output);
		print_blank();
		if(nexttype==GT)
		{
			cnt++;
			print_ast(from,"cmptail",cnt,">",1);
			printf("大于\n");
		}
		else if(nexttype==GE)
		{
			cnt++;
			print_ast(from,"cmptail",cnt,">=",1);
			printf("大于等于\n");

		}
		else if(nexttype==LT)
		{
			cnt++;
			print_ast(from,"cmptail",cnt,"<",1);
			printf("小于\n");
		}
		else if(nexttype==LE)
		{
			cnt++;
			print_ast(from,"cmptail",cnt,"<=",1);
			printf("小于等于\n");
		}
		else if(nexttype==EQU)
		{
			cnt++;
			print_ast(from,"cmptail",cnt,"==",1);
			printf("等于\n");
		}
		else if(nexttype==NEQU)
		{
			cnt++;
			print_ast(from,"cmptail",cnt,"!=",1);
			printf("不等于\n");
		}
		gonext();
		in();
		print_ast(from,"cmptail",cnt,"aloexpr",0);
		aloexpr();
		out();
		in();
		print_ast(from,"cmptail",cnt,"cmptail",0);
		cmptail();
		out();
	}
}
void aloexpr()
{
	int from=cnt;
	in();
	print_ast(from,"aloexpr",cnt,"item",0);
	item();
	out();
	in();
	print_ast(from,"aloexpr",cnt,"alotail",0);
	alotail();
	out();
}
void alotail()
{
	int from=cnt;
	if(nexttype==SUB||nexttype==ADD)
	{
		fprint_token(output);
		print_blank();
		if(nexttype==SUB)
		{
			cnt++;
			print_ast(from,"alotail",cnt,"+",1);
			printf("加\n");
		}
		else if(nexttype==ADD)
		{
			cnt++;
			print_ast(from,"alotail",cnt,"-",1);
			printf("减\n");
		}
		gonext();
		in();
		print_ast(from,"alotail",cnt,"item",0);
		item();
		out();
		in();
		print_ast(from,"alotail",cnt,"alotail",0);
		alotail();
		out();
	}
}
void item()
{
	int from=cnt;
	in();
	print_ast(from,"item",cnt,"factor",0);
	factor();
	out();
	in();
	print_ast(from,"item",cnt,"itemtail",0);
	itemtail();
	out();
}
void itemtail()
{
	int from=cnt;
	if(nexttype==MUL||nexttype==MOD||nexttype==DIV)
	{
		fprint_token(output);
		print_blank();
		if(nexttype==MUL)
		{
			cnt++;
			print_ast(from,"itemtail",cnt,"*",1);
			printf("乘\n");
		}
		else if(nexttype==MOD)
		{
			cnt++;
			print_ast(from,"itemtail",cnt,"%",1);
			printf("取余\n");
		}
		else if(nexttype==DIV)
		{
			cnt++;
			print_ast(from,"itemtail",cnt,"/",1);
			printf("除以\n");
		}
		gonext();
		in();
		print_ast(from,"itemtail",cnt,"factor",0);
		factor();
		out();
		in();
		print_ast(from,"itemtail",cnt,"itemtail",0);
		itemtail();
		out();
	}
}
void factor()
{
	int from=cnt;
	if(nexttype==NOT||nexttype==LEA||nexttype==MUL||nexttype==SUB||nexttype==INC||nexttype==DEC)
	{
		fprint_token(output);
		print_blank();
		if(nexttype==NOT)
		{
			cnt++;
			print_ast(from,"factor",cnt,"!",1);
			printf("逻辑非\n");
		}
		else if(nexttype==LEA)
		{
			cnt++;
			print_ast(from,"factor",cnt,"&",1);
			printf("取地址\n");
		}
		else if(nexttype==MUL)
		{
			cnt++;
			print_ast(from,"factor",cnt,"*",1);
			printf("调用指针\n");
		}
		else if(nexttype==SUB)
		{
			cnt++;
			print_ast(from,"factor",cnt,"-",1);
			printf("负号\n");
		}
		else if(nexttype==INC)
		{
			cnt++;
			print_ast(from,"factor",cnt,"++",1);
			printf("自增\n");
		}
		else if(nexttype==DEC)
		{
			cnt++;
			print_ast(from,"factor",cnt,"--",1);
			printf("自减\n");
		}
		gonext();
		in();
		print_ast(from,"factor",cnt,"factor",0);
		factor();
		out();
	}
	else
	{
		in();
		print_ast(from,"factor",cnt,"val",0);
		val();
		out();
	}
}
void val()
{
	int from=cnt;
	in();
	print_ast(from,"val",cnt,"elem",0);
	elem();
	out();
	if(nexttype==INC||nexttype==DEC)
	{
		fprint_token(output);
		print_blank();
		if(nexttype==INC)
		{
			cnt++;
			print_ast(from,"val",cnt,"++",1);
			printf("自增\n");
		}
		else if(nexttype==DEC)
		{
			cnt++;
			print_ast(from,"val",cnt,"--",1);
			printf("自减\n");
		}
		gonext();
	}
	/*else
	{
		synerr();
	}*/
}
void elem()
{
	int from=cnt;
	if(nexttype==ID)
	{
		cnt++;
		print_ast(from,"elem",cnt,tokenarray[noft-1].value,1);
		fprint_token(output);
		print_blank();
		printf("名称：%s\n",tokenarray[noft-1].value);
		gonext();
		in();
		print_ast(from,"elem",cnt,"idexpr",0);
		idexpr();
		out();
	}
	else if(nexttype==LPAREN)
	{
		cnt++;
		print_ast(from,"elem",cnt,"(",1);
		fprint_token(output);
		gonext();
		in();
		expr();
		out();
		if(nexttype==RPAREN)
		{
			cnt++;
			print_ast(from,"elem",cnt,")",1);
			fprint_token(output);
			gonext();
		}
		else
		{
			synerr(nexttype,1,RPAREN);
		}
	}
	else
	{
		in();
		print_ast(from,"elem",cnt,"literal",0);
		literal();
		out();
	}
}
void idexpr()
{
	int from=cnt;
	if(nexttype==LBRACK)
	{
		cnt++;
		print_ast(from,"idexpr",cnt,"[",1);
		fprint_token(output);
		gonext();
		in();
		expr();
		out();
		if(nexttype==RBRACK)
		{
			cnt++;
			print_ast(from,"idexpr",cnt,"]",1);
			fprint_token(output);
			gonext();
		}
		else
		{
			synerr(nexttype,1,RBRACK);
		}
	}
	else if(nexttype==LPAREN)
	{
		cnt++;
		print_ast(from,"idexpr",cnt,"(",1);
		fprint_token(output);
		print_blank();
		printf("函数调用的参数：\n"); 
		gonext();
		in();
		print_ast(from,"idexpr",cnt,"realarg",0);
		realarg();
		out();
		if(nexttype==RPAREN)
		{
			cnt++;
			print_ast(from,"idexpr",cnt,")",1);
			fprint_token(output);
			gonext();
		}
		else
		{
			synerr(nexttype,1,RPAREN);
		}
	}
}
void realarg()
{
	int from=cnt;
	//if(nexttype>=LPAREN&&nexttype==SEMICON)
	if(nexttype==ID||nexttype==NUM||nexttype==STR||nexttype==CH)
	{
		in();
		print_ast(from,"realarg",cnt,"expr",0);
	    expr();
	    out();
	    in();
		print_ast(from,"realarg",cnt,"arglist",0);
	    arglist();	
	    out();
	}
}
void arglist()
{
	int from=cnt;
	if(nexttype==COMMA)
	{
		cnt++;
		print_ast(from,"arglist",cnt,",",1);
		fprint_token(output);
		gonext();
		in();
		print_ast(from,"arglist",cnt,"expr",0);
		expr();
		out();
		in();
		print_ast(from,"arglist",cnt,"arglist",0);
		arglist();
		out();
	}
}
void literal()
{
	int from=cnt;
	fprint_token(output);
	switch(nexttype)
	{
		case NUM:
			cnt++;
			print_ast(from,"literal",cnt,tokenarray[noft-1].value,1);
			print_blank();
			printf("数值常量：%s\n",tokenarray[noft-1].value);
			gonext();
			break;
		case STR:
			cnt++;
			print_ast(from,"literal",cnt,tokenarray[noft-1].value,1);
			print_blank();
			printf("字符串常量：%s\n",tokenarray[noft-1].value);
			gonext();
			break;
		case CHAR:
			cnt++;
			print_ast(from,"literal",cnt,tokenarray[noft-1].value,1);
			print_blank();
			printf("字符常量：%s\n",tokenarray[noft-1].value);
			gonext();
			break;
	}
}
//*************错误处理函数***********//
void synerr(int type,int num,...)
{
	int i=0,expect=0,sign=WRONG;//期望出现的词法符号。 
	va_list p;
	va_start(p,num);
	iserr=1;
	switch(type)
	{
		case ID:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect<=VOID&&expect>=INT)//所有可以出现在ID前面的词法符号。
				{
					printerr(TYPELOST);
					sign=LOST; 
					break;
				}
				else if(expect==ASSIGN)
				{
					printerr(ASSIGNLOST);
					sign=LOST;
					break;
				}
				else if(expect==LPAREN)
				{
					printerr(LPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==RPAREN)
				{
					printerr(RPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACK)
				{
					printerr(LBRACKLOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACK)
				{
					printerr(RBRACKLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACE)
				{
					printerr(LBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACE)
				{
					printerr(RBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==COMMA)
				{
					printerr(COMMALOST);
					sign=LOST;
					break;
				}
				else if(expect==COLON)
				{
					printerr(COLONLOST);
					sign=LOST;
					break;
				}
				else if(expect==SEMICON)
				{
					printerr(SEMICONLOST);
					sign=LOST;
					break;
				} 
			}
			if(sign==WRONG)
			{
				printerr(IDWRONG);
			}
			break;
		case INT:
		case FLOAT:
		case DOUBLE:
		case CHAR:
		case VOID:
		case EXTERN:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==LPAREN)
				{
					printerr(LPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==RPAREN)
				{
					printerr(RPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACK)
				{
					printerr(LBRACKLOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACK)
				{
					printerr(RBRACKLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACE)
				{
					printerr(LBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACE)
				{
					printerr(RBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==COLON)
				{
					printerr(COLONLOST);
					sign=LOST;
					break;
				}
				else if(expect==SEMICON)
				{
					printerr(SEMICONLOST);
					sign=LOST;
					break;
				}
			}
			if(sign==WRONG)
			{
				printerr(TYPEWRONG);
			}
			break;
		case NUM:
		case CH:
		case STR:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==ASSIGN)
				{
					printerr(ASSIGNLOST);
					sign=LOST;
					break;
				}
				else if(expect==LPAREN)
				{
					printerr(LPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACK)
				{
					printerr(LBRACKLOST);
					sign=LOST;
					break;
				}
			}
			if(sign==WRONG)
			{
				printerr(LITERALWRONG);
			}
			break;
		case ADD:
		case SUB:
		case DIV:
		case MOD:
		case GT:
		case GE:
		case LT:
		case LE:
		case EQU:
		case NEQU:
		case AND:
		case OR:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==NUM||expect==CH||expect==STR)
				{
					printerr(LITERALLOST);
					sign=LOST;
					break;
				}
				else if(expect==ID)
				{
					printerr(IDLOST);
					sign=LOST;
					break;
				}
			}
			break;
		case NOT:
		case LEA:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==ASSIGN)
				{
					printerr(ASSIGNLOST);
					sign=LOST;
					break;
				}
				else if(expect==LPAREN)
				{
					printerr(LPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==COMMA)
				{
					printerr(COMMALOST);
					sign=LOST;
					break;
				}
				else if(expect==COLON)
				{
					printerr(COLONLOST);
					sign=LOST;
					break;
				}
				else if(expect==SEMICON)
				{
					printerr(SEMICONLOST);
					sign=LOST;
					break;
				} 
			}
			break;
		case MUL:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==NUM||expect==CH||expect==STR)
				{
					printerr(LITERALLOST);
					sign=LOST;
					break;
				}
				else if(expect==ID)
				{
					printerr(IDLOST);
					sign=LOST;
					break;
				}
				if(expect<=VOID&&expect>=INT)
				{
					printerr(TYPELOST);
					sign=LOST; 
					break;
				}
				else if(expect==ASSIGN)
				{
					printerr(ASSIGNLOST);
					sign=LOST;
					break;
				}
				else if(expect==LPAREN)
				{
					printerr(LPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==RPAREN)
				{
					printerr(RPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACK)
				{
					printerr(LBRACKLOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACK)
				{
					printerr(RBRACKLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACE)
				{
					printerr(LBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACE)
				{
					printerr(RBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==COMMA)
				{
					printerr(COMMALOST);
					sign=LOST;
					break;
				}
				else if(expect==COLON)
				{
					printerr(COLONLOST);
					sign=LOST;
					break;
				}
				else if(expect==SEMICON)
				{
					printerr(SEMICONLOST);
					sign=LOST;
					break;
				} 
			} 
			break;
		case INC:
		case DEC:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==ID)
				{
					printerr(IDLOST);
					sign=LOST;
					break;
				}
				else if(expect==ASSIGN)
				{
					printerr(ASSIGNLOST);
					sign=LOST;
					break;
				}
				else if(expect==LPAREN)
				{
					printerr(LPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==RPAREN)
				{
					printerr(RPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACK)
				{
					printerr(LBRACKLOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACK)
				{
					printerr(RBRACKLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACE)
				{
					printerr(LBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACE)
				{
					printerr(RBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==COMMA)
				{
					printerr(COMMALOST);
					sign=LOST;
					break;
				}
				else if(expect==COLON)
				{
					printerr(COLONLOST);
					sign=LOST;
					break;
				}
				else if(expect==SEMICON)
				{
					printerr(SEMICONLOST);
					sign=LOST;
					break;
				}  
			}
			break;
		case LPAREN:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==ID)
				{
					printerr(IDLOST);
					sign=LOST;
					break;
				}
				else if(expect==ASSIGN)
				{
					printerr(ASSIGNLOST);
					sign=LOST;
					break;
				}
				else if(expect<=RETURN&&expect>=IF)
				{
					printerr(STATEMENTLOST);
					sign=LOST;
					break;
				}
				else if(expect==LPAREN)
				{
					printerr(LPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACK)
				{
					printerr(LBRACKLOST);
					sign=LOST;
					break;
				}
			}
			if(sign==WRONG)
			{
				printerr(LPARENWRONG);
			}
			break;
		case RPAREN:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==ID)
				{
					printerr(IDLOST);
					sign=LOST;
					break;
				}
				else if(expect==NUM||expect==CH||expect==STR)
				{
					printerr(LITERALLOST);
					sign=LOST;
					break;
				}
				else if(expect==LPAREN)
				{
					printerr(LPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==RPAREN)
				{
					printerr(RPARENLOST);
					sign=LOST;
					break;
				}
			}
			if(sign==WRONG)
			{
				printerr(RPARENWRONG);
			}
			break;
		case LBRACK:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==ID)
				{
					printerr(IDLOST);
					sign=LOST;
					break;
				}
			}
			if(sign==WRONG)
			{
				printerr(LBRACKWRONG);
			}
			break;
		case RBRACK:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==NUM)
				{
					printerr(NUMLOST);
					sign=LOST;
					break;
				}
				else if(expect==RPAREN)
				{
					printerr(RPARENLOST);
					sign=LOST;
					break;
				}
			}
			if(sign==WRONG)
			{
				printerr(LBRACKWRONG);
			}
			break;
		case LBRACE:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==ID)
				{
					printerr(IDLOST);
					sign=LOST;
					break;
				}
				else if(expect==SEMICON)
				{
					printerr(SEMICONLOST);
					sign=LOST;
					break;
				}
				else if(expect==RPAREN)
				{
					printerr(RPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACE)
				{
					printerr(LBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACE)
				{
					printerr(RBRACELOST);
					sign=LOST;
					break;
				}
			}
			if(sign==WRONG)
			{
				printerr(LBRACKWRONG);
			}
			break;
		case RBRACE:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==SEMICON)
				{
					printerr(SEMICONLOST);
					sign=LOST;
					break;
				}
				else if(expect==RPAREN)
				{
					printerr(RPARENLOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACK)
				{
					printerr(RBRACKLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACE)
				{
					printerr(LBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACE)
				{
					printerr(RBRACELOST);
					sign=LOST;
					break;
				}
			}
			if(sign==WRONG)
			{
				printerr(RBRACEWRONG);
			}
			break;
		case IF:
		case ELSE:
		case SWITCH:
		case CASE:
		case DEFAULT:
		case WHILE:
		case DO:
		case FOR:
		case BREAK:
		case CONTINUE:
		case RETURN:
			for(i=0;i<num;i++)
			{
				expect=va_arg(p,int);
				if(expect==SEMICON)
				{
					printerr(SEMICONLOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACE)
				{
					printerr(LBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==LBRACE)
				{
					printerr(RBRACELOST);
					sign=LOST;
					break;
				}
				else if(expect==RBRACE)
				{
					printerr(RBRACELOST);
					sign=LOST;
					break;
				}
			}
			if(sign==WRONG)
			{
				printerr(STATEMENTWRONG);
			}
			break;
		default:
			printf("第%d行：未知错误！\n",loc);
			//exit(-1);
	}
	va_end(p);
	if(sign==WRONG)//如果是符号错误，继续读取下一个token
	{
		gonext();
	}
	exit(-1);
} 

void printerr(int errtype) //用于显示语法错误的名称 
{
	switch(errtype)
	{
		case TYPELOST:
			printf("第%d行：类型缺失！\n",loc);
			break; 
		case TYPEWRONG:
			printf("第%d行：类型匹配失败！\n",loc);
			break;
		case IDLOST:
			printf("第%d行：标识符缺失！\n",loc);
			break; 
		case IDWRONG:
			printf("第%d行：标识符匹配失败！\n",loc);
			break;
		case NUMLOST:
			printf("第%d行：数组的长度缺失！\n",loc);
			break; 
		case NUMWRONG:
			printf("第%d行：数组的长度匹配失败！\n",loc);
			break;
		case LITERALLOST:
			printf("第%d行：常量缺失！\n",loc);
			break; 
		case LITERALWRONG:
			printf("第%d行：常量匹配失败！\n",loc);
			break;
		case COMMALOST:
			printf("第%d行：逗号缺失！\n",loc);
			break;
		case COMMAWRONG:
			printf("第%d行：逗号匹配失败！\n",loc);
			break;
		case SEMICONLOST:
			printf("第%d行：分号缺失！\n",loc);
			break;
		case SEMICONWRONG:
			printf("第%d行：分号匹配失败！\n",loc);
			break;
		case ASSIGNLOST:
			printf("第%d行：赋值运算符缺失！\n",loc);
			break;
		case ASSIGNWRONG:
			printf("第%d行：赋值运算符匹配失败！\n",loc);
			break;
		case COLONLOST:
			printf("第%d行：冒号缺失！\n",loc);
			break;
		case COLONWRONG:
			printf("第%d行：冒号匹配失败！\n",loc);
			break;
		case STATEMENTLOST:
			printf("第%d行：语句缺失！\n",loc);
			break;
		case STATEMENTWRONG:
			printf("第%d行：语句匹配失败！\n",loc);
			break;
		case LPARENLOST:
			printf("第%d行：左小括号缺失！\n",loc);
			break;
		case LPARENWRONG:
			printf("第%d行：左小括号匹配失败！\n",loc);
			break;
		case RPARENLOST:
			printf("第%d行：右小括号缺失！\n",loc);
			break;
		case RPARENWRONG:
			printf("第%d行：右小括号匹配失败！\n",loc);
			break;
		case LBRACKLOST:
			printf("第%d行：左中括号缺失！\n",loc);
			break;
		case LBRACKWRONG:
			printf("第%d行：左中括号匹配失败！\n",loc);
			break;
		case RBRACKLOST:
			printf("第%d行：右中括号缺失！\n",loc);
			break;
		case PBRACKWRONG:
			printf("第%d行：右中括号匹配失败！\n",loc);
			break;
		case LBRACELOST:
			printf("第%d行：左大括号缺失！\n",loc);
			break;
		case LBRACEWRONG:
			printf("第%d行：左大括号匹配失败！\n",loc);
			break;
		case RBRACELOST:
			printf("第%d行：右大括号缺失！\n",loc);
			break;
		case RBRACEWRONG:
			printf("第%d行：右大括号匹配失败！\n",loc);
			break;
	}
}
#endif
