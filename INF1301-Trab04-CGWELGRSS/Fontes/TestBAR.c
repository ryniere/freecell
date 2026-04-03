/***************************************************************************
*  $MCI Módulo de implementação: TBAR Teste baralho
*
*  Arquivo gerado:              TestBAR.c
*  Letras identificadoras:      TBAR
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

extern CRT_ptpCarta vtBaralho[];

static const char CRIAR_BARALHO_CMD					[ ] = "=criarbaralho"     ;
static const char DESTRUIR_BARALHO_CMD				[ ] = "=destruirbaralho"  ;
static const char IMPRIMIR_BARALHO_CMD				[ ] = "=imprimirbaralho"  ;
static const char EMBARALHAR_CMD					[ ] = "=embaralhar"  ;
static const char VERIFICA_EMBARALHAMENTO_CMD		[ ] = "=verificaembaralhamento";
static const char BUSCAR_CARTA_BARALHO_ORDENADO_CMD [ ] = "=buscarcartabaralhoordenado";


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100


/********************************************************
*		Funções encapsuladas no módulo					*
*********************************************************/

static int verificarCartaBaralho(CRT_ptpCarta pCarta, int iPosicao);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TBAR &Testar baralho
*
*  $ED Descrição da função
*     Podem ser criado 1 baralho de cada vez.
*
*     Comandos disponíveis:
*
*     =criarbaralho                 CondRetEsp         
*     =destruirbaralho              CondRetEsp               
*     =embaralhar                   CondRetEsp
*	  =buscarcartabaralhoordenado	iValor szNaipe CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

	int iNumLidos   = -1 ,
		iCondRetEsp = -1 ;	
	int iContadorCartasEmbaralhadas = 0;
	int iContadorCartas = 0;	
	int iTolerancia = -1;
	int iValor;
	char szNaipe[ DIM_VALOR ];

	CRT_ptpCarta vtCopiaBaralho[QTD_CARTAS];
	CRT_ptpCarta pCartaTeste;

	/* Testar CriarBaralho */

	if ( strcmp( ComandoTeste , CRIAR_BARALHO_CMD ) == 0 )
	{

		iNumLidos = LER_LerParametros( "i" ,
			&iCondRetEsp ) ;

		if ( ( iNumLidos != 1 ) )
		{
			return TST_CondRetParm ;
		} /* if */

		
		return TST_CompararInt( iCondRetEsp , BAR_CriarBaralho() ,
			"Condicao de retorno errada ao criar baralho" ) ;

	} /* fim ativa: Testar CriarBaralho */

	/* Testar Destruir baralho */

	else if ( strcmp( ComandoTeste , DESTRUIR_BARALHO_CMD ) == 0 )
	{

		iNumLidos = LER_LerParametros( "i" ,
			&iCondRetEsp ) ;

		if ( ( iNumLidos != 1 ))
		{
			return TST_CondRetParm ;
		} /* if */

		

		return TST_CompararInt( iCondRetEsp , BAR_DestruirBaralho() ,
			"Condicao de retorno errada ao criar baralho" ) ;

	} /* fim ativa: Testar Destruir baralho */

	/* Testar Embaralhar */

	else if ( strcmp( ComandoTeste , EMBARALHAR_CMD ) == 0 )
	{

		iNumLidos = LER_LerParametros( "i" ,
			&iCondRetEsp ) ;

		if ( ( iNumLidos != 1 ))
		{
			return TST_CondRetParm ;
		} /* if */

		//for

		return TST_CondRetErro ;

	} /* fim ativa: Testar Embaralhar */

	else if ( strcmp( ComandoTeste , VERIFICA_EMBARALHAMENTO_CMD ) == 0 )
	{

		iNumLidos = LER_LerParametros( "ii" ,
			&iTolerancia, &iCondRetEsp ) ;

		if ( ( iNumLidos != 2 ) || (iTolerancia < 0) || (iTolerancia >= 52) )
		{
			return TST_CondRetParm ;
		} /* if */

		iContadorCartasEmbaralhadas = 0;


		for(iContadorCartas = 0; iContadorCartas < QTD_CARTAS; iContadorCartas++) {
			vtCopiaBaralho[iContadorCartas] = vtBaralho[iContadorCartas];
		}

		BAR_Embaralhar();

		for(iContadorCartas = 0; iContadorCartas < QTD_CARTAS; iContadorCartas++) {

			if( !(verificarCartaBaralho(vtCopiaBaralho[ iContadorCartas ], iContadorCartas) == TRUE) ) {
				iContadorCartasEmbaralhadas++;
			}
		}

		if( iContadorCartasEmbaralhadas <= iTolerancia ) {
			return TST_CondRetErro;
		}

		//for

		return TST_CondRetOK ;

	} /* fim ativa: Testar Embaralhar */

	/* Testar Buscar carta baralho ordenado */

	if ( strcmp( ComandoTeste , BUSCAR_CARTA_BARALHO_ORDENADO_CMD ) == 0 )
	{

		iNumLidos = LER_LerParametros( "isii" , &iValor, szNaipe, 
									&iCondRetEsp ) ;

		if ( ( iNumLidos != 3 ) )
		{
			return TST_CondRetParm ;
		} /* if */

		pCartaTeste = BAR_BuscarCartaBaralhoOrdenado( iValor, szNaipe );
		
		if ( iCondRetEsp == 0 )
            {
				return TST_CompararPonteiroNulo( 0, pCartaTeste, 
							"Devia retornar ponteiro nulo." ) ;
            } 
						
            return TST_CompararPonteiroNulo( 1, pCartaTeste, 
						"Devia retornar ponteiro nao nulo." ) ;

	} /* fim ativa: Testar Buscar carta baralho ordenado */

	return TST_CondRetNaoConhec ;

} /* Fim função: TBAR &Testar baralho */

/*************** Código das funções encapsuladas no módulo ***********************/

int verificarCartaBaralho(CRT_ptpCarta pCarta, int iPosicao)
{
	if( (pCarta != NULL) && (iPosicao >= 0) && (iPosicao <= 51)) {

		if( strcmp( CRT_ObterNaipeCarta(pCarta), CRT_ObterNaipeCarta(vtBaralho[ iPosicao ]) ) != 0 ) {
			return FALSE;
		}

		if( CRT_ObterCodigoCarta(pCarta) == CRT_ObterCodigoCarta(vtBaralho[ iPosicao ]) ) {
			return TRUE;
		}
	}
return FALSE;
}


/********** Fim do módulo de implementação: TBAR Teste baralho **********/

