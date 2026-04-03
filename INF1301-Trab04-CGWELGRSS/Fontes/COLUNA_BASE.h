#if ! defined( ColunaBase_ )
#define ColunaBase_

/***************************************************************************
* 
*  $MCD M�dulo de defini��o: CBSE ColunaBase
*
*  Arquivo gerado:              COLUNA_BASE.H
*  Letras identificadoras:      CBSE
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  $ED Descri��o do m�dulo
*
*  Cont�m  4 listas de endere�os de carta, os quais s�o externalizados pelo m�dulo.
*  Este m�dulo permite o preenchimento dos elementos destas listas atrav�s 
*  da fun��o de inser��o de cartas.
***************************************************************************/

#include <stdio.h>
#include <malloc.h>
#include "Carta.h"
#include "LISTA.h"

#if defined( ColunaBase_OWN )
   #define ColunaBase_EXT
#else
   #define ColunaBase_EXT extern
#endif

#define QTD_COLUNAS_BASE 4

/* Declara��es importadas pelo m�dulo */

extern  char* CRT_STRING_COPAS;
extern  char* CRT_STRING_ESPADAS;
extern  char* CRT_STRING_OUROS;
extern  char* CRT_STRING_PAUS;

/* Declara��es exportadas pelo m�dulo */

LIS_tppLista CBSE_ColunaBaseCopas;

LIS_tppLista CBSE_ColunaBaseOuros;

LIS_tppLista CBSE_ColunaBaseEspadas;

LIS_tppLista CBSE_ColunaBasePaus;


/* indice das colunas */
   typedef enum {
		
	   CBSE_IndiceColunaCopas = 1,
			/* �ndice colunas copas */

	   CBSE_IndiceColunaEspadas,
			/* �ndice colunas espadas */

	   CBSE_IndiceColunaOuros,
			/* �ndice colunas ouros */
	   
	   CBSE_IndiceColunaPaus,
			/* �ndice colunas paus */

   }CBSE_IndiceColunasBase;

/************* Fun��es exportadas pelo m�dulo **************************/

/***********************************************************************
*
*  $FC Fun��o: CBSE  &Criar colunas bases
*
*  $ED Descri��o da fun��o
*		A fun��o cria 4 listas para representarem as colunas base de cada naipe.
*
*  $EP Par�metros
*		N�o tem Par�metros
*
*  $FV tipo retornado
*		COR_CondRetOK se colunas foram criadas corretamente
*		COR_CondRerErro, se ocorreu algum problema ao criar colunas base
*
***********************************************************************/

COR_tpCondRet CBSE_CriarColunasBase();

/***********************************************************************
*
*  $FC Fun��o: CBSE  &Inserir Carta na colunas bases
*
*  $ED Descri��o da fun��o
*		A fun��o testa qual o naipe da carta, e insere, se permitido,
*		em sua respectiva coluna base.
*
*  $EP Par�metros
*		ptpCarta - ponteiro para a carta a ser inserida.
*		ixIndice - indice indicando a coluna onde ser� inserida a carta
*
*  $FV tipo retornado
*		COR_CondRetOK, se a carta foi inserida corretamente.
*		COR_CondRetErro, se ocorreu algum erro.
*		COR_CondRetAtoProibido, se n�o � permitido o movimento
***********************************************************************/

COR_tpCondRet CBSE_InserirCartaColunasBases( CRT_ptpCarta ptpCarta, int ixIndice);

/***********************************************************************
*
*  $FC Fun��o: CBSE  &Imprimir colunas bases
*
*  $ED Descri��o da fun��o
*		A fun��o ImprimirColunasBases imprime a ultima carta de cada coluna base
*
*  $EP Par�metros
*		N�o tem Par�metros
*
*   $FV tipo retornado
*		COR_CondRetOK, se a coluna foi impressa corretamente.
*		COR_CondRetErro, se ocorreu algum erro.
*
***********************************************************************/

COR_tpCondRet CBSE_ImprimirColunasBases();

/***********************************************************************
*
*  $FC Fun��o: CBSE  &Destruir colunas base
*
*  $ED Descri��o da fun��o
*		A fun��o libera a mem�ria �s colunas base e seus componentes interiores .
*
*  $EP Par�metros
*		N�o h� par�metros
*
*  $FV tipo retornado
*		COR_CondRetOK, se a carta foi inserida corretamente.
*		COR_CondRetErro, se ocorreu algum erro.
*
***********************************************************************/

COR_tpCondRet CBSE_DestruirColunasBase();

/***********************************************************************
*
*  $FC Fun��o: CBSE  &Obter Carta Coluna Base
*
*  $ED Descri��o da fun��o
*		A fun��o obt�m o endere�o da carta corrente da coluna base sugerida.
*
*  $EP Par�metros
*		ixIndiceColuna - representa o �ndice da coluna na qual se quer obter a carta.
*			copas = 1, espadas = 2, ouros = 3, paus = 4.
*
*  $FV tipo retornado
*		Se a carta foi obtida corretamente, retorna ponteiro para a carta
*		NULL, se ocorreu algum erro.
*
***********************************************************************/

CRT_ptpCarta CBSE_ObterCartaColunaBase( int ixIndiceColuna );

/***********************************************************************
*
*  $FC Fun��o: CBSE  &Ir Final Coluna Base
*
*  $ED Descri��o da fun��o
*		A fun��o posiciona o elemento corrente na ultima carta da coluna.
*
*  $EP Par�metros
*		ixIndiceColuna - representa o �ndice da coluna na qual se quer obter a carta.
*			copas = 1, espadas = 2, ouros = 3, paus = 4.
*
*  $FV tipo retornado
*		COR_CondRetOK, se executou corretamente.
*		COR_CondRetErro, se o indice correpondente a coluna for invalido.
*
***********************************************************************/

COR_tpCondRet CBES_IrFinalColunaBase( int ixIndice);

/***********************************************************************
*
*  $FC Fun��o: CBSE  &Ir Inicio Coluna Base
*
*  $ED Descri��o da fun��o
*		A fun��o posiciona o elemento corrente na primeira carta da coluna.
*
*  $EP Par�metros
*		ixIndiceColuna - representa o �ndice da coluna na qual se quer obter a carta.
*			copas = 1, espadas = 2, ouros = 3, paus = 4.
*
*  $FV tipo retornado
*		COR_CondRetOK, se executou corretamente.
*		COR_CondRetErro, se o indice correpondente a coluna for invalido.
*
***********************************************************************/

COR_tpCondRet CBES_IrInicioColunaBase( int ixIndice);

/***********************************************************************
*
*  $FC Fun��o: CBSE  &Avan�ar Elem Corr Coluna Base
*
*  $ED Descri��o da fun��o
*		A fun��o posiciona o elemento corrente da coluna, uma carta antes do elemento corrente atual.
*
*  $EP Par�metros
*		ixIndiceColuna - representa o �ndice da coluna na qual se quer obter a carta.
*			copas = 1, espadas = 2, ouros = 3, paus = 4.
*		numElem - o n�mero de elementos a andar.
*
*  $FV tipo retornado
*		COR_CondRetOK, se executou corretamente.
*		COR_CondRetErro, se n�o foi possivel avan�ar elemento corrente.
*
*		N�o ser� dada mais informa��o quanto ao problema ocorrido.
***********************************************************************/

COR_tpCondRet CBSE_AvancarElemCorrColunaBase( CBSE_IndiceColunasBase ixIndice, int numElem);


#undef ColunaBase_EXT

/********** Fim do m�dulo de defini��o: BSE ColunaBase ******************/
#else
#endif
