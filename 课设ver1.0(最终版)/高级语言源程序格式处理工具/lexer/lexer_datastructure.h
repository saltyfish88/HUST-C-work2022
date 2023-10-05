#ifndef __LEXER_DATASTRUCTURE__
#define __LEXER_DATASTRUCTURE__
typedef struct TOKEN//定义token. 
{
	int type;
	char value[MAXLEN_OF_CONTENT];
	int loc;
}Token;

enum Tag//词法符号的标签 
{
	ERR,//错误。 
	END,//文件结束。 
	ID,//标识符。 
	INT,CHAR,FLOAT,DOUBLE,VOID,EXTERN,//数据类型。 
	NUM,//数字常量。 
	CH,//字符常量。 
	STR,//字符串。 
	NOT,LEA,//！& 
	ADD,SUB,MUL,DIV,MOD,//+-*/% 
	INC,DEC,//++--
	GT,GE,LT,LE,EQU,NEQU,//>>=<<==!=
	AND,OR,//&&|| 
	LPAREN,RPAREN,//（） 
	LBRACK,RBRACK,//【】 
	LBRACE,RBRACE,//｛｝ 
	COMMA,COLON,SEMICON,//，：； 
	ASSIGN,//= 
	IF,ELSE,SWITCH,CASE,DEFAULT,WHILE,DO,FOR,BREAK,CONTINUE,RETURN,//关键字。
	MAC//宏。 
}; 

enum LEXERROR//词法错误的标签 
{
	STR_NO_R_QUTION,//字符串缺少右双引号。 
	NUM_BIN_TYPE,//二进制常量无值。 
	NUM_HEX_TYPE,//十六进制常量无值。 
	CHAR_NO_R_QUTION,//字符类型缺少右单引号。 
	CHAR_NO_DATA,//字符常量无值。 
	OR_NO_PAIR,//逻辑或缺少| 。 
	TOKEN_NO_EXIST//错误的词法记号。 
};
#endif 
