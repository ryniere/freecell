/***************************************************************************
*  $MCI Módulo de implementação: TCB Teste coluna Base
*
*  Arquivo gerado:              TEST_COLUNA_BASE.c
*  Letras identificadoras:      TCB
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner e Ryniere Santos Silva
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Coluna_base.h"
#include    "Carta.h"
#include    "PrivilegioCarta.h"

static const char CRIAR_COLUNAS_BASE_CMD			[ ]	= "=criarbase";
static const char INSERIR_CARTA_BASE_CMD			[ ]	= "=inserircartabase";
static const char DESTRUIR_CARTA_BASE_CMD			[ ]	= "=destruirbase";
static const char IMPRIMIR_COLUNAS_BASE_CMD			[ ] = "=imprimirbase";
static const char OBTER_CARTA_COLUNA_BASE_CMD		[ ]	= "=obtercartabase";
static const char IR_FINAL_COLUNA_BASE_CMD			[ ]	= "=irfinalbase";
static const char IR_INICIO_COLUNA_BASE_CMD			[ ] = "=iriniciobase";
static const char AVANCAR_ELEM_CORR_COLUNA_BASE_CMD	[ ] = "=avancarelemcorrbase";
static const char RESET_CARTAS_CMD					[ ] = "=resetcartas";


#define DIM_NAIPE 10

#define DIM_VT_CARTA 15

CRT_ptpCarta  vtCarta[ DIM_VT_CARTA ] ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar Coluna Base
*
*  $ED Descrição da função
*     São usadas as colunas base do módulo testado para inserir uma carta.
*     Podem ser criadas até 10 cartas, identificadas pelos índices 0 a 14

*     Comandos disponíveis:
*
*     =criarbase                  
*     =destruircarta                
*	  =inserircartabase		iValor szNaipe ixIndiceCarta iValorEsp
*     =imprimirbase         iValorEsp
*	  =obtercartabase		ixIndiceColuna CondRetEsp
*	  =irfinalbase			ixIndiceColuna CondRetEsp
*	  =iriniciobase			ixIndiceColuna CondRetEsp
*	  =avancarelemcorrbase	ixIndiceColuna numElem CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int  iNumLidos   = -1;
	  int CondRetEsp = -1;
	  int iValEsp = -1 ;
	  int iValor = -1,
		  ixIndiceCarta = -1;
	  int i;
	  int ixIndiceColuna = -1;
	  int numElem = -1;
	  char szNaipe[ DIM_NAIPE ];

	  CRT_ptpCarta pCartaTeste;


	  /* Efetuar reset das cartas criadas para o teste do modulo Coluna Base */

	  if ( strcmp( ComandoTeste , RESET_CARTAS_CMD ) == 0 )
	  {

		  for( i = 0 ; i < DIM_VT_CARTA ; i++ )
		  {
			  vtCarta[ i ] = NULL ;
		  } /* for */

		  return TST_CondRetOK ;

	  } /* fim ativa: Efetuar reset das cartas criadas para o teste do modulo Coluna Base */

	  /* Testar Destruir Coluna Base */

         else if ( strcmp( ComandoTeste , DESTRUIR_CARTA_BASE_CMD ) == 0 )
         {
  
            return TST_CompararInt( CBSE_DestruirColunasBase() , COR_CondRetOK ,
                         "Erro ao destruir colunas base." ) ;

         } /* fim ativa: Testar Destruir Coluna Base */

      /* Testar Criar Coluna Base */

         else if ( strcmp( ComandoTeste , CRIAR_COLUNAS_BASE_CMD ) == 0 )
         {
            
			return TST_CompararInt( CBSE_CriarColunasBase() , COR_CondRetOK ,
                         "Erro ao criar Colunas Base." ) ;
         } /* fim ativa: Testar Criar Coluna Base */

      /* Testar Inserir Carta em Coluna Base */

         else if ( strcmp( ComandoTeste , INSERIR_CARTA_BASE_CMD ) == 0 )
         {
			
            iNumLidos = LER_LerParametros( "isiii" ,
                       &iValor , szNaipe, &ixIndiceCarta, &ixIndiceColuna, &iValEsp ) ;

            if ( ( iNumLidos != 5 ) || ( iValor <= 0) || ( iValor > 13) || (szNaipe == NULL)|| 
				( ixIndiceCarta<0 ) || ( ixIndiceCarta >= DIM_VT_CARTA ) )
            {
				return TST_CondRetParm;
            } /* if */
         
			vtCarta[ ixIndiceCarta ] = PCRT_CriarCarta(iValor, szNaipe);
        
			if( vtCarta[ ixIndiceCarta ] == NULL ) {

				return TST_CondRetMemoria;

			} else {
				return TST_CompararInt( iValEsp , CBSE_InserirCartaColunasBases(vtCarta[ ixIndiceCarta ], ixIndiceColuna) ,
							"Condição de inserção de carta na base diferente da esperada." );
			}

         } /* fim ativa: Testar Imprimir colunas base */

		 else if ( strcmp( ComandoTeste , IMPRIMIR_COLUNAS_BASE_CMD ) == 0 )
		 {

			 iNumLidos = LER_LerParametros( "i" ,
				 &iValEsp ) ;

			 if ( iNumLidos != 1 )
			 {
				 return TST_CondRetParm;
			 } /* if */

			 return TST_CompararInt( iValEsp , CBSE_ImprimirColunasBases() ,
					 "Condição de impressão das colunas base diferente da esperada." );		

		 } /* fim ativa: Testar Imprimir coluna base */

		 /* Testar obter carta coluna base */
		 else if ( strcmp( ComandoTeste , OBTER_CARTA_COLUNA_BASE_CMD ) == 0 ) {
			
			iNumLidos = LER_LerParametros( "ii", &ixIndiceColuna, &CondRetEsp ) ;
			
            if ( iNumLidos != 2 )
            {
               return TST_CondRetParm ;
            }
			
			pCartaTeste = CBSE_ObterCartaColunaBase( ixIndiceColuna );
            
            if ( CondRetEsp == 0 )
            {
				return TST_CompararPonteiroNulo( 0, pCartaTeste, 
							"Devia retornar ponteiro nulo." ) ;
            } 
						
            return TST_CompararPonteiroNulo( 1, pCartaTeste, 
						"Devia retornar ponteiro nao nulo." ) ;

         } /* fim ativa: Testar obter carta coluna base */

		 /* Testar Ir Inicio Coluna Base */
         else if ( strcmp( ComandoTeste , IR_INICIO_COLUNA_BASE_CMD ) == 0 )
         {
			 iNumLidos = LER_LerParametros( "ii", &ixIndiceColuna, &CondRetEsp ) ;
			
            if ( iNumLidos != 2 )
            {
               return TST_CondRetParm ;
            }
            
			return TST_CompararInt( CBES_IrInicioColunaBase(ixIndiceColuna) , CondRetEsp ,
                         "Erro ao ir inicio Coluna Base." ) ;

         } /* fim ativa: Testar Ir Inicio Coluna Base */

		 /* Testar Ir Final Coluna Base */
         else if ( strcmp( ComandoTeste , IR_FINAL_COLUNA_BASE_CMD ) == 0 )
         {
			 iNumLidos = LER_LerParametros( "ii", &ixIndiceColuna, &CondRetEsp ) ;
			
            if ( iNumLidos != 2 )
            {
               return TST_CondRetParm ;
            }
            
			return TST_CompararInt( CBES_IrFinalColunaBase(ixIndiceColuna) , CondRetEsp ,
                         "Erro ao ir final Coluna Base." ) ;

         } /* fim ativa: Testar Ir Final Coluna Base */

		 /* Testar Avancar Elem Corr Coluna Base */
         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CORR_COLUNA_BASE_CMD ) == 0 )
         {
			 iNumLidos = LER_LerParametros( "iii", &ixIndiceColuna, &numElem, &CondRetEsp ) ;
			
            if ( iNumLidos != 3 )
            {
               return TST_CondRetParm ;
            }
            
			return TST_CompararInt( CBSE_AvancarElemCorrColunaBase(ixIndiceColuna, numElem) , CondRetEsp ,
                         "Erro ao avancar elemento da coluna base." ) ;

         } /* fim ativa: Testar Avancar Elem Corr Coluna Base */

      return TST_CondRetNaoConhec ;

   }/* Fim função: TCB &Testar Colunas Base */

/********** Fim do módulo de implementação: TCB Teste Coluna Base **********/

