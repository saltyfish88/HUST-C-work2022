@echo off
if not exist D:\��ѧ\����\ѧУ�γ�\C�����Ӽ�������_���ݽṹ�����\�߼�����Դ�����ʽ������ (
    echo δ�ҵ�dot�ļ���
    pause
    exit /b 1
) 
cd D:\��ѧ\����\ѧУ�γ�\C�����Ӽ�������_���ݽṹ�����\�߼�����Դ�����ʽ������
dot -Tpng AST.dot -o AST.png 
if %ERRORLEVEL% NEQ 0 (
    echo δ�ҵ�dot�ļ���graphviz�ı�����
    pause
    exit /b 2
)
echo complete
pause