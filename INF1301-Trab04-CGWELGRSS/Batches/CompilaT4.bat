@ECHO  OFF
REM  Compila todos os exemplos simples 
cls

del ..\produto\*.err
del ..\objetos\*.obj

pushd .
nmake /F..\composicao\testelistadebug.make
popd




del ..\objetos\*.obj
..\ferramnt\compilebanner  /cMensagensCompilacao
copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err
goto sai

:sai