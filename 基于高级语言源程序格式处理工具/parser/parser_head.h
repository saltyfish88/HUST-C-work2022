#ifndef __PARSER_HEAD__
#define __PARSER_HEAD__
//***********���ƺ���************// 
void readtokenarray(FILE*fp);//����token
void gonext();//��һ��token
void in();//����AST�е�����
void out();//�˳�AST�е�����
void block_in();//����block
void block_out();//�˳�block
void print_blank();//��Ļ��ӡ�ո�
void fprint_token(FILE*fp);//��ӡtoken
//***********����AST�ĺ���************// 
void init_ast();//��ʼ��AST�����ļ����ģ��
void end_ast();//����AST�����ļ����ģ��
void print_ast(int from,const char*from_name,int to,const char*to_name,int is_terminal);//AST�����ļ����
//**********������������***********// 
void program();//paser��ں���
void segment();//�����
void type();//����
void def();//��ȥ���͵���������
void init();//��ʼ����ֵ
void deflist();//�������������
void idtail();//��������
void defdata();//����������Ϣ
void varrdef();//��������
//*********������������*********//
void funtail();//�������ƺ������
void paralist();//�β��б�
void paradata();//�����β�
void para();//�����β�����
void paradatatail();//���������β�
//*************�������庯��************//
void block();//��
void subprogram();//{}�еĳ���
void localdef();//���ر�������
//************��亯��**************//
void statement();//�����ں���
void whilestat();//while��� 
void forstat();//for��� 
void forinit();//for����ʼ�� 
void dowhilestat();//do while��� 
void ifstat();//if��� 
void elsestat();//else��� 
void casestat();//case��� 
void switchstat();//switch��� 
//**********���ʽ����*********//
void altexpr();//��ѡ�ı��ʽ��ں���
void expr();//���ʽ��ں���
void assexpr();//��ֵ����
void asstail();
void orexpr();//�߼�������
void ortail();
void andexpr();//�߼�������
void andtail();
void cmpexpr();//��ϵ����
void cmptail();
void aloexpr();//+-����
void alotail();
void item();//����Ŀ���������
void itemtail();//*/%����
void factor();//��Ŀ����
void val();//ǰ�������Լ�
void elem();//�����������С��Ԫ
void idexpr();//����������������
void realarg();//��������ĺ����β�
void arglist();//�β��б�
void literal();//����
//*************��������**********//
void synerr(int type,int num,...); 
//type:ʵ�ʵõ��Ĵʷ����š�num:�����õ��Ĵʷ����ŵĸ�����...�������õ��Ĵʷ����š�
void printerr(int errtype);//��ӡ���� 
int noft=0,nofc=0,nexttype=0,loc,if2nd=0,isinfor=0,iserr=0,blocknum=0,layer=0;//��ʼ�����ڼ�¼���ջ�� 
int cnt=0;//���ڼ�¼AST�ڵ��š�
int setted[MAXLEN]={0};//���ڼ�¼�ڵ��Ƿ������á�
char from_name[MAXLEN_OF_CONTENT];
char to_name[MAXLEN_OF_CONTENT];
Token tokenarray[MAXLEN];//token���С�
FILE*tokenlist;
FILE*output;
FILE*graph;
#endif
