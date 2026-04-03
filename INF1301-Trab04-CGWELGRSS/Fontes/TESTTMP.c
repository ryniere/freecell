/***************************************************************************
*  $MCI Módulo de implementação: TTMP Teste celulas temporarias
*
*  Arquivo gerado:              TESTTMP.c
*  Letras identificadoras:      TTMP
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
#include	"CELULA_TEMPORARIA.h"
#include    "PrivilegioCarta.h"


static const char DESTRUIR_CELULAS_TEMP_CMD			    [ ] = "=destruircelulastemp";
static const char CRIAR_CELULAS_TEMP_CMD		        [ ] = "=criarcelulastemp";
static const char INSERIR_CARTA_CELULA_TEMP_CMD			[ ] = "=inserircartacelulatemp";
static const char RETIRAR_CARTA_CELULA_TEMP_CMD			[ ] = "=retirarcartacelulatemp";
static const char IMPRIMIR_CELULAS_TEMP_CMD				[ ] = "=imprimircelulastemp";
static const char OBTER_CARTA_CELULAS_TEMP_CMD			[ ] = "=obtercartacelulastemp";
static const char RESET_CARTAS_CMD                      [ ] = "=resetcartas"; 


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_STRING_NAIPES	8

#define DIM_VT_CARTA  15

CRT_ptpCarta vtCartas[ DIM_VT_CARTA ] ;


/***********************************************************************
*
*  $FC Função: TTMP &Testar celulas temporarias
*
*     Comandos disponíveis:
*
*		=resetcartas
*		=destruircelulastemp			CondRetEsp
*		=criarcelulastemp				CondRetEsp
*		=inserircartacelulatemp			iValor szNaipe ixIndiceCarta ixIndice CondRetEsp 
*		=retirarcartacelulatemp			iPosicao ValEsp
*		=imprimircelulatemp				CondRetEsp
*		=obtercartacelulastemp			ixIndice CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int numLidos   = -1 ,
          CondRetEsp = -1,
		  iValor = -1, 
		  iPosicao = -1,
		  ixIndiceCarta = -1,
		  ixIndice = -1;

	  int i;

	  char szNaipe[DIM_STRING_NAIPES];
      TST_tpCondRet CondRet ;

	  int ValEsp = -1 ;
	  CRT_ptpCarta pCartaTeste;

	  /* Efetuar reset das cartas criada para o teste do modulo celulas temporarias  */
	  if ( strcmp( ComandoTeste , RESET_CARTAS_CMD ) == 0 )
	  {

		  for( i = 0 ; i < DIM_VT_CARTA ; i++ )
		  {
			  PCRT_DestruirCarta(vtCartas[i]);
			  vtCartas[ i ] = NULL ;
		  } /* for */

		  return TST_CondRetOK ;

	  } /* fim ativa: Efetuar reset das cartas criada para o teste do modulo celulas temporarias */


      /* Testar destruir celulas temporarias  */
	  else if ( strcmp( ComandoTeste , DESTRUIR_CELULAS_TEMP_CMD	 ) == 0 )
         {
			numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;

			if ( ( numLidos != 1 ))
			{
				return TST_CondRetParm ;
			} /* if */

			return TST_CompararInt( CondRetEsp , TMP_DestruirCelulasTemporarias() ,
				"Condicao de retorno errada ao destruir lista." ) ;

         } /* fim ativa: Testar destruir celulas temporarias */

      /* Testar CriarCelulaTemp */
		 if ( strcmp( ComandoTeste , CRIAR_CELULAS_TEMP_CMD ) == 0 )
         {
				numLidos = LER_LerParametros( "i", &CondRetEsp ) ;
			    if ( numLidos != 1 )
				{
					return TST_CondRetParm ;
				}	 /* if */

				
				CondRet = TMP_CriarCelulasTemp();
				
				return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao criar celulas." ) ;
		 } /* fim ativa: Testar CriarCelulaTemp */

      /* Testar Inserir Carta Celula Temp */

         else if ( strcmp( ComandoTeste , INSERIR_CARTA_CELULA_TEMP_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "isiii" ,
                       &iValor , szNaipe, &ixIndiceCarta, &ixIndice, &CondRetEsp ) ;

			if ( ( numLidos != 5 ) || ( szNaipe==NULL )
				||( iValor<=0 ) || ( iValor>=14 ) || 
				( ixIndiceCarta <  0 ) || ( ixIndiceCarta >= DIM_VT_CARTA ) || (ixIndice < 1) 
				  || (ixIndice > 4))
			{
				return TST_CondRetParm ;
			} /* if */

			vtCartas[ ixIndiceCarta ] = PCRT_CriarCarta( iValor, szNaipe );
			CondRet = TMP_InserirCartaCelulaTemp( vtCartas[ ixIndiceCarta ], ixIndice );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir carta." ) ;

         } /* fim ativa: Inserir Carta Celula Temp */

		 /* Testar Retirar Carta celula Temp */

         else if ( strcmp( ComandoTeste , RETIRAR_CARTA_CELULA_TEMP_CMD	 ) == 0 )
         {
			numLidos = LER_LerParametros( "ii" ,
						&iPosicao , &ValEsp ) ;

            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
			
			pCartaTeste = TMP_RetirarCartaCelulaTemp( iPosicao );

			if ( ValEsp == 0 )
            {
				return TST_CompararPonteiroNulo( 0, pCartaTeste, 
							"Devia retornar ponteiro nulo." ) ;
            } 
						
            return TST_CompararPonteiroNulo( 1, pCartaTeste, 
						"Devia retornar ponteiro nao nulo." ) ;

         } /* fim ativa: Testar retirar carta celula temp */

      		 /* Testar imprimir celulas temporarias */
		 else if ( strcmp( ComandoTeste , IMPRIMIR_CELULAS_TEMP_CMD ) == 0 ) {
			
			numLidos = LER_LerParametros( "i",&CondRetEsp ) ;
			
            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            }
			
			CondRet = TMP_ImprimirCelulasTemporarias();
            
            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao imprimir celulas temporarias." ) ;

         } /* fim ativa: Testar imprimir celulas temporarias */

		  /* Testar obter carta celulas temporarias */
		 else if ( strcmp( ComandoTeste , OBTER_CARTA_CELULAS_TEMP_CMD ) == 0 ) {
			
			numLidos = LER_LerParametros( "ii", &ixIndice, &CondRetEsp ) ;
			
            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            }
			
			pCartaTeste = TMP_ObterCartaCelulaTemporaria( ixIndice );
            
            if ( CondRetEsp == 0 )
            {
				return TST_CompararPonteiroNulo( 0, pCartaTeste, 
							"Devia retornar ponteiro nulo." ) ;
            } 
						
            return TST_CompararPonteiroNulo( 1, pCartaTeste, 
						"Devia retornar ponteiro nao nulo." ) ;

         } /* fim ativa: Testar obter carta celulas temporarias */

		 return TST_CondRetNaoConhec ;

   }/* Fim função: TTMP &Testar Celulas Temporarias */



/********** Fim do módulo de implementação: TTMP Teste de Celulas Temporarias **********/