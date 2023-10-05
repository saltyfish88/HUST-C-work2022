#ifndef __PARSER_HEAD__
#define __PARSER_HEAD__
//***********控制函数************// 
void readtokenarray(FILE*fp);//读入token
void gonext();//下一个token
void in();//进入AST中的子树
void out();//退出AST中的子树
void block_in();//进入block
void block_out();//退出block
void print_blank();//屏幕打印空格
void fprint_token(FILE*fp);//打印token
//***********绘制AST的函数************// 
void init_ast();//初始化AST绘制文件输出模块
void end_ast();//结束AST绘制文件输出模块
void print_ast(int from,const char*from_name,int to,const char*to_name,int is_terminal);//AST绘制文件输出
//**********变量声明函数***********// 
void program();//paser入口函数
void segment();//程序段
void type();//类型
void def();//除去类型的完整声明
void init();//初始化赋值
void deflist();//，后的连续声明
void idtail();//函数声明
void defdata();//后续声明信息
void varrdef();//数组声明
//*********函数声明函数*********//
void funtail();//函数名称后的声明
void paralist();//形参列表
void paradata();//函数形参
void para();//函数形参声明
void paradatatail();//后续函数形参
//*************函数定义函数************//
void block();//块
void subprogram();//{}中的程序
void localdef();//本地变量声明
//************语句函数**************//
void statement();//语句入口函数
void whilestat();//while语句 
void forstat();//for语句 
void forinit();//for语句初始化 
void dowhilestat();//do while语句 
void ifstat();//if语句 
void elsestat();//else语句 
void casestat();//case语句 
void switchstat();//switch语句 
//**********表达式函数*********//
void altexpr();//可选的表达式入口函数
void expr();//表达式入口函数
void assexpr();//赋值运算
void asstail();
void orexpr();//逻辑或运算
void ortail();
void andexpr();//逻辑与运算
void andtail();
void cmpexpr();//关系运算
void cmptail();
void aloexpr();//+-运算
void alotail();
void item();//带单目运算的整体
void itemtail();//*/%运算
void factor();//单目运算
void val();//前置自增自减
void elem();//参与运算的最小单元
void idexpr();//参与运算的数组或函数
void realarg();//参与运算的函数形参
void arglist();//形参列表
void literal();//常数
//*************错误处理函数**********//
void synerr(int type,int num,...); 
//type:实际得到的词法符号。num:期望得到的词法符号的个数。...是期望得到的词法符号。
void printerr(int errtype);//打印错误。 
int noft=0,nofc=0,nexttype=0,loc,if2nd=0,isinfor=0,iserr=0,blocknum=0,layer=0;//初始化用于记录层的栈。 
int cnt=0;//用于记录AST节点编号。
int setted[MAXLEN]={0};//用于记录节点是否已设置。
char from_name[MAXLEN_OF_CONTENT];
char to_name[MAXLEN_OF_CONTENT];
Token tokenarray[MAXLEN];//token序列。
FILE*tokenlist;
FILE*output;
FILE*graph;
#endif
