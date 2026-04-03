@ECHO  OFF
REM  Gera script de make de todos os modulos de teste

pushd  .

cd ..\ferramnt

gmake /b..\composicao  /cTesteLista
gmake /b..\composicao  /cTesteCarta
gmake /b..\composicao  /cTesteBaralho
gmake /b..\composicao  /cTesteColunasAleatorias
gmake /b..\composicao  /cTesteCelulasTemp
gmake /b..\composicao  /cTesteColunaBase 
gmake /b..\composicao  /cCriaLib



popd