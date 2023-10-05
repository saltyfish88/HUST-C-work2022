#ifndef __LEXER_DATASTRUCTURE__
#define __LEXER_DATASTRUCTURE__
typedef struct TOKEN//����token. 
{
	int type;
	char value[MAXLEN_OF_CONTENT];
	int loc;
}Token;

enum Tag//�ʷ����ŵı�ǩ 
{
	ERR,//���� 
	END,//�ļ������� 
	ID,//��ʶ���� 
	INT,CHAR,FLOAT,DOUBLE,VOID,EXTERN,//�������͡� 
	NUM,//���ֳ����� 
	CH,//�ַ������� 
	STR,//�ַ����� 
	NOT,LEA,//��& 
	ADD,SUB,MUL,DIV,MOD,//+-*/% 
	INC,DEC,//++--
	GT,GE,LT,LE,EQU,NEQU,//>>=<<==!=
	AND,OR,//&&|| 
	LPAREN,RPAREN,//���� 
	LBRACK,RBRACK,//���� 
	LBRACE,RBRACE,//���� 
	COMMA,COLON,SEMICON,//������ 
	ASSIGN,//= 
	IF,ELSE,SWITCH,CASE,DEFAULT,WHILE,DO,FOR,BREAK,CONTINUE,RETURN,//�ؼ��֡�
	MAC//�ꡣ 
}; 

enum LEXERROR//�ʷ�����ı�ǩ 
{
	STR_NO_R_QUTION,//�ַ���ȱ����˫���š� 
	NUM_BIN_TYPE,//�����Ƴ�����ֵ�� 
	NUM_HEX_TYPE,//ʮ�����Ƴ�����ֵ�� 
	CHAR_NO_R_QUTION,//�ַ�����ȱ���ҵ����š� 
	CHAR_NO_DATA,//�ַ�������ֵ�� 
	OR_NO_PAIR,//�߼���ȱ��| �� 
	TOKEN_NO_EXIST//����Ĵʷ��Ǻš� 
};
#endif 
