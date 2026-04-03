#if ! defined( TratamentoFalha_ )
#define TratamentoFalha__

/***************************************************************************
* 
*  $MCD Módulo de definição: TRF Tratamento de Falhas
*
*  Arquivo gerado:              TRATAMENTO_FALHA.H
*  Letras identificadoras:      TRF
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  $ED Descrição do módulo
*
*	Possui uma lista de dados criada apenas em modo DEBUG que contem os ponteiros para 
*   todas as estruturas de dados usadas no software.
*	Possui funções de tratamento de erro que buscam o contorno de eventuais erros ocorridos
*	durante a execução do programa.
***************************************************************************/
#include "Lista.h"

#if defined( TratamentoFalha__OWN )
#define TratamentoFalha_EXT
#else
#define TratamentoFalha_EXT extern
#endif

/***********************************************************************
*
*  $FC Função: TRF &TratarPonteiroNuloLista
*
*  $ED Descrição da função
*		A função trata a ocorrência de um ponteiro nulo em algum ponteiro de lista
*	alocando uma nova lista para este ponteiro.
*
*  $EP Parâmetros
*		pLista ponteiro da lista nula.
*
*  $FV tipo retornado
*		Não há retorno.
*
***********************************************************************/

void TRF_TratarPonteiroNuloLista( LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: TRF &  PreencherListaAncora
*
*  $ED Descrição da função
*		A função preenche uma lista âncora que auxilia no desenvolvimento da estrutura
*		auto verificável possibilitanto o uso de instrumentação no software.
*
*  $EP Parâmetros
*		Nao há parametros
*
*  $FV tipo retornado
*		Não há retorno
*
***********************************************************************/

#ifdef _DEBUG
	void preencherListaAncora();
#endif

/***********************************************************************
*
*  $FC Função: TRF &Abortar Programa
*
*  $ED Descrição da função
*		A função desaloca estruturas alocadas dinamicament e aborta o programa em caso de erro.
*
*  $EP Parâmetros
*		Mensagem - string contendo mensagem sobre o erro ocorrido.
*
*  $FV tipo retornado
*		Não há retorno
*
***********************************************************************/

void TRF_AbortarPrograma( char * mensagem );


#undef TratamentoFalha__EXT

/********** Fim do módulo de definição: TRF Tratamento Falha ******************/

#else
#endif