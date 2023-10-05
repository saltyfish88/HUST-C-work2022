#ifndef __LEXER_HEAD__
#define __LEXER_HEAD__
void wordscanner(FILE*fp,char file[]);//读取文件。 
int nextstep(char file[],int cnt,char*present,char*next);//下一步。
void token_print_to_file(FILE*fp,Token tokenarray[]);//打印词法记号到文件。 
void token_print_to_stdout(Token tokenarray[]);//打印词法记号到stdout。 
void lexerr(int a);//处理词法记号错误。 

const char*keywords[]={"int","char","float","double","void","extern","if","else","switch","case","default","while","do","for","break","continue","return",NULL};//关键字。
int lin=1,error=0; //行号和错误标记 
#endif
