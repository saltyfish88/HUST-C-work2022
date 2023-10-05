#include"lexer\lexer_main.c"
#include"parser\parser_main.c"
int main() {
    int op = 1;//初始化选项 
    FILE *file;//定义文件指针 
	while (op) {
        system("cls");
        printf("------------------欢迎使用基于高级语言源程序格式处理工具------------------\n");
        printf("1. 词法分析\n2. 语法分析\n3. 缩进编排\n0. 退出程序\n请选择：");
choose: scanf("%d", &op);
//system("cls");
		if(op==1){
            	lexer_main();
            	printf("\n按任意键继续...\n");
				getchar();
				goto choose;
		}//进行词法分析
		if(op==2){
            	parser_main();
            	printf("\n按任意键继续...\n");
				getchar();
				goto choose;
		}//进行语法分析
		if(op==3){
   				file = fopen("result.txt", "r"); // "r" 表示以只读方式打开文件
    			if (file == NULL) {
       				printf("无法打开文件\n");
    			}
				char line[100]; // 假设每行不超过100个字符
   				while (fgets(line, sizeof(line), file)) {
       				 printf("%s", line);
   				}//打印缩进编排后的文件 
    			fclose(file);
				printf("\n按任意键继续...\n");
				getchar();
				goto choose;
		}//进行缩进编排 
		if(op==0){
				return 0;
		}
    } // end of while
    //return 0;
}

