# 文件夹结构
+ lexer   
词法分析器源代码和可执行文件   
+ parser   
语法分析器源代码和可执行文件   
+ create_AST.bat   
用于生成AST   
+ input.txt   
输入的源文件   
# 操作手册   
编译顺序：   
1. 编译lexer.main   
2. 编译parser.main 
      
运行顺序：      
1. 把源文件放入input.txt
2. 运行lexer.exe
3. 运行parser.exe
4. 运行create_AST.bat
5. 打开AST.png
# 注意事项
1. **请不要在运行时删除temp_token.txt、AST.dot等中间文件**  
2. **运行create_AST.bat需要先配置好graphviz的环境**  