@ECHO  OFF
REM  Gera script de make de todos os modulos de teste

pushd  .

cd ..\ferramnt

gmake /b..\composicao  /cTesteListaDebug




popd