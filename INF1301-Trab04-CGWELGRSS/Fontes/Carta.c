/***************************************************************************
*  $MCI Módulo de implementação: CRT Carta
*
*  Arquivo gerado:              Carta.c
*  Letras identificadoras:      CRT
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Carta_OWN
#include "Carta.h"
#undef Carta_OWN

#define PrivilegioCarta_OWN
#include "PrivilegioCarta.h"
#undef PrivilegioCarta_OWN

const char* CRT_STRING_COPAS = "copas";
const char* CRT_STRING_ESPADAS = "espadas";
const char* CRT_STRING_OUROS = "ouros";
const char* CRT_STRING_PAUS = "paus";


/***********************************************************************
*
*  $TC Tipo de dados: CRT Carta do baralho
*
*
***********************************************************************/

struct tgCarta {
	int iValor;
	char* szNaipe;
	int icodNome;
};


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: CRT  &Criar Carta
*  ****/

CRT_ptpCarta PCRT_CriarCarta(int valor, char* szNaipe)
{

	CRT_ptpCarta pCarta = (CRT_ptpCarta)malloc( sizeof(struct tgCarta) );

	if( (szNaipe == NULL) || ( (strcmp(szNaipe, CRT_STRING_COPAS) != 0) && (strcmp(szNaipe, CRT_STRING_ESPADAS) != 0) && (strcmp(szNaipe, CRT_STRING_OUROS) != 0) && (strcmp(szNaipe, CRT_STRING_PAUS) != 0) ) ) {
		return NULL; /* Valor de entrada para Naipe inválido. */	
	}
	if( (valor < 1) | (valor > 13) ) {
		return NULL; /* Valor de entrada para valor inválido. */
	}

	if(pCarta == NULL) {
		return NULL; /* Carta não alocada em memória. */
	}

	pCarta->iValor = valor;
	/* Aloca espaço para string do naipe */
	pCarta->szNaipe = ( char* )malloc( ( strlen( szNaipe ) + 1 ) * sizeof( char ) );
	
	if(pCarta->szNaipe == NULL) {
		return NULL; /* Naipe não alocado em memória. */
	}	
	strcpy(pCarta->szNaipe, szNaipe);	

		if( (valor == 1) || (valor >= 11)) {	/* Neste caso, carta pode ser 
												Ás (A), Valete(J), Dama(Q) ou Rei(K) */
			switch(valor) {
				case 1:
					pCarta->icodNome = 'A';
					break;
				case 11:
					pCarta->icodNome = 'J';
					break;
				case 12:
					pCarta->icodNome = 'Q';
					break;
				case 13:
					pCarta->icodNome = 'K';
					break;
			} 
		} else {
			pCarta->icodNome = valor;	/* Codigo da carta é o próprio valor */
		}

return pCarta;

} /* Fim função: CRT  &Criar Carta */

/***************************************************************************
*
*  Função: CRT  &Destruir Carta
*  ****/

void PCRT_DestruirCarta(CRT_ptpCarta carta)
{
	if(carta != NULL) {
		/*Desaloca o conteúdo da carta*/
		free(carta->szNaipe);
		/*Desaloca a carta*/
		free(carta);
	}
} /* Fim função: CRT  &Destruir Carta */

/***************************************************************************
*
*  Função: CRT  &Imprimir Carta
*  ****/

COR_tpCondRet CRT_ImprimirCarta(CRT_ptpCarta carta)
{
	if(carta == NULL) {
		return COR_CondRetErro;
	}

	if( (carta->iValor >= 2) && (carta->iValor < 10) ) { /* Neste caso, codigo equivale
														  a um inteiro */
		printf(" | %d ", carta->icodNome);
	} 
	else if(carta->iValor == 10){

		printf(" |%d ", carta->icodNome);

	}
	else {								/* Neste caso, codigo equivale a um char */
		printf(" | %c ", carta->icodNome);
	}

	if(strcmp(carta->szNaipe,CRT_STRING_ESPADAS)==0){

		printf("- %c|", 6);

	}
	else if(strcmp(carta->szNaipe,CRT_STRING_PAUS)==0) {
		printf("- %c|", 5);

	}
	else if(strcmp(carta->szNaipe,CRT_STRING_COPAS)==0){
		printf("- %c|", 3);

	}
	else{
		printf("- %c|", 4);
	}
	

return COR_CondRetOK; 
} /* Fim função: CRT  &Imprimir Carta */

/***************************************************************************
*
*  Função: CRT  &Obter Naipe Carta
*  ****/

char* CRT_ObterNaipeCarta(CRT_ptpCarta pCarta)
{
	if(pCarta == NULL) {
		return NULL;
	}
	return pCarta->szNaipe;

} /* Fim função: CRT  &Obter Naipe Carta */

/***************************************************************************
*
*  Função: CRT  &Obter Valor Carta
*  ****/

int CRT_ObterValorCarta(CRT_ptpCarta pCarta)
{
	if(pCarta == NULL) {
		return 0;
	}
	return pCarta->iValor;

} /* Fim função: CRT  &Obter Valor Carta */

/***************************************************************************
*
*  Função: CRT  &Obter Codigo Carta
*  ****/

int CRT_ObterCodigoCarta(CRT_ptpCarta pCarta)
{
	if(pCarta == NULL) {
		return 0;
	}
	return pCarta->icodNome;

} /* Fim função: CRT  &Obter Codigo Carta */


/********** Fim do módulo de implementação: CRT Carta **********/