#if ! defined( CelulaTemp_ )
#define CelulaTemp_

/***************************************************************************
* 
*  $MCD Módulo de definição: TMP CelulaTemporaria
*
*  Arquivo gerado:              CELULA_TEMPORARIA.H
*  Letras identificadoras:      TMP
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  $ED Descrição do módulo
*
*	Contém um vetor de 4 endereços de carta, o qual é esternalizado pelo módulo.
*  Este módulo permite o preenchimento e retirada de elementos deste vetor através 
*  das funções de inserção e retirada de cartas.
***************************************************************************/

#include <stdio.h>
#include "Carta.h"
#include "Lista.h"

#if defined( CelulaTemp_OWN )
#define CelulaTemp_EXT
#else
#define CelulaTemp_EXT extern
#endif

#define QTD_CELULAS_TEMPORARIAS 4

/* Declarações exportadas pelo módulo */

LIS_tppLista TMP_celulaTemporaria;

/***********************************************************************
*
*  $FC Função: TMP  &Criar Células Temporárias
*
*  $ED Descrição da função
*		A função CriarCartaTemp preenche os campos do vetor de células temporárias
*	com o valor que representa VAZIO (NULL).
*
*  $EP Parâmetros
*		Não há parâmetros
*
*  $FV tipo retornado
*		COR_CondRetOK, se as celulas foram criadas corretamente
*		COR_CondRetErro, se ocorreu algum problema ao criar celulas
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet TMP_CriarCelulasTemp();

/***********************************************************************
*
*  $FC Função: TMP  &Inserir Carta Temporária
*
*  $ED Descrição da função
*		A função InserirCartaTemp procura uma célula temporária livre e a preenche
*	com o endereço de carta recebido.
*
*  $EP Parâmetros
*		pCarta - ponteiro para a Carta que deve ser inserida.
*		ixIndice - indice indicando a celula temporaria onde será inserida a carta
*
*  $FV tipo retornado
*		Se executou corretamente retorna COR_CondRetOK .
*		Se todas as células estão preenchidas, retorna COR_CondRetAtoProibido.
*		Se ocorreu outro tipo de problema, retorna COR_CondRetErro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet TMP_InserirCartaCelulaTemp( CRT_ptpCarta pCarta, int ixIndice );


/***********************************************************************
*
*  $FC Função: TMP  &Retirar Carta Temporária
*
*  $ED Descrição da função
*		A função RetirarCartaTemp retira a carta da posição recebida
*
*  $EP Parâmetros
*		iposicao - indice indicando qual carta deve ser retirada
*
*  $FV tipo retornado
*		Ponteiro para a carta retirada
*		Caso, seja recebido um valor invalido como indice ou a celula
*		esteja vazia, retorna NULL
*
***********************************************************************/

CRT_ptpCarta TMP_RetirarCartaCelulaTemp( int iposicao );


/***********************************************************************
*
*  $FC Função: TMP  &ImprimirCelulasTemporarias
*
*  $ED Descrição da função
*		A função InprimeCelulasTemporarias imprime o valor das cartas contida 
*	no vetor de células temporárias.
*
*  $EP Parâmetros
*		Nao há parametros.
*
*  $FV tipo retornado
*		COR_CondRetOK, se celulas foram impressas corretamente.
*		COR_CondRetErro, se não foram impressas todas as celulas.
*
***********************************************************************/

COR_tpCondRet TMP_ImprimirCelulasTemporarias();

/***************************************************************************
*
*  Função: TMP  &Destruir Celulas Temporarias
* 
*  $ED Descrição da função
*		A função destroi a lista de celulas temporarias, 
*		liberando todos seus elementos.
*
*  $EP Parâmetros
*		Nao há parametros.
*
*  $FV tipo retornado
*		COR_CondRetOK se celulas foram destruidas corretamente
*		COR_CondRetErro se ocorreu algum problema ao destruir celulas
*
***********************************************************************/

COR_tpCondRet TMP_DestruirCelulasTemporarias();

/***********************************************************************
*
*  $FC Função: TMP  &Obter Carta Celula Temporaria
*
*  $ED Descrição da função
*		A função obtém o endereço da carta corrente da celula temporaria.
*
*  $EP Parâmetros
*		ixIndiceCelula - representa o índice da celula na qual se quer obter a carta.
*
*  $FV tipo retornado
*		COR_CondRetOK, se a carta foi obtida corretamente.
*		COR_CondRetErro, se ocorreu algum erro.
*
***********************************************************************/

CRT_ptpCarta TMP_ObterCartaCelulaTemporaria( int ixIndiceCelula );


#undef CelulaTemp_EXT

/********** Fim do módulo de definição: TMP Celula Temporaria ******************/

#else
#endif