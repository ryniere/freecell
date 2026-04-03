#if ! defined( Gerenciador_ )
#define Gerenciador_

/***************************************************************************
* 
*  $MCD Módulo de definição: GER Gerenciador
*
*  Arquivo gerado:              GERENCIADOR.H
*  Letras identificadoras:      GER
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  $ED Descrição do módulo
*
*  Implementa funções abstratas usando as interfaces dos módulos referentes as estruturas físicas do jogo FREECELL.
***************************************************************************/

#include <stdio.h>

#if defined( Gerenciador_OWN )
   #define Gerenciador_EXT
#else
   #define Gerenciador_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: GER Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do gerenciador
*
***********************************************************************/

   typedef enum {

         GER_CondRetOK ,
               /* Concluiu corretamente */

	     GER_CondRetAtoProibido,
			  /*  Ato não permitido de acordo com as normas do jogo*/

		 GER_CondRetErroParametros,
		      /* Parâmetros recebidos pela função não condizem com os valores esperados*/

		 GER_CondRetErroArquivo,
			   /* Erro ao preencher célula */

		 GER_CondRetErro,
			   /* Erro ao preencher célula */

   }GER_tpCondRet;


   typedef enum {
		
	   GER_LocalColunaAleatoria = 1,
			/* Tipo de local movido: Coluna aleatória */

	   GER_LocalColunaBase,
	   /* Tipo de local movido: Coluna Base */

	   GER_LocalCelulaTemporaria,
	   /* Tipo de local movido: Coluna Temporaria */

	   GER_LocalInexistente,
	   /* Tipo de local inexistente */

   }GER_tpLocalMovido;


/***********************************************************************
*
*  $FC Função: GER  &Iniciar Jogo
*
*  $ED Descrição da função
*    Interage com o usuário perguntando se ele deseja iniciar um novo jogo ou recuparar o último jogo salvo.
*
*  $EP Parâmetros
*		iRecuperarJogo - 
*			deve assumir o valor 1 para resgatar o último jogo salvo
*			deve assumir o valor 0 para carregar um novo jogo.
*
*  $FV tipo retornado
*		Se executou corretamente retorna GER_CondRetOK.
*		Se ocorreu algum erro, retorna GER_CondRetErro;
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   GER_tpCondRet GER_IniciarJogo(int iRecuperarJogo);


/***********************************************************************
*
*  $FC Função: GER  &Encerrar Jogo
*
*  $ED Descrição da função
*     Interage com o usuário perguntando se o jogo deve ser salvo
*     e desaloca todas as estruturas usadas durante o jogo.
*     
*  $EP Parâmetros
*		Não tem parâmetros.
*
*  $FV tipo retornado
*		Se executou corretamente retorna GER_CondRetOK.
*		Se ocorreu algum erro, retorna GER_CondRetErro;
*
*     Não será dada mais informação quanto ao problema ocorrido.
*      
***********************************************************************/

   GER_tpCondRet GER_EncerrarJogo(char cSalvarJogo);

/***********************************************************************
*
*  $FC Função: GER  &Mover Carta
*
*  $ED Descrição da função
*     Move cartas entre de uma coluna(ou célula) para outra coluna(ou célula).
*
*  $EP Parâmetros
*		GER_tpLocalMovido localOrigem - indicação do tipo de local onde a carta a ser movida se encontra.
*
*		GER_tpLocalMovido localDestino - indicação do tipo de local para onde a carta deve ser movida.
*
*		void* (*InserirCarta)(void*) - ponteiro para a função que insere a última (ou única) carta em uma coluna
*				(célula), retornar uma condição de retorno.
*
*		ixColunaOrigem - índice da coluna aleatória da qual se deseja mover a carta
*       (pode variar de 1 a 8).
*
*		ixColunaDestino - índice da coluna aleatória para qual a carta deve ser movida
*       (pode variar de 1 a 8).
*
*  $FV tipo retornado
*		Se executou corretamente retorna GER_CondRetOK .
*		Se não é permitido mover a carta, retorna GER_CondRetAtoProibido.
*		Se ocorreu qualquer outro tipo de erro, retorna GER_CondRetErro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

GER_tpCondRet GER_MoverCarta( 
				GER_tpLocalMovido localOrigem, 
				GER_tpLocalMovido localDestino, 
				int ixColunaOrigem, 
				int ixColunaDestino);

/***********************************************************************
*
*  $FC Função: GER  &Atualizar tela
*
*  $ED Descrição da função
*		Imprime na tela a configuração atual do jogo.
*     
*  $EP Parâmetros
*		Não tem parâmetros.
*
*  $FV tipo retornado
*		Se executou corretamente retorna GER_CondRetOK.
*		Se ocorreu algum erro, retorna GER_CondRetErro;
*
*     Não será dada mais informação quanto ao problema ocorrido.
*      
***********************************************************************/

GER_tpCondRet GER_AtualizarTela();

/***********************************************************************
*
*  $FC Função: GER  &Testar Fim Jogo
*
*  $ED Descrição da função
*		Testa se todas as colunas base estão completas e o fim do jogo foi atingido
*     
*  $EP Parâmetros
*		Não tem parâmetros.
*
*  $FV tipo retornado
*		Se o fim do jogo foi atingido, retorna GER_CondRetOK.
*		Se ocorreu algum erro ou não é o fim do jogo, retorna GER_CondRetErro;
*
*     Não será dada mais informação quanto ao problema ocorrido.
*      
***********************************************************************/

 GER_tpCondRet GER_TestarFimJogo();

/***********************************************************************
*
*  $FC Função: GER  &Exibir Regras
*
*  $ED Descrição da função
*		Exibe as regras de uso dos comandos do jogo
*     
*  $EP Parâmetros
*		Não tem parâmetros.
*
*  $FV tipo retornado
*		não retorna nada.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*      
***********************************************************************/

 void GER_ExibirRegras();

 /***********************************************************************
*
*  $FC Função: GER  &Obter Local Movido
*
*  $ED Descrição da função
*		Obtem o LocalMovido através de um vetor de char
*     
*  $EP Parâmetros
*		szLocalMovido - vetor de char que contém a string correspondente à um local movido.
*		GER_LocalColunaAleatoria = "aleatoria",
*       GER_LocalColunaBase = "base",
*       GER_LocalCelulaTemporaria = "temporaria",
*
*  $FV tipo retornado
*		GER_tpLocalMovido correspondente ao vetor passado como parâmetro.
*		GER_LocalInexistente caso não corresponda à nenhuma string
*
*     Não será dada mais informação quanto ao problema ocorrido.
*      
***********************************************************************/

 GER_tpLocalMovido GER_ObterLocalMovido(char szLocalMovido[]);

/***********************************************************************/

#undef Gerenciador_EXT

/********** Fim do módulo de definição: GER Gerenciador ******************/

#else
#endif