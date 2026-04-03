@ECHO  OFF
REM  Gera script de make de todos os modulos de teste

pushd  .

cd ..\ferramnt

gmake /b..\composicao  /cTestePersistencia
gmake /b..\composicao  /cTesteGerenciador
gmake /b..\composicao  /cPrincipal


popd