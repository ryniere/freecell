@ECHO  OFF
REM  Compila todos os exemplos simples 
cls

del ..\produto\*.err
del ..\objetos\*.obj

pushd .
nmake /F..\composicao\testelista.make
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testecarta.make 
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testebaralho.make
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testecolunasaleatorias.make
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testecelulastemp.make
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testecolunabase.make
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\CriaLib.make  "PRD="
popd


del ..\objetos\*.obj
..\ferramnt\compilebanner  /cMensagensCompilacao
copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err
goto sai

:sai