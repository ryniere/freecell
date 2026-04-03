/***************************************************************************
*  $MCI Módulo de implementação: TCALT Teste Colunas Aleatorias
*
*  Arquivo gerado:              TestCALT.c
*  Letras identificadoras:      TCALT
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
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

#include "COLUNAS_ALEATORIAS.H"
#include    "Baralho.h"
#include    "PrivilegioCarta.h"


static const char CRIAR_COLUNAS_ALEATORIAS_CMD              [ ] = "=criarcolunasaleatorias"     ;
static const char PREENCHER_COLUNAS_ALEATORIAS_CMD          [ ] = "=preenchercolunasaleatorias"     ;
static const char INSERIR_CARTA_SEQUENCIA_CMD               [ ] = "=inserircartasequencia"     ;
static const char RETIRAR_CARTA_SEQUENCIA_CMD               [ ] = "=retirarcartasequencia"     ;
static const char IMPRIMIR_COLUNAS_ALEATORIAS_CMD           [ ] = "=imprimircolunasaleatorias"     ;
static const char DESTRUIR_COLUNAS_ALEATORIAS_CMD           [ ] = "=destruircolunasaleatorias"     ;
static const char OBTER_CARTA_COLUNA_ALEATORIA_CMD			[ ]	= "=obtercartaaleatoria"	;
static const char IR_FINAL_COLUNA_ALEATORIA_CMD				[ ] = "=irfinalaleatoria";
static const char AVANCAR_ELEM_CORR_COLUNA_ALEATORIA_CMD	[ ] = "=avancarelemcorraleatoria";
static const char RESET_CARTAS_CMD                          [ ] = "=resetcartas"     ;


#define DIM_VALOR     100
#define DIM_VT_CARTA  15

CRT_ptpCarta   vtCartas[ DIM_VT_CARTA ] ;


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TCALT &Testar Colunas Aleatorias
*
*  $ED Descrição da função
*      Podem ser criadas até 15 cartas, identificadas pelos índices 0 a 14
*     
*
*     Comandos disponíveis:
*
*     =criarcolunasaleatorias                  CondRetEsp         
*     =preenchercolunasaleatorias              CondRetEsp               
*     =inserircartasequencia                   ValorDado StringDado ixIndiceCarta ixIndice CondRetEsp
*     =retirarcartasequencia                   ixIndice CondRetEsp
*     =imprimircolunasaleatorias               CondRetEsp
*     =destruircolunasaleatorias               CondRetEsp
*	  =obtercartaaleatoria					   ixIndice CondRetEsp
*	  =irfinalaleatoria						   ixIndice CondRetEsp
*	  =avancarelemcorraleatoria				   ixIndice numElem CondRetEsp
*     =resetcartas
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

	int numLidos   = -1 ,
		CondRetEsp = -1,
		ValorDado  = -1,
		ixIndice = -1,
	    ixIndiceCarta = -1,
		numElem = -1;


    char   StringDado[  DIM_VALOR ] ;

	int ValEsp = -1 ;
	
	int i ;
    
	CRT_ptpCarta ptpCarta;


    StringDado[ 0 ] = 0 ;

	 /* Efetuar reset das cartas criada para o teste do modulo Colunas Aleatorias  */

        if ( strcmp( ComandoTeste , RESET_CARTAS_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_CARTA ; i++ )
            {
			   PCRT_DestruirCarta(vtCartas[i]);
               vtCartas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */


	/* Testar Criar Colunas Aleatorias */

		 else if ( strcmp( ComandoTeste , CRIAR_COLUNAS_ALEATORIAS_CMD ) == 0 )
	{
         
		numLidos = LER_LerParametros( "i" ,
			&CondRetEsp ) ;
		

		if ( ( numLidos != 1 ) )
		{
			return TST_CondRetParm ;
		} /* if */

		
        
		if(  CALT_CriarColunasAleatorias() == COR_CondRetOK ){
            
			return TST_CondRetOK;

		}
		

		return TST_CondRetErro;

	} /* fim ativa: Testar Criar Colunas Aleatorias */

	/* Testar Preencher Colunas Aleatorias */



	else if ( strcmp( ComandoTeste , PREENCHER_COLUNAS_ALEATORIAS_CMD ) == 0 )
	{
		

		numLidos = LER_LerParametros( "i" ,
			&CondRetEsp ) ;

		if ( ( numLidos != 1 ) )
		{
			return TST_CondRetParm ;
		} /* if */
		

		if ( BAR_CriarBaralho() != COR_CondRetOK ) {

			return TST_CondRetErro ;
		}/* if */
        
		if ( BAR_Embaralhar() != COR_CondRetOK ) {

			return TST_CondRetErro ;
		}/*if */


		return TST_CompararInt( CondRetEsp , CALT_PreencherColunasAleatorias() ,
			"Condicao de retorno errada ao preencher colunas." ) ;


	} /* fim ativa: Testar Preencher Colunas Aleatorias */

	/* Testar Imprimir Colunas Aleatorias */

	else if ( strcmp( ComandoTeste , IMPRIMIR_COLUNAS_ALEATORIAS_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "i" ,
			&CondRetEsp ) ;

		if ( numLidos != 1 )
		{
			return TST_CondRetParm ;
		} /* if */



		return TST_CompararInt( CondRetEsp , CALT_ImprimirColunasAleatorias() ,
			"Condicao de retorno errada ao imprimir colunas." ) ;

	} /* fim ativa: Testar Imprimir Colunas Aleatorias */

	/* Testar Destruir Colunas Aleatorias */

	else if ( strcmp( ComandoTeste , DESTRUIR_COLUNAS_ALEATORIAS_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "i" ,
			&CondRetEsp ) ;

		if ( ( numLidos != 1 ))
		{
			return TST_CondRetParm ;
		} /* if */
       

		return TST_CompararInt( CondRetEsp , CALT_DestruirColunasAleatorias() ,
			"Condicao de retorno errada ao destruir lista." ) ;

	} /* fim ativa: Testar Destruir Colunas Aleatorias */

	/* Testar Inserir Carta Na Sequencia */

	else if ( strcmp( ComandoTeste , INSERIR_CARTA_SEQUENCIA_CMD ) == 0 )
	{
        
		numLidos = LER_LerParametros( "isiii" ,
			&ValorDado, StringDado, &ixIndiceCarta, &ixIndice, &CondRetEsp ) ;

		if ( ( numLidos != 5 ) || ( StringDado==NULL )
			||( ValorDado<=0 ) || ( ValorDado>=14 ) || 
			( ixIndiceCarta <  0 ) || ( ixIndiceCarta >= DIM_VT_CARTA ))
		{
			return TST_CondRetParm ;
		} /* if */

		vtCartas[ ixIndiceCarta ]= PCRT_CriarCarta( ValorDado, StringDado );
       
		if(  vtCartas[ ixIndiceCarta ]==NULL ){

			return TST_CondRetMemoria;


		}
		
            
		return TST_CompararInt( CondRetEsp ,
			CALT_InserirCartaSequenciaColuna(vtCartas[ ixIndiceCarta ],ixIndice) ,
			"Condicao de retorno errada ao inserir carta" ) ;

	} /* fim ativa: Testar Inserir Carta Na Sequencia */

	/* Testar Retirar Carta Na Sequencia */

	else if ( strcmp( ComandoTeste , RETIRAR_CARTA_SEQUENCIA_CMD ) == 0 )
	{   
		
		numLidos = LER_LerParametros( "ii" ,
			&ixIndice, &ValEsp ) ;

		if (  numLidos != 2   )
		{
			return TST_CondRetParm ;
		} /* if */

		ptpCarta = CALT_RetirarCartaSequenciaColuna(ixIndice);
        
		if ( ValEsp == 0 )
		{
			return TST_CompararPonteiroNulo( 0 , ptpCarta ,
				"Valor não deveria existir." ) ;
		} 
		if ( ptpCarta == NULL )
		{
			return TST_CompararPonteiroNulo( 1 , ptpCarta ,
				"Dado tipo um deveria existir." ) ;
		}

		return TST_CondRetOK;

	} /* fim ativa: Testar Destruir Colunas Aleatorias */

	/* Testar obter carta coluna aleatoria */
		 else if ( strcmp( ComandoTeste , OBTER_CARTA_COLUNA_ALEATORIA_CMD ) == 0 ) {
			
			numLidos = LER_LerParametros( "ii", &ixIndice, &CondRetEsp ) ;
			
            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            }
			
			ptpCarta = CALT_ObterCartaColunaAleatoria( ixIndice );
            
            if ( CondRetEsp == 0 )
            {
				return TST_CompararPonteiroNulo( 0, ptpCarta, 
							"Devia retornar ponteiro nulo." ) ;
            } 
						
            return TST_CompararPonteiroNulo( 1, ptpCarta, 
						"Devia retornar ponteiro nao nulo." ) ;

         } /* fim ativa: Testar obter carta coluna aleatoria */

		 /* Testar Ir Final Coluna Aleatoria */
         else if ( strcmp( ComandoTeste , IR_FINAL_COLUNA_ALEATORIA_CMD ) == 0 )
         {
			 numLidos = LER_LerParametros( "ii", &ixIndice, &CondRetEsp ) ;
			
            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            }
            
			return TST_CompararInt( CALT_IrFinalColunaAleatoria(ixIndice) , CondRetEsp ,
                         "Erro ao ir final Coluna Aleatoria." ) ;

         } /* fim ativa: Testar Ir Final Coluna Aleatoria */

		 /* Testar Avancar Elem Corr Coluna Aleatoria */
         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CORR_COLUNA_ALEATORIA_CMD ) == 0 )
         {
			 numLidos = LER_LerParametros( "iii", &ixIndice, &numElem, &CondRetEsp ) ;
			
            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            }
            
			return TST_CompararInt( CALT_AvancarElemCorrColunasAleatorias(ixIndice, numElem) , CondRetEsp ,
                         "Erro ao avancar elemento da coluna aleatoria." ) ;

         } /* fim ativa: Testar Avancar Elem Corr Coluna Aleatoria */

	return TST_CondRetNaoConhec ;

} /* Fim função: TCALT &Testar Colunas Aleatorias */


/********** Fim do módulo de implementação: TCALT Colunas Aleatorias **********/