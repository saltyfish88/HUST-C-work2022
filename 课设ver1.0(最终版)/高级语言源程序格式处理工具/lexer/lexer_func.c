#ifndef __LEXER_FUNC__
#define __LEXER_FUNC__
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
int nextstep(char file[],int cnt,char*present,char*next)
{
	*present=*next;
	if(file[cnt]!='\0')
	{
		*next=file[1+cnt];
		return 1;
	}
	else{return 0;}
}
void token_print_to_file(FILE*fp,Token tokenarray[])
{
	int i=0,type=0; 
	if(error==1){return;}//�дʷ�����ֱ�ӷ��ء�
	while((type=tokenarray[i++].type)!=END)
	{
		fprintf(fp,"%d\n",tokenarray[i-1].type);
		if(type==NUM||type==STR||type==ID||type==CH||type==MAC){fprintf(fp,"%s\n",tokenarray[i-1].value);}
		fprintf(fp,"%d\n",tokenarray[i-1].loc);
	}
	fprintf(fp,"%d\n",tokenarray[i-1].type);
	fprintf(fp,"%d",tokenarray[i-1].loc);
}
void token_print_to_stdout(Token tokenarray[])
{
	int i=0,type=0;
	if(error==1){return;}//�дʷ�����ֱ�ӷ��ء� 
	while((type=tokenarray[i].type)!=END)
	{
		i++;
		printf("��%d���ʷ����ţ�\n",i);
		switch(type)
		{
			case ID:
				printf("\t�ֱ𣺱�ʶ��\n");
				printf("\t���ݣ�%s\n",tokenarray[i-1].value);
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case INT:
				printf("\t�ֱ���������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case CHAR:
				printf("\t�ֱ��ַ�������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case FLOAT:
				printf("\t�ֱ𣺵����ȸ���������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case DOUBLE:
				printf("\t�ֱ�˫���ȸ���������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case VOID:
				printf("\t�ֱ𣺿�����\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case EXTERN:
				printf("\t�ֱ�ȫ�ֱ�������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case NUM:
				printf("\t�ֱ���ֵ����\n");
				printf("\t���ݣ�%s\n",tokenarray[i-1].value);
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case CH:
				printf("\t�ֱ��ַ��ͳ���\n");
				printf("\t���ݣ�%s\n",tokenarray[i-1].value);
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case STR:
				printf("\t�ֱ��ַ�������\n");
				printf("\t���ݣ�%s\n",tokenarray[i-1].value);
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case NOT:
				printf("\t�ֱ��߼���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case LEA:
				printf("\t�ֱ�ȡ��ַ\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case ADD:
				printf("\t�ֱ𣺼ӷ�����\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case SUB:
				printf("\t�ֱ𣺼�������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case MUL:
				printf("\t�ֱ𣺳˷�����\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case DIV:
				printf("\t�ֱ𣺳�������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case MOD:
				printf("\t�ֱ�ȡ������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case INC:
				printf("\t�ֱ���������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case DEC:
				printf("\t�ֱ��Լ�����\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case GT:
				printf("\t�ֱ𣺴���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case GE:
				printf("\t�ֱ𣺴��ڵ���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case LT:
				printf("\t�ֱ�С��\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case LE:
				printf("\t�ֱ�С�ڵ���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case EQU:
				printf("\t�ֱ𣺵���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case NEQU:
				printf("\t�ֱ𣺲�����\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case AND:
				printf("\t�ֱ��߼���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case OR:
				printf("\t�ֱ��߼���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case LPAREN:
				printf("\t�ֱ���С����\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case RPAREN:
				printf("\t�ֱ���С����\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case LBRACK:
				printf("\t�ֱ���������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case RBRACK:
				printf("\t�ֱ���������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case LBRACE:
				printf("\t�ֱ��������\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case RBRACE:
				printf("\t�ֱ��Ҵ�����\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case COMMA:
				printf("\t�ֱ𣺶���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case COLON:
				printf("\t�ֱ�ð��\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case SEMICON:
				printf("\t�ֱ𣺷ֺ�\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case ASSIGN:
				printf("\t�ֱ𣺸�ֵ\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case IF:
				printf("\t�ֱ�if���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case ELSE:
				printf("\t�ֱ�else���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case SWITCH:
				printf("\t�ֱ�switch���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case CASE:
				printf("\t�ֱ�case���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case DEFAULT:
				printf("\t�ֱ�default���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case WHILE:
				printf("\t�ֱ�while���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case DO:
				printf("\t�ֱ�do���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case FOR:
				printf("\t�ֱ�for���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case BREAK:
				printf("\t�ֱ�break���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case CONTINUE:
				printf("\t�ֱ�continue���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case RETURN:
				printf("\t�ֱ�return���\n");
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
			case MAC:
				printf("\t�ֱ𣺺�\n");
				printf("\t���ݣ�%s\n",tokenarray[i-1].value);
				printf("\tλ��: ��%d��\n",tokenarray[i-1].loc);
				break;
		}
	} 
}
void lexerr(int a)
{
	switch(a)
	{
		case STR_NO_R_QUTION:
			printf("��%d�У��ַ���ȱ����˫���š�\n",lin);
			break;
		case NUM_BIN_TYPE:
			printf("��%d�У������Ƴ�����ֵ��\n",lin);
			break;
		case NUM_HEX_TYPE:
			printf("��%d�У�ʮ�����Ƴ�����ֵ�� \n",lin);
			break;
		case CHAR_NO_R_QUTION:
			printf("��%d�У��ַ�����ȱ���ҵ����š�\n",lin);
			break;
		case CHAR_NO_DATA:
			printf("��%d�У��ַ�������ֵ��\n",lin);
			break;
		case OR_NO_PAIR:
			printf("��%d�У��߼���ȱ��|��\n",lin);
			break;
		case TOKEN_NO_EXIST:
			printf("��%d�У�����Ĵʷ��Ǻš�\n",lin);
			break;
	}
	error=1;
}
#endif
