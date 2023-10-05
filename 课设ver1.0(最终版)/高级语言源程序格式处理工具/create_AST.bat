@echo off
if not exist D:\大学\程序\学校课程\C语言子集编译器_数据结构课设版\高级语言源程序格式处理工具 (
    echo 未找到dot文件夹
    pause
    exit /b 1
) 
cd D:\大学\程序\学校课程\C语言子集编译器_数据结构课设版\高级语言源程序格式处理工具
dot -Tpng AST.dot -o AST.png 
if %ERRORLEVEL% NEQ 0 (
    echo 未找到dot文件或graphviz的编译器
    pause
    exit /b 2
)
echo complete
pause