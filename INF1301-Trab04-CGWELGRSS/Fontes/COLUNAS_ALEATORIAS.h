#if ! defined( ColunasAleatorias_ )
#define ColunasAleatorias_

/***************************************************************************
* 
*  $MCD Módulo de definição: CALT Colunas Aleatorias
*
*  Arquivo gerado:              COLUNAS_ALEATORIAS.H
*  Letras identificadoras:      CALT
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  $ED Descrição do módulo
*
*  Manipula listas de endereços de carta, as quais são externalizadas pelo módulo.
*  Este módulo permite o preenchimento e retirada de elementos dessas listas através 
*  das funções de inserção e retirada de cartas.
***************************************************************************/

#include <string.h>
#include <stdio.h>
#include "LISTA.h"
#include "Baralho.h"

#if defined( SequenciaAleatoria_OWN )
   #define SequenciaAleatoria_EXT
#else
   #define SequenciaAleatoria_EXT extern
#endif

/* Declarações exportadas pelo módulo */

LIS_tppLista CALT_coluna1;
LIS_tppLista CALT_coluna2;
LIS_tppLista CALT_coluna3;
LIS_tppLista CALT_coluna4;
LIS_tppLista CALT_coluna5;
LIS_tppLista CALT_coluna6;
LIS_tppLista CALT_coluna7;
LIS_tppLista CALT_coluna8;

/* Declarações importadas pelo módulo */

extern  char* CRT_STRING_COPAS;
extern  char* CRT_STRING_ESPADAS;
extern  char* CRT_STRING_OUROS;
extern  char* CRT_STRING_PAUS;


   /***********************************************************************
*
*  $FC Função: CALT  &Criar Colunas Aleatórias
*
*  $ED Descrição da função
*		A função CriarColunasAleatorias preenche os campos da estrutura de 8 listas com NULL,
*		representando que as colunas estão vazias.
*
*  $EP Parâmetros
*		Não tem parâmetros.
*
*  $FV tipo retornado
*		Se executou corretamente retorna COR_CondRetOK.
*		Se ocorreu algum erro ao criar lista, retorna COR_CondRetErro;
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   COR_tpCondRet CALT_CriarColunasAleatorias();

   /***********************************************************************
   *
   *  $FC Função: CALT  &Destruir Colunas Aleatorias
   *
   *  $ED Descrição da função
   *     Destrói todas as colunas aleatorias.
   *     
   *  $EP Parâmetros
   *		Não tem parâmetros.
   *  
   * 
   *  $FV tipo retornado
   *		Se executou corretamente retorna COR_CondRetOK.
   *		Se ocorreu algum erro ao criar lista, retorna COR_CondRetErro;
   *
   *     Não será dada mais informação quanto ao problema ocorrido.
   *      
   ***********************************************************************/

   COR_tpCondRet CALT_DestruirColunasAleatorias();

/***********************************************************************
*
*  $FC Função: CALT  &Inserir Carta Sequencia Coluna
*
*  $ED Descrição da função
*		Para inserir uma carta em uma sequencia aleatoria é necessario que esta possua o menor 
*		valor seguinte ao da ultima carta da coluna e uma cor diferente.
*		A função InserirCartaSequencia insere uma carta no final de uma lista de cartas,	
*		testando as condições citadas acima.
*
*  $EP Parâmetros
*		pCarta - ponteiro para a Carta que deve ser inserida.
*		ixIndice - Numero da coluna a se inserir a Carta.
*
*  $FV tipo retornado
*		Se executou corretamente retorna CALT_CondRetOK .
*		Se não é permitido inserir a carta, retorna CALT_CondRetAtoProibido.
*		Se ocorreu qualquer outro tipo de erro, retorna CALT_CondRetErro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

	COR_tpCondRet CALT_InserirCartaSequenciaColuna( CRT_ptpCarta pCarta, int ixIndice);

/***********************************************************************
*
*  $FC Função: CALT  &Retirar Carta Sequencia Coluna
*
*  $ED Descrição da função
*		A função RetirarCartaSequencia remove a ultima carta de uma lista de cartas.
*
*  $EP Parâmetros
*		ixIndice - Numero da coluna a se inserir a Carta.
*
*  $FV tipo retornado
*		Ponteiro para a carta removida.
*		NULL, se a lista está vazia. 
*
***********************************************************************/

	CRT_ptpCarta CALT_RetirarCartaSequenciaColuna( int ixIndice);

/***********************************************************************
*
*  $FC Função: CALT  &Imprimir Colunas Aleatorias
*
*  $ED Descrição da função
*		Função para imprimir as cartas das colunas aleatorias.
*
*  $EP Parâmetros
*		Não tem parâmetros
*
*  $FV tipo retornado
*		Se executou corretamente retorna CALT_CondRetOK.
*		Se ocorreu algum erro ao imprimir a coluna, retorna CALT_CondRetErro;
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

	COR_tpCondRet CALT_ImprimirColunasAleatorias();

/***********************************************************************
*
*  $FC Função: CALT  &Preencher Colunas Aleatorias
*
*  $ED Descrição da função
*		Preenche 8 sequencias com cartas embaralhadas do baralho.
*
*  $EP Parâmetros
*		Não há parâmetros
*
*  $FV tipo retornado
*		Se executou corretamente retorna CALT_CondRetOK.
*		Se ocorreu algum erro ao preencher a coluna, retorna CALT_CondRetErro;
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

	COR_tpCondRet CALT_PreencherColunasAleatorias();

/***********************************************************************
*
*  $FC Função: CALT  &Inserir Carta  Coluna
*
*  $ED Descrição da função
*		
*		A função InserirCartaColuna insere uma carta no inicio de uma lista de cartas,
*		essa função só pode ser usada na hora de carregar as colunas de um jogo salvo
*		
*
*  $EP Parâmetros
*		pCarta - ponteiro para a Carta que deve ser inserida.
*		ixIndice - Numero da coluna a se inserir a Carta.
*
*  $FV tipo retornado
*		Se executou corretamente retorna COR_CondRetOK .
*		Se ocorreu qualquer outro tipo de erro, retorna COR_CondRetErro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

	COR_tpCondRet CALT_InserirCartaColuna( CRT_ptpCarta pCarta, int ixIndice);

/***********************************************************************
*
*  $FC Função: CALT  &Obter Carta Coluna Aleatória
*
*  $ED Descrição da função
*		A função obtém o endereço da carta corrente da coluna aleatória.
*
*  $EP Parâmetros
*		ixIndiceColuna - representa o índice da coluna na qual se quer obter a carta.
*
*  $FV tipo retornado
*		se a carta foi obtida corretamente, retorna o ponteiro para a carta.
*		NULL, se ocorreu algum erro.
*
***********************************************************************/

CRT_ptpCarta CALT_ObterCartaColunaAleatoria( int ixIndiceColuna );

/***********************************************************************
*
*  $FC Função: CBSE  &Ir Final Coluna Aleatoria
*
*  $ED Descrição da função
*		A função posiciona o elemento corrente na ultima carta da coluna.
*
*  $EP Parâmetros
*		ixIndiceColuna - representa o índice da coluna na qual se quer obter a carta.
*			copas = 1, espadas = 2, ouros = 3, paus = 4.
*
*  $FV tipo retornado
*		COR_CondRetOK, se executou corretamente.
*		COR_CondRetErro, se o indice correpondente a coluna for invalido.
*
***********************************************************************/

COR_tpCondRet CALT_IrFinalColunaAleatoria( int ixIndiceColuna );

/***********************************************************************
*
*  $FC Função: CBSE  &Avançar Elem Corr Coluna Aleatoria
*
*  $ED Descrição da função
*		A função posiciona o elemento corrente da coluna na posição desejada.
*
*  $EP Parâmetros
*		ixIndiceColuna - representa o índice da coluna na qual se quer obter a carta.
*			copas = 1, espadas = 2, ouros = 3, paus = 4.
*		numElem - o número de elementos a andar.
*
*  $FV tipo retornado
*		COR_CondRetOK, se executou corretamente.
*		COR_CondRetErro, se não foi possivel avançar elemento corrente.
*
*		Não será dada mais informação quanto ao problema ocorrido.
***********************************************************************/

COR_tpCondRet CALT_AvancarElemCorrColunasAleatorias( int ixIndiceColuna, int numElem);


#undef ColunasAleatorias_EXT

/********** Fim do módulo de definição: CALT Colunas Aleatorias ******************/

#else
#endif