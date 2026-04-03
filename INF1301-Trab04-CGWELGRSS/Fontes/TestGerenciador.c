/***************************************************************************
*  $MCI Módulo de implementação: TGER Teste gerenciador
*
*  Arquivo gerado:              TestGerenciador.c
*  Letras identificadoras:      TGER
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Baralho.h"
#include    "PrivilegioCarta.h"
#include	"Persistencia.h"
#include	"Gerenciador.h"

#include "CELULA_TEMPORARIA.H"
#include "COLUNA_BASE.H"
#include "COLUNAS_ALEATORIAS.H"

static const char INICIAR_JOGO_CMD					    [ ] = "=iniciarjogo";
static const char ENCERRAR_JOGO_CMD				        [ ] = "=encerrarjogo";
static const char MOVER_CARTA_CMD						[ ] = "=movercarta";
static const char ATUALIZAR_TELA_CMD					[ ] = "=atualizartela";
static const char TESTAR_FIM_JOGO_CMD					[ ] = "=testarfimjogo";
static const char OBTER_LOCAL_MOVIDO_CMD				[ ] = "=obterlocalmovido";

/* Comandos auxiliares */

static const char ALTERAR_NOME_ARQUIVO_CMD						[ ] = "=alterarnomearquivo";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_STRING_NAIPES	8

#define DIM_VT_CARTA  15

CRT_ptpCarta vtCartas[ DIM_VT_CARTA ] ;

/***********************************************************************
*
*  $FC Função: TGER &Testar gerenciador
*
*  $ED Descrição da função
*
*     Comandos disponíveis:
*
*	=iniciarjogo
*	=encerrarjogo
*	=movercarta
*	=atualizartela
*	=testarfimjogo
*
*	Comandos de funções auxiliares
*
*	=criaraleatorias
*	=inseriraleatoria
*	=criarbases
*	=criartemporarias
*	=criarbaralho
*	
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int numLidos   = -1 ,
          CondRetEsp = -1,
		  iLocalOrigem = -1, 
		  iLocalDestino = -1,
		  iColunaOrigem = -1, 
		  iColunaDestino = -1,
		  iRecuperar = -1;
	  
	  char szNomeArquivo[30];
	  char szLocalMovido[10];
	  char cSalvarJogoObtido;

      int iCondRet ;

	  
	  /* Testar iniciar jogo */
	  if ( strcmp( ComandoTeste , INICIAR_JOGO_CMD	 ) == 0 )
         {
			numLidos = LER_LerParametros( "ii" , &iRecuperar,
										 &CondRetEsp ) ;

			if ( ( numLidos != 2 ))
			{
				return TST_CondRetParm ;
			} /* if */

			return TST_CompararInt( CondRetEsp , GER_IniciarJogo(iRecuperar) ,
				"Condicao de retorno errada ao iniciar jogo." ) ;

         } /* fim ativa: Testar iniciar jogo */

			/* Testar Encerrar Jogo */
		 else if ( strcmp( ComandoTeste , ENCERRAR_JOGO_CMD ) == 0 )
         {
				numLidos = LER_LerParametros( "ci", &cSalvarJogoObtido, &CondRetEsp ) ;

			    if ( numLidos != 2 )
				{
					return TST_CondRetParm ;
				}	 /* if */

				
				iCondRet = GER_EncerrarJogo(cSalvarJogoObtido);
				
				return TST_CompararInt( CondRetEsp , iCondRet ,
                     "Condicao de retorno errada ao encerrar jogo." ) ;
		 } /* fim ativa: Testar encerrar Jogo */

      /* Testar Mover Carta */

         else if ( strcmp( ComandoTeste , MOVER_CARTA_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "iiiii" , &iLocalOrigem , 
											&iLocalDestino, &iColunaOrigem, &iColunaDestino, &CondRetEsp ) ;
			

			if ( ( numLidos != 5 ) || ((iLocalOrigem < 1 || iLocalOrigem > 3 ))
				||( iLocalDestino < 1 ) || ( iLocalDestino > 3) || 
				(iColunaOrigem <  1 ) || ( iColunaOrigem > 8  ) || (iColunaDestino < 1) 
				  || (iColunaDestino > 8))
			{
				return TST_CondRetParm ;
			} /* if */

			iCondRet = GER_MoverCarta( iLocalOrigem, iLocalDestino, 
										iColunaOrigem, iColunaDestino);

            return TST_CompararInt( CondRetEsp , iCondRet ,
                     "Condicao de retorno errada ao mover carta." ) ;

         } /* fim ativa: Mover Carta */

		 /* Testar Atualizar Tela */

         else if ( strcmp( ComandoTeste , ATUALIZAR_TELA_CMD	 ) == 0 )
         {
			numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
			
			return TST_CompararInt( CondRetEsp , GER_AtualizarTela() ,
                     "Condicao de retorno errada ao atualizar tela." ) ;

         } /* fim ativa: Testar Atualizar Tela */

      		 /* Testar 'testar fim jogo' */
		 else if ( strcmp( ComandoTeste , TESTAR_FIM_JOGO_CMD ) == 0 ) {
			
			numLidos = LER_LerParametros( "i",&CondRetEsp ) ;
			
            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            }
			
			iCondRet = GER_TestarFimJogo();
            
            return TST_CompararInt( CondRetEsp , iCondRet ,
                     "Condicao de retorno errada ao testar fim do jogo." ) ;

         } /* fim ativa: Testar 'testar fim jogo' */

		 /* Testar 'Obter Local Movido' */
		 else if ( strcmp( ComandoTeste ,OBTER_LOCAL_MOVIDO_CMD ) == 0 ) {
			
			numLidos = LER_LerParametros( "si",szLocalMovido, &CondRetEsp ) ;
			
            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            }
			
			iCondRet = GER_ObterLocalMovido(szLocalMovido);
            
            return TST_CompararInt( CondRetEsp , iCondRet ,
                     "Condicao de retorno errada ao obter local movido." ) ;

         } /* fim ativa: Testar 'Obter Local Movido' */

		 /* Função auxiliar: CarregarJogoSalvo */
		 else if ( strcmp( ComandoTeste , ALTERAR_NOME_ARQUIVO_CMD ) == 0 ) {
			
			numLidos = LER_LerParametros( "s", szNomeArquivo ) ;
			
            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            }

			PERS_AlterarNomeArquivo(szNomeArquivo);
            
            return 0 ;

         } /* fim ativa: Função auxiliar: Alterar Nome Arquivo */

		 return TST_CondRetNaoConhec ;
   }

/********** Fim do módulo de implementação: TGER Teste Gerenciador **********/