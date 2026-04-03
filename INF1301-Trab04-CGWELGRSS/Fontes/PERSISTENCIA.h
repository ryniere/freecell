#if ! defined( Persistencia_ )
#define Persistencia__

/***************************************************************************
* 
*  $MCD Módulo de definição: PERS Persistencia
*
*  Arquivo gerado:             PERSISTENCIA.h
*  Letras identificadoras:     PERS
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  $ED Descrição do módulo
*
*	Este módulo é responsável por salvar e carregar um jogo.
***************************************************************************/

#include <stdio.h>
#include "Carta.h"
#include "Lista.h"

#if defined( Persistencia__OWN )
#define Persistencia__EXT
#else
#define Persistencia__EXT extern
#endif



/***********************************************************************
*
*  $FC Função: PERS  &Salvar Jogo
*
*  $ED Descrição da função
*		A função salvar jogo armazena todas as cartas de um jogo em um arquivo: JogoSalvo.txt 
*
*  $EP Parâmetros
*		Não há parâmetros
*
*  $FV tipo retornado
*		PERS_CondRetErro, se houve algum problema ao gravar cartas
*		PERS_CondRetOK, se o jogo foi salvo corretamente
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet PERS_SalvarJogo();

/***********************************************************************
*
*  $FC Função: PERS  &Carregar Jogo
*
*  $ED Descrição da função
*		A função carrega um jogo salvo em um arquivo
*
*  $EP Parâmetros
*		Não há parâmetros
*
*  $FV tipo retornado
*		PERS_CondRetErro, se não foi possível carregar o jogo.
*		PERS_CondRetOK, se o jogo foi carregado corretamente.
*
***********************************************************************/

COR_tpCondRet PERS_CarregarJogo();


/***********************************************************************
*
*  $FC Função: PERS  &Verificar Jogo Salvo
*
*  $ED Descrição da função
*		A função verifica se um jogo salvo existe ou não
*
*  $EP Parâmetros
*		Não há parâmetros
*
*  $FV tipo retornado
*		PERS_CondRetJogoSalvoNaoExiste, o não existe o jogo;
*		PERS_CondRetJogoSalvoExiste, se existe o jogo.
*
***********************************************************************/

int PERS_VerificarJogoSalvo();

/***********************************************************************
*
*  $FC Função: PERS  &Alterar nome do Arquivo
*
*  $ED Descrição da função
*		A função altera o nome do arquivo onde se salva o jogo
*
*  $EP Parâmetros
*		szNomeArquivo - Novo nome do arquivo
*
*  $FV tipo retornado
*		PERS_CondRetErro, se ocorreu algum problema ao alterar nome arquivo.
*		PERS_CondRetOK, se nome do arquivo foi alterado corretamente.
*
***********************************************************************/

COR_tpCondRet PERS_AlterarNomeArquivo(char * szNomeArquivo);

/***********************************************************************
*
*  $FC Função: PERS &Destruir Referencia Jogo Salvo
*
*  $ED Descrição da função
*		A função desaloca espaço reservado para string com o nome do jogo salvo;
*
*  $EP Parâmetros
*		Nao há parametros
*
*  $FV tipo retornado
*		Nao há retorno
*
***********************************************************************/

void PERS_DestruirReferenciaJogoSalvo();


#undef Persistencia__EXT

/********** Fim do módulo de definição: PERS Persistencia ******************/

#else
#endif