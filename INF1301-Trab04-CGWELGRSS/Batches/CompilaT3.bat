@ECHO  OFF
REM  Compila os modulos do trabalho 3
cls

del ..\produto\*.err
del ..\objetos\*.obj

pushd .
nmake /F..\composicao\testepersistencia.make
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testegerenciador.make 
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\principal.make 
popd


del ..\objetos\*.obj
..\ferramnt\compilebanner  /cMensagensCompilacao
copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err
goto sai

:sai