set path=C:\WorkProg\Bison\bin
bison.exe -d GridStack.y
flex.exe GridStack.lex
call "C:\WorkProg\VisualStudio.NET 2003\Vc7\bin\vcvars32.bat"
"C:\WorkProg\VisualStudio.NET 2003\Vc7\bin\nmake.exe" RELEASE=1 all
del GridStack.exe
copy /b Release\GridStack_test.exe GridStack.exe