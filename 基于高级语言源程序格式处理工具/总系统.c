#include"lexer\lexer_main.c"
#include"parser\parser_main.c"
int main() {
    int op = 1;//��ʼ��ѡ�� 
    FILE *file;//�����ļ�ָ�� 
	while (op) {
        system("cls");
        printf("------------------��ӭʹ�û��ڸ߼�����Դ�����ʽ������------------------\n");
        printf("1. �ʷ�����\n2. �﷨����\n3. ��������\n0. �˳�����\n��ѡ��");
choose: scanf("%d", &op);
//system("cls");
		if(op==1){
            	lexer_main();
            	printf("\n�����������...\n");
				getchar();
				goto choose;
		}//���дʷ�����
		if(op==2){
            	parser_main();
            	printf("\n�����������...\n");
				getchar();
				goto choose;
		}//�����﷨����
		if(op==3){
   				file = fopen("result.txt", "r"); // "r" ��ʾ��ֻ����ʽ���ļ�
    			if (file == NULL) {
       				printf("�޷����ļ�\n");
    			}
				char line[100]; // ����ÿ�в�����100���ַ�
   				while (fgets(line, sizeof(line), file)) {
       				 printf("%s", line);
   				}//��ӡ�������ź���ļ� 
    			fclose(file);
				printf("\n�����������...\n");
				getchar();
				goto choose;
		}//������������ 
		if(op==0){
				return 0;
		}
    } // end of while
    //return 0;
}

