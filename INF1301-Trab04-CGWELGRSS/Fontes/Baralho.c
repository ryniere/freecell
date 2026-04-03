/***************************************************************************
*
*  $MCD Módulo de implementação: BAR Baralho
*
*  Arquivo gerado:              Baralho.c
*  Letras identificadoras:      BAR
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  
***************************************************************************/

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Baralho.h"

#define Baralho_OWN
#include "Baralho.H"
#undef Baralho_OWN

#include "PrivilegioCarta.H"

#define QTD_CARTA_NAIPE 13

/***** Protótipos das funções encapuladas no módulo *****/

static COR_tpCondRet PreencherNaipe( int ixIndiceAtual, char * szNaipe );

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: BAR  &Criar baralho
*****/

 COR_tpCondRet BAR_CriarBaralho()
 {
	
	 /*Preenche o baralho com cartas do naipe copas*/ 
	 if ( ( PreencherNaipe( 0, CRT_STRING_COPAS ) ) == COR_CondRetErro )
	 {
		 return COR_CondRetErro;
	 }	 
     
	 /*Preenche o baralho com cartas do naipe espadas*/
	 if ( ( PreencherNaipe( QTD_CARTA_NAIPE, CRT_STRING_ESPADAS ) ) == COR_CondRetErro )
	 {
		 return COR_CondRetErro;
	 }	 
	 
	 /*Preenche o baralho com cartas do naipe ouros*/
	 if ( ( PreencherNaipe( 2 * QTD_CARTA_NAIPE, CRT_STRING_OUROS ) ) == COR_CondRetErro )
	 {
		 return COR_CondRetErro;
	 }	
	 
	 /*Preenche o baralho com cartas do naipe paus*/
	 if ( ( PreencherNaipe( 3 * QTD_CARTA_NAIPE, CRT_STRING_PAUS ) ) == COR_CondRetErro )
	 {
		 return COR_CondRetErro;
	 }
 	 
	return COR_CondRetOK;

 } /* Fim função: BAR  &Criar Baralho */

/***********************************************************************
*
*  $FC Função: BAR  &Destruir baralho
*****/

COR_tpCondRet BAR_DestruirBaralho()
{
	int ixIndice = 0;
	/* Destroi cartas do baralho */
	for(ixIndice; ixIndice < QTD_CARTAS; ixIndice++) {
		PCRT_DestruirCarta( vtBaralho[ixIndice] );
		if (vtBaralho[ixIndice]!=NULL){

			return COR_CondRetErro;

		}
	}
	return COR_CondRetOK;

} /* Fim função: BAR  &Destruir Baralho */

/***********************************************************************
*
*  $FC Função: BAR  &Embaralhar
*****/

COR_tpCondRet BAR_Embaralhar()
{
	int ixIndice, ixRandom;
	CRT_ptpCarta ptpAuxiliar;

	/* Função usada para escolher aleatoriamente números inteiros */
	srand( ( int )time(NULL) );
	for(ixIndice = 0; ixIndice < QTD_CARTAS; ixIndice++){

		if (vtBaralho[ixIndice]==NULL){

			return COR_CondRetErro;

		}

		/* Gera número aleatório */
		ixRandom = rand() % QTD_CARTAS;

		/* Embaralha as cartas */
		ptpAuxiliar = vtBaralho[ixRandom];
		vtBaralho[ixRandom] = vtBaralho[ixIndice];
		vtBaralho[ixIndice] = ptpAuxiliar;
	}

	return COR_CondRetOK;

} /* Fim função: BAR  &Embaralhar */

/***********************************************************************
*
*  $FC Função: BAR  &Buscar Carta Baralho Ordenado
*****/

CRT_ptpCarta BAR_BuscarCartaBaralhoOrdenado( int iValor, char * szNaipe ){

	int ixIndice = -1;
	/* Testa se valor da carta esta correto */
	if( (iValor <= 0) || (iValor > 13) ) {
		return NULL;
	}

	/* Testa se a carta desejada é de copas */
	if( strcmp( szNaipe, CRT_STRING_COPAS ) == 0 ){
		
		ixIndice = iValor - 1;
	} /* Testa se a carta desejada é de espadas */
	else if( strcmp(szNaipe, CRT_STRING_ESPADAS) == 0 ){
		
		ixIndice = 12 + iValor;

	} /* Testa se a carta desejada é de ouros */
	else if( strcmp( szNaipe,CRT_STRING_OUROS ) == 0 ){
		
		ixIndice = 25 + iValor;

	} /* Testa se a carta desejada é de paus */
	else if( strcmp(szNaipe, CRT_STRING_PAUS ) == 0 ){
		
		ixIndice = 38 + iValor;

		}
	else{
		/* Naipe da carta está errado */
		return NULL;
	}
	
	return vtBaralho[ixIndice];


}/* Fim função: BAR  &Buscar Carta Baralho Ordenado */
 
/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: BAR  -Preencher cartas de um naipe
*
*  $ED Descrição da função
*    Cria todas a cartas do naipe escolhido.
*
*  $EP Parâmetros
*		ixIndiceAtual - indice do vetor de cartas a partir de onde a função deve preencher
*		szNaipe - Naipe a ser preenchido
*
*  $FV tipo retornado
*		Se executou corretamente, retorna COR_CondRetOK .
*		Se ocorreu algum erro ao criar a carta, retorna COR_CondRetErro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
***********************************************************************/

COR_tpCondRet PreencherNaipe( int ixIndiceAtual, char * szNaipe ){

     int valor, ixIndice;

	 ixIndice = ixIndiceAtual;
	/*Preenche o baralho com cartas de um naipe*/
	 for( valor=1; valor <= 13; valor++ ) {
		vtBaralho[ixIndice] = PCRT_CriarCarta(valor, szNaipe);
		if(vtBaralho[ixIndice] == NULL) {
			return  COR_CondRetErro; 
		}
		ixIndice++;
	 }

	 return COR_CondRetOK;
}/* Fim função: BAR  -Preencher cartas de um naipe */


/********** Fim do módulo de implementação: BAR Baralho **********/
