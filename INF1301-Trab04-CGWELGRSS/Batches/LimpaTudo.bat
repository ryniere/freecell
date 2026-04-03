@ECHO  OFF
REM  Elimina todos os arquivos gerados


cd ..\Composicao
del *.list
del *.make

cd ..\Objetos
del *.build

cd ..\Produto
del *.log
del *.err
del jogoSalvo.txt

cd ..\Scripts
del *.estat


cd ..\Batches

popd

:sai

