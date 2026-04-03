REM executa os testes dos modulos do FreeCell

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\TRAB2-1  /s..\scripts\TesteColunasAleatorias  /l..\produto\TesteColunasAleatorias   /a..\scripts\estatisticas
..\produto\TRAB2-2  /s..\scripts\TesteCarta              /l..\produto\TesteCarta               /a..\scripts\estatisticas
..\produto\TRAB2-3  /s..\scripts\TesteCelulasTemp        /l..\produto\TesteCelulasTemp         /a..\scripts\estatisticas
..\produto\TRAB2-4  /s..\scripts\TesteBaralho            /l..\produto\TesteBaralho             /a..\scripts\estatisticas
..\produto\TRAB2-5  /s..\scripts\TesteColunaBase         /l..\produto\TesteColunaBase          /a..\scripts\estatisticas
..\produto\TRAB2-6  /s..\scripts\TesteLista              /l..\produto\TesteLista               /a..\scripts\estatisticas

cd ..\Produto
TRAB3-1  /s..\scripts\TestePersistencia       /l..\produto\TestePersistencia        /a..\scripts\estatisticas
del jogoSalvo.txt
TRAB3-2  /s..\scripts\TesteGerenciador        /l..\produto\TesteGerenciador         /a..\scripts\estatisticas
cd ..\Batches

..\produto\TRAB4-1  /s..\scripts\TesteContadoresLista            /l..\produto\TesteContadoresLista             /a..\scripts\estatisticas
..\produto\TRAB4-1  /s..\scripts\TesteControleEspacoLista            /l..\produto\TesteControleEspacoLista            /a..\scripts\estatisticas
..\produto\TRAB4-1  /s..\scripts\TesteDeturpaLista            /l..\produto\TesteDeturpaLista             /a..\scripts\estatisticas
..\produto\TRAB4-1  /s..\scripts\TesteListaDebug            /l..\produto\TesteListaDebug             /a..\scripts\estatisticas

..\ferramnt\CompileBanner     /c"Estatisticas acumuladas"
..\ferramnt\exbestat /e..\scripts\estatisticas

:sai