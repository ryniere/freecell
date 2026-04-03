#include <stdio.h>
#include <stdlib.h>
#include "Carta.h"
#include "Baralho.h"
#include "CELULA_TEMPORARIA.H"
#include "COLUNA_BASE.h"
#include "COLUNAS_ALEATORIAS.h"

#ifdef _DEBUG
LIS_tppLista pListaAncora;
#endif

/***************************************************************************
*
*  Função: TRF  &Preencher Lista Ancora
*  ****/

#ifdef _DEBUG
void preencherListaAncora()
{
	pListaAncora = LIS_CriarLista();
	LIS_InserirElementoAntes( pListaAncora, ( void * )TMP_celulaTemporaria );
	LIS_InserirElementoApos( pListaAncora, ( void * )CBSE_ColunaBaseCopas );
	LIS_InserirElementoApos( pListaAncora, ( void * )CBSE_ColunaBaseEspadas );
	LIS_InserirElementoApos( pListaAncora, ( void * )CBSE_ColunaBaseOuros );
	LIS_InserirElementoApos( pListaAncora, ( void * )CBSE_ColunaBasePaus );
	LIS_InserirElementoApos( pListaAncora, ( void * )CALT_coluna1 );
	LIS_InserirElementoApos( pListaAncora, ( void * )CALT_coluna2 );
	LIS_InserirElementoApos( pListaAncora, ( void * )CALT_coluna3 );
	LIS_InserirElementoApos( pListaAncora, ( void * )CALT_coluna4 );
	LIS_InserirElementoApos( pListaAncora, ( void * )CALT_coluna5 );
	LIS_InserirElementoApos( pListaAncora, ( void * )CALT_coluna6 );
	LIS_InserirElementoApos( pListaAncora, ( void * )CALT_coluna7 );
	LIS_InserirElementoApos( pListaAncora, ( void * )CALT_coluna8 );
	LIS_InserirElementoApos( pListaAncora, ( void * )vtBaralho );

} /* Fim função: TRF  &Preencher Lista Ancora */

#endif

/***************************************************************************
*
*  Função: TRF  &Tratar Ponteiro Nulo Lista
*  ****/

void TRF_TratarPonteiroNuloLista( LIS_tppLista pLista)
{
	pLista = LIS_CriarLista();

} /* Fim função: TRF  &Tratar Ponteiro Nulo Lista */

/***************************************************************************
*
*  Função: TRF  &Abortar Programa
*  ****/

void TRF_AbortarPrograma( char * mensagem )
{
	printf(" %s\n", mensagem); /* Imprime mensagem de erro */

	/* Desaloca estruturas */

#ifdef _RELEASE

	BAR_DestruirBaralho();
	TMP_DestruirCelulasTemporarias();
	CALT_DestruirColunasAleatorias();
	CBSE_DestruirColunasBase();

	exit(1);  Aborta programa */

#endif

} /* Fim função: TRF  &Abortar Programa */
