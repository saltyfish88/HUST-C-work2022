#ifndef __LEXER_HEAD__
#define __LEXER_HEAD__
void wordscanner(FILE*fp,char file[]);//��ȡ�ļ��� 
int nextstep(char file[],int cnt,char*present,char*next);//��һ����
void token_print_to_file(FILE*fp,Token tokenarray[]);//��ӡ�ʷ��Ǻŵ��ļ��� 
void token_print_to_stdout(Token tokenarray[]);//��ӡ�ʷ��Ǻŵ�stdout�� 
void lexerr(int a);//����ʷ��ǺŴ��� 

const char*keywords[]={"int","char","float","double","void","extern","if","else","switch","case","default","while","do","for","break","continue","return",NULL};//�ؼ��֡�
int lin=1,error=0; //�кźʹ����� 
#endif
