# 代码分析
首先，使用Visual studio里的intellisense进行代码检查，消除了memcpy的使用等警告，如图所示。
![Alt text](intellisense.png)

接着，使用cppcheck工具进行进一步分析，消除了offset声明为const的警告，所剩皆为找不到文件的information，警告均已消除，如图所示。
![Alt text](cppcheck.png)

分析结果具见 checkresult.xml