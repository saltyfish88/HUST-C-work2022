#include"parser_def.h"
int parser_main()
{
tokenlist=fopen("temp_token.txt","r");//���봦�����м��ļ� 
output=fopen("result.txt","w");//������ 
init_ast();
if(!tokenlist)
{
	printf("δ�ҵ�Token�����ļ���\n");
	exit(-1);
}
readtokenarray(tokenlist);//��ȡ�ʷ��Ǻ����������
fclose(tokenlist);
gonext();//���´ʷ��Ǻ���Ϣ
program();
end_ast();
return 0;
}

