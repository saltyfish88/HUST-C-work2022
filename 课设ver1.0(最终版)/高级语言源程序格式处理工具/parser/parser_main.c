#include"parser_def.h"
int main()
{
tokenlist=fopen("../lexer/temp_token.txt","r");
output=fopen("../result.txt","w");
init_ast();
if(!tokenlist)
{
	printf("δ�ҵ�Token�����ļ���\n");
	exit(-1);
}
readtokenarray(tokenlist);
fclose(tokenlist);
gonext();
program();
end_ast();
return 0;
}

