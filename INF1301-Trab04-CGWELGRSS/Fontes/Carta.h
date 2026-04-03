#if ! defined( Carta_ )
#define Carta_
/***************************************************************************
*
*  $MCD Módulo de definição: CRT Carta
*
*  Arquivo gerado:              Carta.h
*  Letras identificadoras:      CRT
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  $ED Descrição do módulo
*
*	  Possui um tipo de dados ptpCarta que contém os campos Valor, Naipe e Nome.
*	  Este módulo permite a utilização deste tipo de dados através de sua criação e preenchimento.
*	  O campo Valor de cada carta pode variar entre 1 e 13.
*	  Os naipes podem ser: copas, espadas, paus e ouros.
*	  Os codigos estão relacionados as cartas que tem letras como símbolos, como o ÁS.
***************************************************************************/

#include "CONDICAO_RETORNO.H"

#if defined( Carta_OWN )
   #define Carta_EXT
#else
   #define Carta_EXT extern
#endif

/* Declarações exportadas pelo módulo */

typedef struct tgCarta * CRT_ptpCarta;

/***********************************************************************
*
*  $FC Função: CRT  &Imprimir Carta
*
*  $ED Descrição da função
*		A função imprime o valor da carta recebida.	
*
*  $EP Parâmetros
*		carta - ponteiro para a estrutura carta a ser impressa.
* 
*  $FV tipo retornado
*		Se executou corretamente retorna COR_CondRetOK .
*		Se ocorreu algum erro, a função retornará COR_CondRetErro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
*
***********************************************************************/

COR_tpCondRet CRT_ImprimirCarta(CRT_ptpCarta carta);


/***********************************************************************
*
*  $FC Função: CRT  &ObterNaipeCarta
*
*  $ED Descrição da função
*		A função obtêm o naipe da carta recebida.	
*
*  $EP Parâmetros
*		carta - ponteiro para a estrutura carta a ser impressa.
*
*  $FV Tipo retornado
*		Ponteiro para a string que representa o naipe.
*		NULL caso a carta seja não exista.
*
*
***********************************************************************/

char* CRT_ObterNaipeCarta(CRT_ptpCarta carta);

/***********************************************************************
*
*  $FC Função: CRT  &ObterValorCarta
*
*  $ED Descrição da função
*		A função obtêm o valor da carta recebida.	
*
*  $EP Parâmetros
*		carta - ponteiro para a estrutura carta a ser impressa.
*
*  $FV Tipo retornado
*		Inteiro que representa o valor da carta.
*		Zero caso a carta seja não exista.
*
*
***********************************************************************/

int CRT_ObterValorCarta( CRT_ptpCarta carta);

/***********************************************************************
*
*  $FC Função: CRT  &ObterCodigoCarta
*
*  $ED Descrição da função
*		A função obtêm o codigo da carta recebida.	
*
*  $EP Parâmetros
*		carta - ponteiro para a estrutura carta a ser impressa.
*
*  $FV Tipo retornado
*		Inteiro que representa o codigo da carta.
*		Zero caso a carta seja não exista.
*
*
***********************************************************************/

int CRT_ObterCodigoCarta( CRT_ptpCarta carta);


#undef Carta_EXT

/********** Fim do módulo de definição: CRT Carta ******************/

#else
#endif