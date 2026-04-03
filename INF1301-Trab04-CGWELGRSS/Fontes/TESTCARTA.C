/***************************************************************************
*  $MCI Módulo de implementação: TCAR Teste de Carta
*
*  Arquivo gerado:              TestCARTA.c
*  Letras identificadoras:      TCAR
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

#include    "Carta.h"
#include	"PrivilegioCarta.h"


static const char RESET_CARTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_CARTA_CMD         [ ] = "=criarcarta"     ;
static const char DESTRUIR_CARTA_CMD      [ ] = "=destruircarta"  ;
static const char OBTER_VALOR_CARTA_CMD   [ ] = "=obtervalorcarta"  ;
static const char OBTER_NAIPE_CARTA_CMD   [ ] = "=obternaipecarta"  ;
static const char OBTER_CODIGO_CARTA_CMD  [ ] = "=obtercodigocarta"  ;
static const char IMPRIMIR_CARTA_CMD	  [ ] = "=imprimircarta" ;


#define TRUE  1
#define FALSE 0

/* Valores a serem usados como parâmetros no script */
#define PONTEIRO_NULO     0
#define PONTEIRO_NAO_NULO 1

/* Valores a serem usados como parâmetros no script */
#define OK     0
#define ERRO   1

#define DIM_VT_CARTA   10
#define DIM_VALOR     100

CRT_ptpCarta vtCartas[ DIM_VT_CARTA] ;


/*****  Protótipo das funções encapsuladas pelo módulo  *****/
/***********************************************************************
*
*  $FC Função: TSTG &Comparar Strings Diferentes
*
*  $ED Descrição da função
*     Compara string esperado com string obtido, reportamdo uma falha
*     caso não sejam diferentes. Ambos os strings devem obedecer o
*     padrão C, terminando em zero.
*
*  $EP Parâmetros
*     ValorEsperado  - é um string fornecido como parâmetro do comando
*                      de teste.
*     ValorObtido    - é o string retornado pela função em teste
*     pMensagem      - mensagem explanatória da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado não for diferente do obtido
*     TST_CondRetOK    se os valores forem diferentes
*
***********************************************************************/
static TST_tpCondRet TST_CompararStringsDiferentes(char * ValorEsperado ,
									 char * ValorObtido   ,
									 char * pMensagem  );

/***********************************************************************
*
*  $FC Função: TSTG &Comparar Inteiros Diferentes 
*
*  $ED Descrição da função
*     Compara valor inteiro long esperado com valor inteiro obtido,
*     reportamdo uma falha caso sejam iguais.
*
*  $EP Parâmetros
*     ValorEsperado  - é um valor fornecido como parâmetro do comando
*                      de teste
*     ValorObtido    - é o valor retornado pela função em teste
*     pMensagem      - mensagem explanatória da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado for igual ao obtido
*     TST_CondRetOK    se os valores não forem iguais
*
***********************************************************************/

  static TST_tpCondRet TST_CompararInteirosDiferentes( long   ValorEsperado ,
                                  long   ValorObtido   ,
                                  char * pMensagem       ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar Carta
*
*  $ED Descrição da função
*     Podem ser criadas até 10 cartas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarcarta                   inxCarta
*     =destruircarta                inxCarta
*     =obtervalorcarta				inxCarta  numero  CondretInteiro
*	  =obternaipecarta				inxCarta  string  CondretInteiro
*	  =obtercodigocarta				inxCarta  numero  CondretInteiro
*     =excluircarta                 inxCarta 
*	  =imprimircarta				inxCarta
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxCarta = -1 ,
          iNumLidos   = -1;
		  
      char   StringDado[  DIM_VALOR ] ;
	  int iNumeroDado;
	  int iCodigo;
	  int iValor;
	  char szNaipe[ DIM_VALOR ];
	  char szNaipeAuxiliar[ DIM_VALOR ];

      int iValEsp = -1 ;

      int i ;


      StringDado[ 0 ] = 0 ;


      /* Efetuar reset de teste de carta*/

         if ( strcmp( ComandoTeste , RESET_CARTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_CARTA ; i++ )
            {
				PCRT_DestruirCarta( vtCartas[ i ] );
				vtCartas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarCarta */

         else if ( strcmp( ComandoTeste , CRIAR_CARTA_CMD ) == 0 )
         {
            iNumLidos = LER_LerParametros( "iisi" ,
                       &inxCarta, &iValor, szNaipe, &iValEsp) ;

			if ( ( iNumLidos != 4 ) || (inxCarta < 0) || (inxCarta >= 10) ) {
            
               return TST_CondRetParm ;
            } /* if */

            vtCartas[ inxCarta ] = PCRT_CriarCarta( iValor, szNaipe) ;

			if( iValEsp == PONTEIRO_NULO ) {
				return TST_CompararPonteiroNulo( iValEsp , vtCartas[ inxCarta ] ,
				   "Erro em ponteiro de nova carta."  ) ;
			} else {
				return TST_CompararPonteiroNulo( iValEsp , vtCartas[ inxCarta ] ,
				   "Carta deveria existir."  ) ;
			}

         } /* fim ativa: Testar CriarLista */

      /* Testar Destruir carta */

         else if ( strcmp( ComandoTeste , DESTRUIR_CARTA_CMD ) == 0 )
         {
            iNumLidos = LER_LerParametros( "i" ,
                               &inxCarta ) ;

			if( (iNumLidos != 1) || (inxCarta < 0) || (inxCarta >=10)) {

               return TST_CondRetParm ;
            } /* if */

            PCRT_DestruirCarta( vtCartas[ inxCarta ] ) ;
            vtCartas[ inxCarta ] = NULL ;
			
            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir Carta */

      /* Testar obter valor da carta */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CARTA_CMD ) == 0 )
         {
            iNumLidos = LER_LerParametros( "iii" ,
                       &inxCarta , &iNumeroDado , &iValEsp ) ;

            if( (iNumLidos != 3) || (inxCarta < 0) || (inxCarta >= 10) ) {

               return TST_CondRetParm ;
            } /* if */

            iValor = CRT_ObterValorCarta( vtCartas[ inxCarta ] ) ;

            if ( iValEsp == OK )
            {
               if( TST_CompararPonteiroNulo( 1 , vtCartas[ inxCarta ] ,
				   "Erro em ponteiro de nova carta."  ) != TST_CondRetOK ) {
					return TST_CondRetErro;
			   }

               return TST_CompararInt( iNumeroDado , iValor ,
					"Valores deveriam ser iguais." ) ;

            } /* if */
			
		   return TST_CompararInteirosDiferentes( iNumeroDado , iValor ,
				"Valores deveriam ser diferentes." ) ;

         } /* fim ativa: Testar obter valor da carta */

		 /* Testar obter naipe da carta */

         else if ( strcmp( ComandoTeste , OBTER_NAIPE_CARTA_CMD ) == 0 )
         {
            iNumLidos = LER_LerParametros( "isi" ,
                       &inxCarta , szNaipe , &iValEsp ) ;

            if( (iNumLidos != 3) || (inxCarta < 0) || (inxCarta >=10) ) {
               return TST_CondRetParm ;
            } /* if */

			if ( szNaipe == NULL ) {

               return TST_CompararPonteiroNulo( 0 , szNaipe ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

			strcpy(szNaipeAuxiliar, CRT_ObterNaipeCarta( vtCartas[ inxCarta ] ));

            if ( iValEsp == OK )
            {
               if( TST_CompararPonteiroNulo( !iValEsp , szNaipeAuxiliar ,
				   "Naipe da carta deveria existir."  ) != TST_CondRetOK) {
					   return TST_CondRetErro;
			   }

			  return TST_CompararString(szNaipe, szNaipeAuxiliar,
				"Naipe diferente do esperado.");
			} else {

				if(strcmp(szNaipe, szNaipeAuxiliar) != 0) {
					return TST_CondRetOK;

				} else {

					return TST_CompararStringsDiferentes(szNaipe, szNaipeAuxiliar,
						"Naipe deveriam ser diferentes.");
				}
			}

         } /* fim ativa: Testar obter naipe da carta */

		 /* Testar obter código do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_CODIGO_CARTA_CMD ) == 0 )
         {

            iNumLidos = LER_LerParametros( "iii" ,
                       &inxCarta , &iNumeroDado , &iValEsp ) ;

            if( (iNumLidos != 3) || (inxCarta < 0) || (inxCarta >= 10) ) {

               return TST_CondRetParm ;
            } /* if */

            iCodigo = CRT_ObterCodigoCarta( vtCartas[ inxCarta ] ) ;

            if ( iValEsp == OK )
            {
               if( TST_CompararPonteiroNulo( 1 , vtCartas[ inxCarta ] ,
				   "Erro em ponteiro de nova carta."  ) != TST_CondRetOK ) {
					return TST_CondRetErro;
				}

			 return TST_CompararInt( iNumeroDado , iCodigo ,
				"Código do elemento diferente do esperado." ) ;

			} 
			
			return TST_CompararInteirosDiferentes( iNumeroDado , iCodigo ,
             "Código do elemento diferente do esperado." ) ;

		} /* fim ativa: Testar obter código da carta */

		 /* Testar imprimir carta */

         else if ( strcmp( ComandoTeste , IMPRIMIR_CARTA_CMD ) == 0 )
         {

            iNumLidos = LER_LerParametros( "i" ,
                       &inxCarta) ;

            if( (iNumLidos != 1) || (inxCarta < 0) || (inxCarta >= 10) ) {

               return TST_CondRetParm ;
            } /* if */

			if( CRT_ImprimirCarta(vtCartas[ inxCarta ]) != COR_CondRetOK ) {
				return TST_CondRetErro;
			}

		return TST_CondRetOK;

		} /* fim ativa: Testar imprimir carta */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar Carta */

   /********    Códigos das funções encapsuladas nos módulos **************/

TST_tpCondRet TST_CompararStringsDiferentes(char * ValorEsperado ,
									 char * ValorObtido   ,
									 char * pMensagem  )
   {
	  if ( strcmp( ValorObtido , ValorEsperado ) == 0 )
      {
         TST_ContarFalhas( );
         TST_ExibirPrefixo( SINALIZA_ERRO , pMensagem ) ;
         fprintf( TST_ObterArqLog() , "Deveria ser: >%s<  É: >%s<" ,
                  ValorEsperado , ValorObtido ) ;
         return TST_CondRetErro ;
      } /* if */
      return TST_CondRetOK ;
   }

   /***************************************************************************
*
*  Função: TSTG &Comparar Inteiros Diferentes
*  ****/

TST_tpCondRet TST_CompararInteirosDiferentes( long   ValorEsperado ,
												long   ValorObtido   ,
												char * pMensagem       )
   {

      if ( ValorObtido == ValorEsperado )
      {
         TST_ContarFalhas( );
         TST_ExibirPrefixo( SINALIZA_ERRO , pMensagem ) ;
         fprintf( TST_ObterArqLog(), "Deveria ser: %ld  É: %ld" ,
                  ValorEsperado , ValorObtido ) ;
         return TST_CondRetErro ;
      } /* if */
      return TST_CondRetOK ;

   } /* Fim função: TSTG &Comparar inteiro */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

