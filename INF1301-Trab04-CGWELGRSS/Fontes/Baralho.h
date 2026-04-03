#if ! defined( Baralho_ )
#define Baralho_

/***************************************************************************
*
*  $MCD Módulo de definição: BAR Baralho
*
*  Arquivo gerado:              Baralho.h
*  Letras identificadoras:      BAR
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  $ED Descrição do módulo
*
*	  Possui um vetor de endereços de cartas. Este vetor possui 52 elementos.
*	  Este módulo agrega o módulo Carta, portanto é o único a criar cartas.
*
***************************************************************************/

#include "Carta.h"


#if defined( Baralho_OWN )
   #define Baralho_EXT
#else
   #define Baralho_EXT extern
#endif

/* Declarações importadas pelo módulo */

extern  char* CRT_STRING_COPAS;
extern  char* CRT_STRING_ESPADAS;
extern  char* CRT_STRING_OUROS;
extern  char* CRT_STRING_PAUS;

/* Declarações exportadas pelo módulo */

#define QTD_CARTAS 52

CRT_ptpCarta vtBaralho[QTD_CARTAS];

/***********************************************************************
*
*  $FC Função: BAR  &Criar baralho
*
*  $ED Descrição da função
*		A função CriarBaralho cria 13 cartas de cada naipe e as insere no vetor baralho.	
*
*  $EP Parâmetros
*		Não tem parâmetros.
*
*  $FV tipo retornado
*		Se executou corretamente retorna COR_CondRetOK .
*		Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*       a função retornará COR_CondRetErro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   COR_tpCondRet BAR_CriarBaralho();

/***********************************************************************
*
*  $FC Função: BAR  &Embaralhar
*
*  $ED Descrição da função
*		A função Embaralhar redistribui de forma aleatória as cartas do baralho.	
*
*  $EP Parâmetros
*		Não há parâmetros.
*
*  $FV tipo retornado
*		Se executou corretamente retorna COR_CondRetOK .
*		Se ocorreu algum erro a função retornará COR_CondRetErro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet BAR_Embaralhar();

/***********************************************************************
*
*  $FC Função: BAR  &DestruirBaralho
*
*  $ED Descrição da função
*		A função DestruirBaralho desaloca todas as estruturas contidas no baralho.	
*
*  $EP Parâmetros
*		Não há parâmetros.
*
*   $FV tipo retornado
*		Se executou corretamente retorna COR_CondRetOK .
*		Se ocorreu algum erro a função retornará COR_CondRetErro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet BAR_DestruirBaralho();

/***********************************************************************
*
*  $FC Função: BAR  &Buscar Carta Baralho Ordenado
*
*  $ED Descrição da função
*		A função Buscar Carta Baralho Ordenado busca uma determinada carta no baralho
*
*  $EP Parâmetros
*		Ivalor - Valor da carta
*       szNaipe - Naipe da carta  
*
*   $FV tipo retornado
*		Se executou corretamente retorna o ponteiro para a carta desejada.
*		Se ocorreu algum erro a função retornará NULL.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

CRT_ptpCarta BAR_BuscarCartaBaralhoOrdenado( int iValor, char * szNaipe );

#undef Baralho_EXT

/********** Fim do módulo de definição: BAR Baralho **********/

#else
#endif