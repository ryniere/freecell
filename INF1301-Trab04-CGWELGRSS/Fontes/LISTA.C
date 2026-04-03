/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include	"TRATAMENTO_FALHA.h"

#ifdef _DEBUG

#include "..\\tabelas\\IdTiposEspaco.def"
#include "CESPDIN.H"
#include "GENERICO.H"
#include "CONTA.H"

#endif

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

typedef struct tagElemLista {

#ifdef _DEBUG

	struct LIS_tagLista * pCabeca ;
	/* Ponteiro para cabeca
	*
	*$ED Descrição
	*   Todos os nós da lista devem apontar para a respectiva cabeça.
	*   Esse ponteiro corresponde a um identificador da lista para fins
	*   de verificação da integridade. */

#endif

	void * pValor ;
	/* Ponteiro para o valor contido no elemento */

	struct tagElemLista * pAnt ;
	/* Ponteiro para o elemento predecessor */

	struct tagElemLista * pProx ;
	/* Ponteiro para o elemento sucessor */

} tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

typedef struct LIS_tagLista {

	tpElemLista * pOrigemLista ;
	/* Ponteiro para a origem da lista */

	tpElemLista * pFimLista ;
	/* Ponteiro para o final da lista */

	tpElemLista * pElemCorr ;
	/* Ponteiro para o elemento corrente da lista */

	int numElem ;
	/* Número de elementos da lista */

} LIS_tpLista ;

/*****  Dados encapsulados no módulo  *****/

#ifdef _DEBUG

static char EspacoLixo[ 256 ] =
"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
/* Espaço de dados lixo usado ao testar */

#endif

/***** Protótipos das funções encapuladas no módulo *****/

static void LiberarElemento( LIS_tppLista   pLista ,
							tpElemLista  * pElem   ) ;

static tpElemLista * CriarElemento( LIS_tppLista pLista ,
								   void *       pValor  ) ;

static void LimparCabeca( LIS_tppLista pLista ) ;

static LIS_tpCondRet VerificarNumElem ( LIS_tppLista pLista );

static LIS_tpCondRet VerificarEncadeamento( LIS_tppLista pLista);

#ifdef _DEBUG

static tpElemLista* VerificarOrigemLista( LIS_tppLista pLista );

static tpElemLista* VerificarFimLista( LIS_tppLista pLista );

static LIS_tpCondRet VerificarElem( tpElemLista * pElem ) ;

#endif

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

LIS_tppLista LIS_CriarLista( void )
{

	LIS_tpLista * pLista = NULL ;

	#ifdef _DEBUG
		CNT_CONTAR("LIS_CriarLista");
	#endif /* _DEBUG */

	pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
	if ( pLista == NULL )
	{
		return NULL ;	/*Erro ao alocar lista */
	} /* if */

	#ifdef _DEBUG
		CED_DefinirTipoEspaco( pLista , LIS_TipoEspacoCabeca ) ;
	#endif

	LimparCabeca( pLista ) ;

	return pLista ;

} /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

void LIS_DestruirLista( LIS_tppLista pLista )
{

	#ifdef _DEBUG
		CNT_CONTAR("LIS_DestruirLista");
	#endif /*_DEBUG */

	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}

	#ifdef _DEBUG
		if( CED_ObterTipoEspaco( pLista ) !=  LIS_TipoEspacoCabeca ) {
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_DestruirLista - TipoEspaco errado." );
		}
	#endif

	LIS_EsvaziarLista( pLista ) ;
	
	free( pLista ) ;

} /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

void LIS_EsvaziarLista( LIS_tppLista pLista )
{

	tpElemLista * pElem ;
	tpElemLista * pProx ;

	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}

	#ifdef _DEBUG
		if( CED_ObterTipoEspaco( pLista ) !=  LIS_TipoEspacoCabeca ) {
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_EsvaziarLista1 - TipoEspaco errado." );
		}

		CNT_CONTAR("LIS_EsvaziarLista");
	#endif /* _DEBUG */

	pElem = pLista->pOrigemLista ;	/* Posiciona ponteiro no inicio da lista */

	#ifdef _DEBUG
		if( VerificarOrigemLista( pLista ) != pElem ){ /* Verifica se ponteiro está no inicio da lista */

			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_EsvaziarLista2 - TipoEspaco errado." );
		}	
	#endif

	while ( pElem != NULL )
	{
		#ifdef _DEBUG
				
			CNT_CONTAR("LIS_EsvaziarLista:Retirar elemento não nulo da lista.");
		

			if( CED_ObterTipoEspaco( pElem ) !=  LIS_TipoEspacoElem ) {
				TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_EsvaziarLista3 - TipoEspaco errado." );
			}
		
		#endif /* _DEBUG */
	
		pProx = pElem->pProx ;
		LiberarElemento( pLista , pElem ) ;
		pElem = pProx ;
	} /* while */

	LimparCabeca( pLista ) ;


} /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
									   void * pValor        )
{

	tpElemLista * pElem ;

	#ifdef _DEBUG

		tpElemLista * pElemCorrEntra = NULL;
		tpElemLista * pElemAux = NULL;
		CNT_CONTAR("LIS_InserirElementoAntes");
	#endif

	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}

	#ifdef _DEBUG
		if( CED_ObterTipoEspaco( pLista ) !=  LIS_TipoEspacoCabeca ) {
				TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_InserirElementoAntes1 - TipoEspaco errado." );
		}
	#endif

	if(LIS_VerificarEstruturaLista( pLista ) != LIS_CondRetOK) {
		TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
	}

	/* Criar elemento a inserir antes */

	pElem = CriarElemento( pLista , pValor ) ;

	if ( pElem == NULL )
	{
		#ifdef _DEBUG
				CNT_CONTAR("LIS_InserirElementoAntes: Falta de memória a criar elemento da lista.");
		#endif /* _DEBUG */

		return LIS_CondRetFaltouMemoria ;
	} /* if */

	#ifdef _DEBUG

		if( CED_ObterTipoEspaco( pElem ) !=  LIS_TipoEspacoElem ) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_InserirElementoAntes2 - TipoEspaco errado." );
		}

			/* Verifica se novo elemento está desencadeado */
		if((pElem->pAnt != NULL) || (pElem->pProx != NULL)) {
		
			TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
		}

	#endif


	/* Encadear o elemento antes do elemento corrente */

	if ( pLista->pElemCorr == NULL )
	{
		#ifdef _DEBUG
				CNT_CONTAR("LIS_InserirElementoAntes: Encadeamento de elemento em lista vazia.");
		#endif /*_DEBUG */

		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else
	{
		#ifdef _DEBUG
			pElemCorrEntra = pLista->pElemCorr;
			pElemAux = pLista->pElemCorr->pAnt;

			CNT_CONTAR("LIS_InserirElementoAntes: Encadeamento de elemento em lista que contém elemento(s).");
		#endif /* _DEBUG */

		if ( pLista->pElemCorr->pAnt != NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR("LIS_InserirElementoAntes: Encadeamento de elemento quando o elemento corrente não é o primeiro.");
			#endif /* _DEBUG */

			pElem->pAnt  = pLista->pElemCorr->pAnt ;
			pLista->pElemCorr->pAnt->pProx = pElem ;
		} else
		{
			#ifdef _DEBUG
				CNT_CONTAR("LIS_InserirElementoAntes: Encadeamento de elemento quando o elemento corrente é primeiro.");
			#endif /* _DEBUG */
			pLista->pOrigemLista = pElem ;
		} /* if */

		pElem->pProx = pLista->pElemCorr ;
		pLista->pElemCorr->pAnt = pElem ;
	} /* if */

	pLista->pElemCorr = pElem ;

#ifdef _DEBUG	
	if(pLista->pElemCorr != pElem) {	/* Verifica encadeamento */
	
		TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
	}
	if((pElemAux != NULL) && (pElemCorrEntra != NULL)){
		if((pLista->pElemCorr->pAnt != pElemAux) || (pElemAux->pProx != pLista->pElemCorr)) {
			
			TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
		}

		if((pElemCorrEntra->pAnt != pLista->pElemCorr) || (pLista->pElemCorr->pProx != pElemCorrEntra)){
		
			TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
		}
	}
#endif

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
									  void * pValor        )

{
	tpElemLista * pElem ;

	
	#ifdef _DEBUG

		tpElemLista * pElemCorrEntra = NULL;
		tpElemLista * pElemAux = NULL;
		CNT_CONTAR("LIS_InserirElementoApos");
	#endif

	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}

	#ifdef _DEBUG
		if( CED_ObterTipoEspaco( pLista ) !=  LIS_TipoEspacoCabeca ) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_InserirElementoApos1 - TipoEspaco errado." );
		}
	#endif

	if(LIS_VerificarEstruturaLista( pLista ) != LIS_CondRetOK) {
		TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
	}

	/* Criar elemento a inserir após */

	pElem = CriarElemento( pLista , pValor ) ;
	if ( pElem == NULL )
	{
		#ifdef _DEBUG
		CNT_CONTAR("LIS_InserirElementoApos: Falta de memória a criar elemento da lista.");
		#endif

		return LIS_CondRetFaltouMemoria ;
	} /* if */

	#ifdef _DEBUG

		if( CED_ObterTipoEspaco( pElem ) !=  LIS_TipoEspacoElem ) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_InserirElementoApos2 - TipoEspaco errado." );
		}

		/* Verifica se novo elemento está desencadeado */
		if((pElem->pAnt != NULL) || (pElem->pProx != NULL)) {
		
			TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
		}

	#endif

	/* Encadear o novo elemento após o elemento corrente */

	if ( pLista->pElemCorr == NULL ) /* Lista vazia */
	{
		#ifdef _DEBUG
				CNT_CONTAR("LIS_InserirElementoApos: Encadeamento de elemento em lista vazia.");
		#endif /* _DEBUG */

		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else
	{
		#ifdef _DEBUG
				pElemCorrEntra = pLista->pElemCorr;
				pElemAux = pLista->pElemCorr->pProx;
	
				CNT_CONTAR("LIS_InserirElementoApos: Encadeamento de elemento em lista que contém elemento(s).");
		#endif /* _DEBUG */

		if ( pLista->pElemCorr->pProx != NULL ) /* Lista com mais de um elemento */
		{
			#ifdef _DEBUG
				CNT_CONTAR("LIS_InserirElementoApos: Encadeamento de elemento quando o elemento corrente não é o último.");
			#endif /* _DEBUG */

			pElem->pProx  = pLista->pElemCorr->pProx ;
			pLista->pElemCorr->pProx->pAnt = pElem ;
		} else /* Lista só com o elemento corrente */
		{
			#ifdef _DEBUG
				CNT_CONTAR("LIS_InserirElementoApos: Encadeamento de elemento quando o elemento corrente é o último.");
			#endif /* _DEBUG */
			pLista->pFimLista = pElem ;
		} /* if */

		pElem->pAnt = pLista->pElemCorr ;	/* Acerta encadeamento */
		pLista->pElemCorr->pProx = pElem ;

	} /* if */

	pLista->pElemCorr = pElem ;

	#ifdef _DEBUG	
	
	if(pLista->pElemCorr != pElem) {	/* Verifica encadeamento */
	
		TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
	}
	if((pElemAux != NULL) && (pElemCorrEntra != NULL)){
		
		if((pLista->pElemCorr->pProx != pElemAux) || (pElemAux->pAnt != pLista->pElemCorr)) {
			
			TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
		}

		if((pElemCorrEntra->pProx != pLista->pElemCorr) || (pLista->pElemCorr->pAnt != pElemCorrEntra)){
		
			TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
		}
		
	}
	#endif

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
{

	tpElemLista * pElem ;
	#ifdef _DEBUG
		tpElemLista * pElemAnt;
		tpElemLista * pElemProx;
		CNT_CONTAR("LIS_ExcluirElemento");
	#endif

	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}

	#ifdef _DEBUG

		if( CED_ObterTipoEspaco( pLista ) !=  LIS_TipoEspacoCabeca) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_ExcluirElemento1 - TipoEspaco errado." );
		}
	#endif

	if(LIS_VerificarEstruturaLista( pLista ) != LIS_CondRetOK) {
		TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
	}

	if ( pLista->pElemCorr == NULL )
	{
		#ifdef _DEBUG
				CNT_CONTAR("LIS_ExcluirElemento: Excluir elemento em lista vazia.");
		#endif /* _DEBUG */

		return LIS_CondRetListaVazia ;
	} /* if */

	pElem = pLista->pElemCorr ;

	#ifdef _DEBUG

		if( CED_ObterTipoEspaco( pElem ) !=  LIS_TipoEspacoElem ) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_ExcluirElemento2- TipoEspaco errado." );
		}

	#endif

	#ifdef _DEBUG
		pElemAnt = pLista->pElemCorr->pAnt;
		pElemProx = pLista->pElemCorr->pProx;
	#endif

	/* Desencadeia à esquerda */

	if ( pElem->pAnt != NULL )
	{
		#ifdef _DEBUG
				CNT_CONTAR("LIS_ExcluirElemento: Excluir elemento que nao é origem lista.");
		#endif /* _DEBUG */
		pElem->pAnt->pProx   = pElem->pProx ;
		pLista->pElemCorr    = pElem->pAnt ;
	} else {

		#ifdef _DEBUG
				CNT_CONTAR("LIS_ExcluirElemento: Excluir origem lista.");
		#endif /* _DEBUG */

		pLista->pElemCorr    = pElem->pProx ;
		pLista->pOrigemLista = pLista->pElemCorr ;
	} /* if */

	/* Desencadeia à direita */

	if ( pElem->pProx != NULL )
	{
		#ifdef _DEBUG
				CNT_CONTAR("LIS_ExcluirElemento: Excluir elemento que nao é fim lista.");
		#endif /* _DEBUG */
		pElem->pProx->pAnt = pElem->pAnt ;
	} else
	{
		#ifdef _DEBUG
				CNT_CONTAR("LIS_ExcluirElemento: Excluir fim lista.");
		#endif /* _DEBUG */

		pLista->pFimLista = pElem->pAnt ;
	} /* if */

	#ifdef _DEBUG
		/* Verifica novo encadeamento */
		if( pElemAnt != NULL ) {
			if( (pElemAnt->pProx != pElemProx) ) {
				TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
			}
		}

		if( pElemProx != NULL ) {
			if(pElemProx->pAnt != pElemAnt) {
				TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
			}
		}

	#endif

	LiberarElemento( pLista , pElem ) ;

	if(LIS_VerificarEstruturaLista( pLista ) != LIS_CondRetOK) {
		TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
	}

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

void * LIS_ObterValor( LIS_tppLista pLista )
{
	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}

	#ifdef _DEBUG

		CNT_CONTAR("LIS_ObterValor");
		if( CED_ObterTipoEspaco( pLista ) !=  LIS_TipoEspacoCabeca) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_ObterValor - TipoEspaco errado." );
		}

	#endif
	
	if ( pLista->pElemCorr == NULL )
	{
		#ifdef _DEBUG
				CNT_CONTAR("LIS_ObterValor: Obter valor de elemento corrente nulo.");
		#endif /* _DEBUG */
		return NULL ;
	} /* if */

	#ifdef _DEBUG
		CNT_CONTAR("LIS_ObterValor: Obter valor de elemento corrente nao nulo.");
	#endif /* _DEBUG */
	return pLista->pElemCorr->pValor ;

} /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

void LIS_IrInicioLista( LIS_tppLista pLista )
{
	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}

	#ifdef _DEBUG

	    CNT_CONTAR("LIS_IrInicioLista");
		if( CED_ObterTipoEspaco( pLista ) !=  LIS_TipoEspacoCabeca) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_IrInicioLista1 - TipoEspaco errado." );
		}

		if( VerificarOrigemLista( pLista ) != pLista->pOrigemLista ){ /* Verifica se ponteiro está no inicio da lista */

			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_IrInicioLista - Origem errada." );
		}
		
	#endif

	pLista->pElemCorr = pLista->pOrigemLista ;

} /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

void LIS_IrFinalLista( LIS_tppLista pLista )
{
	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}

	#ifdef _DEBUG

		CNT_CONTAR("LIS_IrFinalLista");
		if( CED_ObterTipoEspaco( pLista ) !=  LIS_TipoEspacoCabeca) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_IrFinalLista1 - TipoEspaco errado." );
		}

		if( VerificarFimLista( pLista ) != pLista->pFimLista ){ /* Verifica se ponteiro está no fim da lista */

			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_IrFinalLista2 - Fim errado." );
		}
		
	#endif

	pLista->pElemCorr = pLista->pFimLista ;

} /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
										  int numElem )
{
	int i ;

	tpElemLista * pElem ;

	#ifdef _DEBUG
		tpElemLista * pElemAuxiliar;
		CNT_CONTAR("LIS_AvancarElementoCorrente");
	#endif

	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}

	#ifdef _DEBUG
		if( CED_ObterTipoEspaco( pLista ) !=  LIS_TipoEspacoCabeca) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_AvancarElemCorr - TipoEspaco errado." );
		}
	#endif

	/* Tratar lista vazia */

	if ( pLista->pElemCorr == NULL )
	{
		#ifdef _DEBUG
				CNT_CONTAR("LIS_AvancarElementoCorrente: Avancar elemento em lista vazia.");
		#endif /* _DEBUG */

		return LIS_CondRetListaVazia ;

	} /* fim ativa: Tratar lista vazia */

	/* Tratar avançar para frente */

	if ( numElem > 0 )
	{

		pElem = pLista->pElemCorr ;

		for( i = numElem ; i > 0 ; i-- )
		{
			#ifdef _DEBUG
				pElemAuxiliar = pElem;
			#endif		

			if ( pElem == NULL )
			{
				break ;
			} /* if */
			pElem    = pElem->pProx ;

			#ifdef _DEBUG
				if(pElem != NULL) {
					
					if(( pElem->pAnt != pElemAuxiliar) ||
						( pElem != pElemAuxiliar->pProx)){

							TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
					}
				}
			#endif
		} /* for */

		if ( pElem != NULL )
		{
			#ifdef _DEBUG
						CNT_CONTAR("LIS_AvancarElementoCorrente: Avancar elemento para frente e nao chegar ao fim.");
			#endif /* _DEBUG */
			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */

		#ifdef _DEBUG
				CNT_CONTAR("LIS_AvancarElementoCorrente: Avancar elemento para frente e chegar ao fim da lista.");
		#endif /* _DEBUG */

		pLista->pElemCorr = pLista->pFimLista ;

		return LIS_CondRetFimLista ;

	} /* fim ativa: Tratar avançar para frente */


	/* Tratar avançar para trás */

	else if ( numElem < 0 )
	{

		pElem = pLista->pElemCorr ;

		for( i = numElem ; i < 0 ; i++ )
		{
			#ifdef _DEBUG
						pElemAuxiliar = pElem;
			#endif

			if ( pElem == NULL )
			{
				break ;
			} /* if */
			pElem    = pElem->pAnt ;

			#ifdef _DEBUG
				if(pElem != NULL){
				
					if( (pElem->pProx != pElemAuxiliar) 
						||( pElem != pElemAuxiliar->pAnt) ) {

							TRF_AbortarPrograma("Erro fatal. O programa será abortado.");
					}
				}
			#endif
		} /* for */

		if ( pElem != NULL )
		{
			#ifdef _DEBUG
						CNT_CONTAR("LIS_AvancarElementoCorrente: Avancar elemento para trás e nao chegar ao inicio.");
			#endif /* _DEBUG */

			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */

		#ifdef _DEBUG
				CNT_CONTAR("LIS_AvancarElementoCorrente: Avancar elemento para tras e chegar ao inicio da lista.");
		#endif /* _DEBUG */

		pLista->pElemCorr = pLista->pOrigemLista ;
		return LIS_CondRetFimLista ;

	} /* fim ativa: Tratar avançar para trás */

	/* Tratar não avançar */

	#ifdef _DEBUG
		CNT_CONTAR("LIS_AvancarElementoCorrente: Nao avancar elemento.");
	#endif /* _DEBUG */

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
								void * pValor        )
{

	tpElemLista * pElem ;

	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}

	#ifdef _DEBUG

		CNT_CONTAR("LIS_ProcurarValor");
		if( CED_ObterTipoEspaco( pLista ) !=  LIS_TipoEspacoCabeca) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_ProcurarValor1 - TipoEspaco errado." );
		}

	#endif

	if ( pLista->pElemCorr == NULL )
	{
		#ifdef _DEBUG
				CNT_CONTAR("LIS_ProcurarValor: Procurar valor em lista vazia.");
		#endif /* _DEBUG */

		return LIS_CondRetListaVazia ;
	} /* if */

	for ( pElem  = pLista->pElemCorr ;
		pElem != NULL ;
		pElem  = pElem->pProx )
	{
		#ifdef _DEBUG

		if( CED_ObterTipoEspaco( pElem ) !=  LIS_TipoEspacoElem) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_ProcurarValor2 - TipoEspaco errado." );
		}

		#endif

		if ( pElem->pValor == pValor )
		{
			#ifdef _DEBUG
						CNT_CONTAR("LIS_ProcurarValor: Procurar valor pertencente a lista.");
			#endif /* _DEBUG */

			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */
	} /* for */

	#ifdef _DEBUG
		CNT_CONTAR("LIS_ProcurarValor: Procurar valor nao pertencente a lista.");
	#endif /* _DEBUG */

	return LIS_CondRetNaoAchou ;

} /* Fim função: LIS  &Procurar elemento contendo valor */


/***********************************************************************
*
*  $FC Função: LIS  &VerificarEstruturaLista
*
***********************************************************************/

LIS_tpCondRet LIS_VerificarEstruturaLista ( LIS_tppLista pLista ) {

	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}

	#ifdef _DEBUG

		CNT_CONTAR("LIS_VerificarEstruturaLista");
		if( CED_ObterTipoEspaco( pLista ) !=  LIS_TipoEspacoCabeca) {
		
			TRF_AbortarPrograma( "Erro fatal. Contate fornecedor sobre o log: LIS_VerificarEstrutura - TipoEspaco errado." );
		}

	#endif

	if ( VerificarEncadeamento( pLista ) != LIS_CondRetOK) {
		#ifdef _DEBUG
				CNT_CONTAR("LIS_VerificarEstruturaLista: Encadeamento incorreto na lista.");
		#endif
		return LIS_CondRetErro; /* Encadeamento na lista esta errado */
	}

	if ( VerificarNumElem( pLista ) != LIS_CondRetOK) {

		#ifdef _DEBUG
				CNT_CONTAR("LIS_VerificarEstruturaLista: Numero elementos lista != numero elementos encadeados.");
		#endif

		return LIS_CondRetErro; /* Numero de elementos da lista nao 
								corresponde ao numero de elementos encadeados */
	}
	return LIS_CondRetOK;
} /* Fim função: LIS  &Verificar Estrutura Lista */


#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Deturpar lista
*  ****/

void LIS_Deturpar( void * pListaParm ,
				  LIS_tpModosDeturpacao ModoDeturpar )
{

	LIS_tpLista * pLista = NULL ;
	tpElemLista * pElem ;

	CNT_CONTAR("LIS_Deturpar");

	if ( pListaParm == NULL )
	{
		CNT_CONTAR("LIS_Deturpar: Parametro pListaParm eh nulo.");
		return ;
	} /* if */

	pLista = ( LIS_tpLista * )( pListaParm ) ;

	switch ( ModoDeturpar ) {

		/* Modifica o tipo da cabeça */

		 case DeturpaTipoCabeca :
			 {
				 CNT_CONTAR("LIS_Deturpar: Modifica o tipo cabeca.");
				 CED_DefinirTipoEspaco( pLista , CED_ID_TIPO_VALOR_NULO ) ;

				 break ;

			 } /* fim ativa: Modifica o tipo da cabeça */

			 /* Anula ponteiro origem */

		 case DeturpaOrigemNula :
			 {

				 CNT_CONTAR("LIS_Deturpar: Anula ponteiro origem.");
				 pLista->pOrigemLista = NULL ;

				 break ;

			 } /* fim ativa: Anula ponteiro origem */

			 /* Anula ponteiro corrente */

		 case DeturpaFimNulo:
			 {

				 CNT_CONTAR("LIS_Deturpar: Anula ponteiro fim.");
				 pLista->pFimLista = NULL ;

				 break ;

			 } /* fim ativa: Anula ponteiro origem */

			 /* Anula ponteiro corrente */
		 case DeturpaCorrenteNulo :
			 {

				 CNT_CONTAR("LIS_Deturpar: Anula ponteiro corrente.");
				 pLista->pElemCorr = NULL ;

				 break ;

			 } /* fim ativa: Anula ponteiro corrente */

			 /* Faz origem apontar para lixo */

		 case DeturpaOrigemLixo :
			 {
				 CNT_CONTAR("LIS_Deturpar: Faz origem apontar para lixo.");
				 pLista->pOrigemLista = ( tpElemLista * )( EspacoLixo ) ;

				 break ;

			 } /* fim ativa: Faz origem apontar para lixo */
			
			 /* Faz fim apontar para lixo */
			 case DeturpaFimLixo :
			 {
				 CNT_CONTAR("LIS_Deturpar: Faz fim apontar para lixo.");
				 pLista->pFimLista = ( tpElemLista * )( EspacoLixo ) ;

				 break ;

			 } /* fim ativa: Faz fim apontar para lixo */

			 /* Faz corrente apontar para lixo */

		 case DeturpaCorrenteLixo :
			 {
				 CNT_CONTAR("LIS_Deturpar: Faz corrente apontar para lixo.");
				 pLista->pElemCorr = ( tpElemLista * )( EspacoLixo ) ;

				 break ;

			 } /* fim ativa: Faz corrente apontar para lixo */

			 /* Deturpar espaço cabeca */

		 case DeturparEspacoCabeca :
			 {

				 CNT_CONTAR("LIS_Deturpar: Deturpar espaço cabeca.");
				 memcpy( (( char * )( pLista )), "?????" , 5 ) ;

				 break ;

			 } /* fim ativa: Deturpar espaço cabeca */

			 /* Deturpa elemento */

		 default :

			 if ( pLista->pElemCorr != NULL )
			 {

				 CNT_CONTAR("LIS_Deturpar: Deturpa elemento.");
				 switch ( ModoDeturpar ) {

					 /* Modifica tipo elemento corrente */

		 case DeturpaTipoElem :
			 {

				 CNT_CONTAR("LIS_Deturpar: Modifica tipo elemento corrente.");
				 CED_DefinirTipoEspaco( pLista->pElemCorr , CED_ID_TIPO_VALOR_NULO ) ;

				 break ;

			 } /* fim ativa: Modifica tipo elemento corrente */

			 /* Anula ponteiro cabeça */

		 case DeturpaPtCabecaNulo :
			 {

				 CNT_CONTAR("LIS_Deturpar: Anula ponteiro cabeça.");
				 pLista->pElemCorr->pCabeca = NULL ;

				 break ;

			 } /* fim ativa: Anula ponteiro cabeça */

			 /* Anula ponteiro anterior */

		 case DeturpaPtAntNulo :
			 {

				 CNT_CONTAR("LIS_Deturpar: Anula ponteiro anterior.");
				 pLista->pElemCorr->pAnt = NULL ;
				 break ;

			 } /* fim ativa: Anula ponteiro anterior */

			 /* Anula ponteiro proximo */

		 case DeturpaPtProxNulo :
			 {

				 CNT_CONTAR("LIS_Deturpar: Anula ponteiro proximo.");
				 pLista->pElemCorr->pProx = NULL ;

				 break ;

			 } /* fim ativa: Anula ponteiro proximo */

			 /* Faz ponteiro cabeça apontar para lixo */

		 case DeturpaPtCabecaLixo :
			 {

				 CNT_CONTAR("LIS_Deturpar: Faz ponteiro cabeça apontar para lixo.");
				 pLista->pElemCorr->pCabeca = ( LIS_tpLista * )( EspacoLixo ) ;

				 break ;

			 } /* fim ativa: Faz ponteiro cabeça apontar para lixo */

			 /* Faz ponteiro anterior apontar para lixo */

		 case DeturpaPtAntLixo :
			 {

				 CNT_CONTAR("LIS_Deturpar: Faz ponteiro anterior apontar para lixo.");
				 pLista->pElemCorr->pAnt = ( tpElemLista * )( EspacoLixo ) ;

				 break ;

			 } /* fim ativa: Faz ponteiro anterior apontar para lixo */

			 /* Faz ponteiro proximo apontar para lixo */

		 case DeturpaPtProxLixo :
			 {

				 CNT_CONTAR("LIS_Deturpar: Faz ponteiro proximo apontar para lixo.");
				 pLista->pElemCorr->pProx = ( tpElemLista * )( EspacoLixo ) ;

				 break ;

			 } /* fim ativa: Faz ponteiro proximo apontar para lixo */

			 /* Atribui valor fora do domínio do espaço */

		 case DeturpaValor :
			 {
				 CNT_CONTAR("LIS_Deturpar: Atribui valor fora do domínio do espaço.");
				 memcpy( ( pLista->pElemCorr->pValor ) , "<<<<<" , 5 ) ;
				 break ;

			 } /* fim ativa: Atribui valor fora do domínio do espaço */

			 /* Deturpar espaço elemento */

		 case DeturparEspacoElem :
			 {

				 CNT_CONTAR("LIS_Deturpar: Deturpar espaço elemento.");
				 memcpy( (( char * )( pLista->pElemCorr )) , "????????" , 8 ) ;

				 break ;

			 } /* fim ativa: Deturpar espaço elemento */

			 /* Deturpar Elimina elemento corrente */		
		 case DeturparEliminarElementoCorrente :
			 {

				 CNT_CONTAR("LIS_Deturpar: Elimina elemento corrente.");
				 LiberarElemento(pLista, pLista->pElemCorr); 

				 break ;

			 } /* fim ativa: Elimina elemento corrente */

			 /* Deturpar Desencadeia elemento sem dar free */
		 case DeturparDesencadeiaElemento :
			 {

				 CNT_CONTAR("LIS_Deturpar: Desencadeia elemento sem libera-lo como free.");
				 pElem = pLista->pElemCorr ;

				 /* Desencadeia à esquerda */
				 if ( pElem->pAnt != NULL )
					{	

						pElem->pAnt->pProx   = pElem->pProx ;
						pLista->pElemCorr    = pElem->pAnt ;

					}
				 else{

					 pLista->pElemCorr    = pElem->pProx ;
					 pLista->pOrigemLista = pLista->pElemCorr ;

					}

				 /* Desencadeia à esquerda */
				 if ( pElem->pProx != NULL )
					{

						pElem->pProx->pAnt = pElem->pAnt ;

					}
				 else{

					 pLista->pFimLista = pElem->pAnt ;

					}


				 break ;

			 } /* fim ativa: Deturpar Desencadeia elemento sem dar free */

				 } /* fim seleciona: Deturpa nóo */

				 break ;

			 } /* fim ativa: Deturpa elemento */

	} /* fim seleciona: Origem de LIS  &Deturpar lista */

} /* Fim função: LIS  &Deturpar lista */

#endif /* DEBUG */


/***************************************************************************
*
*  Função: LIS  &Verificar Elem
*  ****/

#ifdef _DEBUG

LIS_tpCondRet LIS_VerificarElem( void * pElemParm ) 
{
	tpElemLista * pElem     = NULL ;
	LIS_tpLista  * pLista = NULL ;

	/* Verificar se é elemento */
	
	if ( pElemParm == NULL )
	{
		TST_NotificarFalha( "Tentou verificar elemento inexistente." ) ;
		return LIS_CondRetErroEstrutura ;

	} /* if */
	
	if ( ! CED_VerificarEspaco( pElemParm , NULL ))
	{
		TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
		return LIS_CondRetErroEstrutura ;
	} /* if */
	
	if ( TST_CompararInt( LIS_TipoEspacoElem ,
		CED_ObterTipoEspaco( pElemParm ) ,
		"Tipo do espaço de dados não é elemento de lista." ) != TST_CondRetOK )
	{
		return LIS_CondRetErroEstrutura ;
	} /* if */
	
	pElem     = ( tpElemLista * )( pElemParm ) ;
	pLista = pElem->pCabeca ;
	
	/* Verificar cabeça */

	if ( pLista != NULL  )
	{
		if ( TST_CompararPonteiro( pLista , pLista->pOrigemLista->pCabeca ,
			"Elemento não pertence à lista." ) != TST_CondRetOK )
		{
			return LIS_CondRetErroEstrutura ;
		} /* if */
	} else
	{
		return TST_NotificarFalha( "Elemento pertence a lista vazia." ) ;
	} /* if */
	
	/* Verificar origem e fim */

	if ( pElem->pAnt == NULL ) /* Elemento é origem da lista */
	{
		if(pElem->pProx != NULL){

			if (  pElem->pProx->pAnt != pElem )
			{
				TST_NotificarFalha( "Proximo nao aponta para elemento." ) ;
				return LIS_CondRetErroEstrutura ;
			} /* if */
		}

		if ( TST_CompararPonteiro( pElem , pLista->pOrigemLista ,
			"Origem não é apontado por cabeça da lista." ) != TST_CondRetOK )
		{
			return LIS_CondRetErroEstrutura ;
		} /* if */

	} else if ( pElem->pProx == NULL){ /* Elemento é fim da lista */

		if( pElem->pAnt != NULL) {
		
			if (  pElem->pAnt->pProx != pElem )
			{
				TST_NotificarFalha( "Anterior nao aponta para elemento." ) ;
				return LIS_CondRetErroEstrutura ;
			} /* if */
		}

		if ( TST_CompararPonteiro( pElem , pLista->pFimLista ,
			"Fim não é apontado por cabeça da lista." ) != TST_CondRetOK )
		{
			return LIS_CondRetErroEstrutura ;
		} /* if */

	} else { /* Elemento está no meio da lista */
		if ( (pElem->pProx->pAnt != pElem) && (pElem->pAnt->pProx != pElem) )
		{
			TST_NotificarFalha( "Encadeamento errado." ) ;
			return LIS_CondRetErroEstrutura ;
		} /* if */
	}

	/* Verificar elemento à esquerda */

	if ( pElem->pAnt != NULL )
	{
		if ( TST_CompararPonteiro( pElem->pCabeca , pElem->pAnt->pCabeca ,
			"Elemento à esquerda não pertence à mesma lista que este elemento." ) != TST_CondRetOK )
		{
			return LIS_CondRetErroEstrutura ;
		} /* if */
	} /* if */

	/* Verificar elemento à direita */

	if ( pElem->pProx != NULL )
	{ 
		if ( TST_CompararPonteiro( pElem->pCabeca , pElem->pProx->pCabeca ,
			"Elemento à direita não pertence à mesma lista que este elemento." ) != TST_CondRetOK )
		{
			return LIS_CondRetErroEstrutura ;
		} /* if */
	} /* if */

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Verificar um nó de estrutura */

#endif /* DEBUG */

/***************************************************************************
*
*  Função: LIS  &Verificar Lista
*  ****/

#ifdef _DEBUG

LIS_tpCondRet LIS_VerificarLista( void * pListaParm )
{

	LIS_tpLista * pLista = NULL ;
	
	if ( LIS_VerificarCabeca( pListaParm ) != LIS_CondRetOK )
	{
		return LIS_CondRetErroEstrutura ;
	} /* if */
	
	CED_MarcarEspacoAtivo( pListaParm ) ;

	pLista = (LIS_tpLista *) ( pListaParm ) ;
	
	if( (pLista->numElem != 0) && (pLista->pElemCorr == NULL)) {
		return LIS_CondRetErroEstrutura;
	}

	return VerificarElem( pLista->pElemCorr ) ; 

} /* Fim função: LIS  &Verificar Lista */

#endif /* DEBUG */

/***************************************************************************
*
*  Função: LIS  &Verificar cabeça
*  ****/

#ifdef _DEBUG

LIS_tpCondRet LIS_VerificarCabeca( void * pCabecaParm )
{

	LIS_tpLista * pLista = NULL ;

	/* Verifica o tipo do espaço */
	
	if ( pCabecaParm == NULL )
	{
		TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
		return LIS_CondRetErroEstrutura ;
	} /* if */

	if ( ! CED_VerificarEspaco( pCabecaParm , NULL ))
	{
		TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
		return LIS_CondRetErroEstrutura ;
	} /* if */

	if ( TST_CompararInt( LIS_TipoEspacoCabeca ,
		CED_ObterTipoEspaco( pCabecaParm ) ,
		"Tipo do espaço de dados não é cabeça de uma lista." ) != TST_CondRetOK )
	{
		return LIS_CondRetErroEstrutura ;
	} /* if */

	pLista = ( LIS_tpLista * )( pCabecaParm ) ;

	/* Verifica origem da lista */

	if ( pLista->pOrigemLista != NULL )
	{
		if ( TST_CompararPonteiro( pCabecaParm , pLista->pOrigemLista->pCabeca ,
			"Origem não aponta para cabeça." ) != TST_CondRetOK )
		{   
			return LIS_CondRetErroEstrutura ;
		} /* if */
	} else {
		if ( TST_CompararPonteiro( NULL , pLista->pElemCorr ,
			"Lista vazia tem elemento corrente não NULL." ) != TST_CondRetOK )
		{
			return LIS_CondRetErroEstrutura ;
		} /* if */
	} /* if */

	/* Verifica fim da lista */

	if ( pLista->pFimLista != NULL )
	{
		if ( TST_CompararPonteiro( pCabecaParm , pLista->pFimLista->pCabeca ,
			"Fim não aponta para cabeça." ) != TST_CondRetOK )
		{
			return LIS_CondRetErroEstrutura ;
		} /* if */
	} else {
		if ( TST_CompararPonteiro( NULL , pLista->pElemCorr ,
			"Lista vazia tem elemento corrente não NULL." ) != TST_CondRetOK )
		{
			return LIS_CondRetErroEstrutura ;
		} /* if */
	} /* if */
	/* Verifica elemento corrente */

	if ( pLista->pElemCorr != NULL )
	{
		if ( TST_CompararPonteiro( pCabecaParm , pLista->pElemCorr->pCabeca ,
			"Elemento corrente não aponta para cabeça." ) != TST_CondRetOK )
		{
			return LIS_CondRetErroEstrutura ;
		} /* if */
	} else {
		if ( TST_CompararPonteiro( NULL , pLista->pOrigemLista ,
			"Lista não vazia tem elemento corrente NULL." ) != TST_CondRetOK )
		{
			return LIS_CondRetErroEstrutura ;
		} /* if */
	} /* if */

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Verificar cabeça */

#endif /* DEBUG */

/***************************************************************************
*
*  Função: LIS  &Verificar espaço
*  ****/

#ifdef _DEBUG

LIS_tpCondRet LIS_VerificarEspaco( LIS_tppLista pLista, int iTipoEspaco) {

	switch( iTipoEspaco) {

		case LIS_TipoEspacoCabeca:
			return LIS_VerificarCabeca( pLista);
			break;
		case LIS_TipoEspacoElem:
			return VerificarElem(pLista->pElemCorr);
			break;
		default:
			return LIS_CondRetErro;
			break;
	}
} /* Fim função: LIS  &Verificar espaço */

#endif
/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

void LiberarElemento( LIS_tppLista   pLista ,
					 tpElemLista  * pElem   )
{
	if( pElem != NULL ) {
		free( pElem ) ;
	}

	pLista->numElem-- ;

} /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

tpElemLista * CriarElemento( LIS_tppLista pLista , void * pValor  )
{

	tpElemLista * pElem ;

	pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
	if ( pElem == NULL )
	{
		return NULL ;
	} /* if */

	pElem->pValor = pValor ;
	pElem->pAnt   = NULL  ;
	pElem->pProx  = NULL  ;

	pLista->numElem ++ ;

#ifdef _DEBUG
	pElem->pCabeca = pLista;
	CED_DefinirTipoEspaco( pElem , LIS_TipoEspacoElem ) ;
#endif

	return pElem ;

} /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

void LimparCabeca( LIS_tppLista pLista )
{

	pLista->pOrigemLista = NULL ;
	pLista->pFimLista = NULL ;
	pLista->pElemCorr = NULL ;
	pLista->numElem   = 0 ;

} /* Fim função: LIS  -Limpar a cabeça da lista */

/***********************************************************************
*
*  $FC Função: LIS  &VerificarNumElem
**
*  $ED Descrição da função
*     Confere se o campo numElem da lista corresponde ao numero de elementos
*     efetivamente encadeados.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista 
*
*  $FV Valor retornado
*     LIS_CondRetOK - Campo numElem da lista esta correto
*     LIS_CondRetErro - Campo numElem da lista esta errado
*
***********************************************************************/

LIS_tpCondRet VerificarNumElem( LIS_tppLista pLista ) {

	int iNumElem = 0;
	tpElemLista * pElem;

	if( pLista == NULL) { /* Verifica se ponteiro para lista é válido */

		TRF_TratarPonteiroNuloLista(pLista) ;	
	}         

	pElem = pLista->pOrigemLista;
	for(pElem ; pElem != NULL ; pElem = pElem->pProx) {
		iNumElem++;
	}
	if( iNumElem != pLista->numElem) {
		return LIS_CondRetErro;
	}

	return LIS_CondRetOK;

} /* Fim função: LIS  -Verificar NumElem */


/***********************************************************************
*
*  $FC Função: LIS  &VerificarEncadeamentoLista
*
*  $ED Descrição da função
*     Verifica se o encadeamento da lista esta correto
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista 
*
*  $FV Valor retornado
*     LIS_CondRetOK - Se encadeamento da lista esta correto
*     LIS_CondRetErro - Se encadeamento da lista esta errado
*
***********************************************************************/

LIS_tpCondRet VerificarEncadeamento( LIS_tppLista pLista) {
	if((pLista != NULL) && (pLista->pElemCorr != NULL)){

		if( pLista->pElemCorr->pAnt != NULL ) {

			if ( pLista->pElemCorr->pAnt->pProx !=
				pLista->pElemCorr) {

					return LIS_CondRetErro;
			}
		}


		if( pLista->pElemCorr->pProx != NULL ) {
			if ( pLista->pElemCorr->pProx->pAnt !=
				pLista->pElemCorr) {

					return LIS_CondRetErro;
			}
		}
	}
	return LIS_CondRetOK;

} /* Fim função: LIS -Verificar encadeamento */

/***********************************************************************
*
*  $FC Função: LIS  &VerificarOrigemListaLista
*
*  $ED Descrição da função
*     Procura o elemento inicial de uma lista.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista 
*
*  $FV Valor retornado
*     Ponteiro para a origem da lista.
*     NULL, se o ponteiro para a lista é null, ou se ela está vazia. 
*
***********************************************************************/
#ifdef _DEBUG

tpElemLista* VerificarOrigemLista( LIS_tppLista pLista ){

	tpElemLista * pElem;
	if( (pLista == NULL) || ( pLista->pElemCorr == NULL) ){	/* Lista inválida ou lista vazia */
		return NULL;
	}
	
	pElem = pLista->pElemCorr;
	while(pElem->pAnt != NULL) { /* Percorre lista até chegar em seu primeiro elemento */
		pElem = pElem->pAnt;
	}

	return pElem;

} /* Fim função: LIS -Verificar Origem Lista */

#endif /* DEBUG */

/***********************************************************************
*
*  $FC Função: LIS  &VerificarFimLista
*
*  $ED Descrição da função
*     Procura o elemento final de uma lista.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista 
*
*  $FV Valor retornado
*     Ponteiro para o fim da lista.
*     NULL, se o ponteiro para a lista é null, ou se ela está vazia. 
*
***********************************************************************/
#ifdef _DEBUG

tpElemLista* VerificarFimLista( LIS_tppLista pLista ){

	tpElemLista * pElem;
	if( ( pLista == NULL ) || ( pLista->pElemCorr == NULL ) ){	/* Lista inválida ou lista vazia */
		return NULL;
	}

	pElem = pLista->pElemCorr;
	while(pElem->pProx != NULL) { /* Percorre lista até chegar em seu ultimo elemento */
		pElem = pElem->pProx;
	}

	return pElem;

} /* Fim função: LIS -Verificar Fim Lista */

#endif /* DEBUG */


/***********************************************************************
*
*  $FC Função: LIS  -Explorar verificando os nós de uma lista
*
*  $ED Descrição da função
*     Percorre recursivamente a lista verificando os elememtos à medida que forem
*     visitados. Caso seja encontrado alguma falha, a verificação será
*     suspensa. Portanto, no caso de falha, é possível que nem todos
*     os elementos da lista sejam visitados.
*
***********************************************************************/

#ifdef _DEBUG

LIS_tpCondRet VerificarElem( tpElemLista * pElem )
{

	tpElemLista* pElemAux; 
	LIS_tpCondRet CondErro = LIS_CondRetOK ;
	
	if ( pElem == NULL )
	{
		return LIS_CondRetOK ;
	} /* if */
	
	for(pElemAux = pElem; pElemAux != NULL; pElemAux = pElemAux->pAnt) {
		
		CED_MarcarEspacoAtivo( pElemAux ) ;
		CondErro = LIS_VerificarElem( pElemAux ) ;
		if( CondErro != LIS_CondRetOK ){
			return CondErro;
		}
	}

	for(pElemAux = pElem; pElemAux != NULL; pElemAux = pElemAux->pProx) {
		
		CED_MarcarEspacoAtivo( pElemAux ) ;
		CondErro = LIS_VerificarElem( pElemAux ) ;
		if( CondErro != LIS_CondRetOK ){
			return CondErro;
		}
	}

	return CondErro ;

} /* Fim função: LIS  -Explorar verificando os elementos de uma lista */

#endif /* _DEBUG */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/