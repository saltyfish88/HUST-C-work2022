#include"parser_def.h"
int parser_main()
{
tokenlist=fopen("temp_token.txt","r");//读入处理后的中间文件 
output=fopen("result.txt","w");//输出结果 
init_ast();
if(!tokenlist)
{
	printf("未找到Token序列文件！\n");
	exit(-1);
}
readtokenarray(tokenlist);//读取词法记号数组的内容
fclose(tokenlist);
gonext();//更新词法记号信息
program();
end_ast();
return 0;
}

