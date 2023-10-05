#include "stdio.h"  //头文件
#include "stdlib.h" //头文件
#include<windows.h> //头文件
#include<string.h>  //头文件


void open_web(char *website)
{
    ShellExecuteA(0,"open", website,0,0,1);
}
                                                         
int main(int argc,char *argv[])   //主函数
{ 
HWND hwnd;  
hwnd=FindWindow("ConsoleWindowClass",NULL);    
ShowWindow(hwnd,SW_HIDE);                      
open_web("http://dreampuf.github.io/GraphvizOnline");
return 0;  
}

