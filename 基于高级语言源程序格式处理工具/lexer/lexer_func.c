#ifndef __LEXER_FUNC__
#define __LEXER_FUNC__
/**
 * 函数名称: wordscanner
 * 函数功能：从文件中读取字符，将字符序列存储在数组file中
 * 函数输入: fp - 文件指针，指向要读取的文件
 *           file - 字符数组，用于存储读取的字符序列
 * 函数输出：无
 */
void wordscanner(FILE*fp,char file[])
{
	int i=0;
	char c;
	while((c=fgetc(fp))!=EOF)
	{
		file[i]=c;
		i++;
	}
	file[i]='\0';
}
/**
 * 函数名称: nextstep
 * 函数功能：更新指针present和next，用于迭代访问字符数组file
 * 函数输入: file - 字符数组，存储字符序列
 *           cnt - 当前字符位置的索引
 *           present - 当前字符指针
 *           next - 下一个字符指针
 * 函数输出：返回1表示下一个字符可用，返回0表示字符数组已结束
 */
int nextstep(char file[],int cnt,char*present,char*next)
{
	*present=*next;//初始化指针 
	if(file[cnt]!='\0')
	{
		*next=file[1+cnt];
		return 1;
	}//下一个字符可用
	else{return 0;}//字符数组已结束
}
/**
 * 函数名称: token_print_to_file
 * 函数功能：将Token数组中的词法信息按格式输出到文件
 * 函数输入: fp - 文件指针，指向输出文件
 *           tokenarray - Token结构体数组，存储词法信息
 * 函数输出：无
 */
void token_print_to_file(FILE*fp,Token tokenarray[])
{
	int i=0,type=0; 
	if(error==1){return;}//有词法错误，直接返回。
	while((type=tokenarray[i++].type)!=END)
	{
		fprintf(fp,"%d\n",tokenarray[i-1].type);
		if(type==NUM||type==STR||type==ID||type==CH||type==MAC){fprintf(fp,"%s\n",tokenarray[i-1].value);}
		fprintf(fp,"%d\n",tokenarray[i-1].loc);
	}
	fprintf(fp,"%d\n",tokenarray[i-1].type);
	fprintf(fp,"%d",tokenarray[i-1].loc);
}
/**
 * 函数名称: token_print_to_stdout
 * 函数功能：将Token数组中的词法信息按格式输出到标准输出
 * 函数输入: tokenarray - Token结构体数组，存储词法信息
 * 函数输出：无
 */
void token_print_to_stdout(Token tokenarray[])
{
	int i=0,type=0;
	if(error==1){return;}//有词法错误，直接返回。 
	while((type=tokenarray[i].type)!=END)
	{
		i++;
		printf("第%d个词法符号：\n",i);
		switch(type)//判断词法符号种别（内容） 
		{
			case ID:
				printf("\t种别：标识符\n");
				printf("\t内容：%s\n",tokenarray[i-1].value);
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case INT:
				printf("\t种别：整型类型\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case CHAR:
				printf("\t种别：字符型类型\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case FLOAT:
				printf("\t种别：单精度浮点型类型\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case DOUBLE:
				printf("\t种别：双精度浮点型类型\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case VOID:
				printf("\t种别：空类型\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case EXTERN:
				printf("\t种别：全局变量声明\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case NUM:
				printf("\t种别：数值常量\n");
				printf("\t内容：%s\n",tokenarray[i-1].value);
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case CH:
				printf("\t种别：字符型常量\n");
				printf("\t内容：%s\n",tokenarray[i-1].value);
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case STR:
				printf("\t种别：字符串常量\n");
				printf("\t内容：%s\n",tokenarray[i-1].value);
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case NOT:
				printf("\t种别：逻辑非\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case LEA:
				printf("\t种别：取地址\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case ADD:
				printf("\t种别：加法运算\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case SUB:
				printf("\t种别：减法运算\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case MUL:
				printf("\t种别：乘法运算\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case DIV:
				printf("\t种别：除法运算\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case MOD:
				printf("\t种别：取余运算\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case INC:
				printf("\t种别：自增运算\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case DEC:
				printf("\t种别：自减运算\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case GT:
				printf("\t种别：大于\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case GE:
				printf("\t种别：大于等于\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case LT:
				printf("\t种别：小于\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case LE:
				printf("\t种别：小于等于\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case EQU:
				printf("\t种别：等于\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case NEQU:
				printf("\t种别：不等于\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case AND:
				printf("\t种别：逻辑与\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case OR:
				printf("\t种别：逻辑或\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case LPAREN:
				printf("\t种别：左小括号\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case RPAREN:
				printf("\t种别：右小括号\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case LBRACK:
				printf("\t种别：左中括号\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case RBRACK:
				printf("\t种别：右中括号\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case LBRACE:
				printf("\t种别：左大括号\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case RBRACE:
				printf("\t种别：右大括号\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case COMMA:
				printf("\t种别：逗号\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case COLON:
				printf("\t种别：冒号\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case SEMICON:
				printf("\t种别：分号\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case ASSIGN:
				printf("\t种别：赋值\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case IF:
				printf("\t种别：if语句\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case ELSE:
				printf("\t种别：else语句\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case SWITCH:
				printf("\t种别：switch语句\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case CASE:
				printf("\t种别：case语句\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case DEFAULT:
				printf("\t种别：default语句\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case WHILE:
				printf("\t种别：while语句\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case DO:
				printf("\t种别：do语句\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case FOR:
				printf("\t种别：for语句\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case BREAK:
				printf("\t种别：break语句\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case CONTINUE:
				printf("\t种别：continue语句\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case RETURN:
				printf("\t种别：return语句\n");
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
			case MAC:
				printf("\t种别：宏\n");
				printf("\t内容：%s\n",tokenarray[i-1].value);
				printf("\t位置: 第%d行\n",tokenarray[i-1].loc);
				break;
		}
	} 
}
/**
 * 函数名称: lexerr
 * 函数功能：根据错误码打印相应的词法错误信息
 * 函数输入: a - 错误码，表示不同的词法错误类型
 * 函数输出：无
 */
void lexerr(int a)
{
	switch(a)//判断词法错误情况 
	{
		case STR_NO_R_QUTION:
			printf("第%d行：字符串缺少双引号。\n",lin);
			break;
		case NUM_BIN_TYPE:
			printf("第%d行：二进制常量无值。\n",lin);
			break;
		case NUM_HEX_TYPE:
			printf("第%d行：十六进制常量无值。 \n",lin);
			break;
		case CHAR_NO_R_QUTION:
			printf("第%d行：字符类型缺少单引号。\n",lin);
			break;
		case CHAR_NO_DATA:
			printf("第%d行：字符常量无值。\n",lin);
			break;
		case OR_NO_PAIR:
			printf("第%d行：逻辑或缺少|。\n",lin);
			break;
		case TOKEN_NO_EXIST:
			printf("第%d行：错误的词法记号。\n",lin);
			break;
	}
	error=1;
}
#endif
