# 文件夹结构
- lexer   
词法分析器源代码和可执行文件   
- parser   
语法分析器源代码和可执行文件   
- AST.dot  
用于生成AST图像的标准文件  
-  input.txt   
输入的源文件  
- result.txt
输出的源文件

## lexer（词法分析器） 
- lexer_datastructure.h
- lexer_def.h
- lexer_func.c
- lexer_head.h
- lexer_main.c
## parser（语法分析器）
- parser_datastructure.h
- parser_def.h
- parser_func.c
- parser_head.h
- parser_main.c

# 操作手册   
运行顺序：      
1. 把源文件放入input.txt
2. 打开总系统.c
3. 选择相关功能
4. 打开AST.dot
5. 没有graphviz环境- 打开openweb.exe并复制dot文件
   有graphviz环境- 运行AST_creator.bat生产AST.png
6. 获取AST.png

# 注意事项
1. **请勿在运行时删除temp_token.txt、AST.dot等中间文件**  
2. **运行AST.dot生成图像需要先配置好网络环境**  
3. **本地解析AST.dot需要先配置好graphviz环境**