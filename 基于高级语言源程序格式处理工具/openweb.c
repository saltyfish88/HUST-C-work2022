#include "stdio.h"  //ͷ�ļ�
#include "stdlib.h" //ͷ�ļ�
#include<windows.h> //ͷ�ļ�
#include<string.h>  //ͷ�ļ�


void open_web(char *website)
{
    ShellExecuteA(0,"open", website,0,0,1);
}
                                                         
int main(int argc,char *argv[])   //������
{ 
HWND hwnd;  
hwnd=FindWindow("ConsoleWindowClass",NULL);    
ShowWindow(hwnd,SW_HIDE);                      
open_web("http://dreampuf.github.io/GraphvizOnline");
return 0;  
}

