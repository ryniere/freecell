/***************************************************************************
* 
*  $MCD Módulo de definição: CBSE ColunaBase
*
*  Arquivo gerado:              COLUNA_BASE.H
*  Letras identificadoras:      CBSE
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
***************************************************************************/

#include <stdio.h>
#include <string.h>

#define ColunaBase_OWN
#include "COLUNA_BASE.H"
#undef ColunaBase_OWN



/***** Protótipos das funções encapuladas no módulo *****/

static COR_tpCondRet ImprimirColunaBase(LIS_tppLista pListaColunaBase, int ixIndice);

static COR_tpCondRet InserirCartaColunaBase( LIS_tppLista pListaColunaBase, 
											 CRT_ptpCarta ptpCarta );

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: CBSE  &Criar colunas bases
*****/

COR_tpCondRet CBSE_CriarColunasBase()
{
	/* Cria as 4 colunas base */
	CBSE_ColunaBaseCopas = LIS_CriarLista();

	CBSE_ColunaBaseEspadas = LIS_CriarLista();

	CBSE_ColunaBaseOuros = LIS_CriarLista();

	CBSE_ColunaBasePaus = LIS_CriarLista();
	/* Verifica se colunas base foram criadas corretamente */
	if( (CBSE_ColunaBaseCopas == NULL) ||
		(CBSE_ColunaBaseEspadas == NULL) ||
		(CBSE_ColunaBaseOuros == NULL) ||
		(CBSE_ColunaBasePaus == NULL)) {
			return COR_CondRetErro;
	}
	
	return COR_CondRetOK;

} /* Fim função: CBSE  &Criar Colunas Base */

/***********************************************************************
*
*  $FC Função: CBSE  &Inserir Carta na coluna base
*****/

COR_tpCondRet CBSE_InserirCartaColunasBases( CRT_ptpCarta ptpCarta, int ixIndice)
{
	if(ptpCarta == NULL){ /* Carta invalida */
		return COR_CondRetErro;
	}

	switch( ixIndice ) {
		/* Caso coluna de Copas recebe a carta */
		case CBSE_IndiceColunaCopas:
			/* Verifica se o naipe da carta corresponde ao da coluna */
			if( strcmp( CRT_ObterNaipeCarta( ptpCarta ), CRT_STRING_COPAS ) != 0 ) {
				return COR_CondRetAtoProibido;
			}
			
			return InserirCartaColunaBase(CBSE_ColunaBaseCopas, ptpCarta );
			break;
		
		/* Caso coluna de Espadas */
		case CBSE_IndiceColunaEspadas:
			/* Verifica se o naipe da carta corresponde ao da coluna */
			if( strcmp( CRT_ObterNaipeCarta( ptpCarta ), CRT_STRING_ESPADAS ) != 0 ) {
				return COR_CondRetAtoProibido;
			}

			return InserirCartaColunaBase(CBSE_ColunaBaseEspadas, ptpCarta );
			break;
		/* Caso coluna de Ouros */
		case CBSE_IndiceColunaOuros:
			/* Verifica se o naipe da carta corresponde ao da coluna */
			if( strcmp( CRT_ObterNaipeCarta( ptpCarta ), CRT_STRING_OUROS ) != 0 ) {
				return COR_CondRetAtoProibido;
			}

			return InserirCartaColunaBase(CBSE_ColunaBaseOuros, ptpCarta );
			break;
		/* Caso coluna de Paus */
		case CBSE_IndiceColunaPaus:
			/* Verifica se o naipe da carta corresponde ao da coluna */
			if( strcmp( CRT_ObterNaipeCarta( ptpCarta ), CRT_STRING_PAUS ) != 0 ) {
				return COR_CondRetAtoProibido;
			}

			return InserirCartaColunaBase(CBSE_ColunaBasePaus, ptpCarta );
			break;
		/* Caso indice não corresponda a nenhuma coluna base */
		default:
			return COR_CondRetErro;
	}
    
} 

/***********************************************************************
*
*  $FC Função: CBSE  &Imprimir colunas bases
*****/

COR_tpCondRet CBSE_ImprimirColunasBases()
{

	printf("\nColunas Bases:\n");
	/* Imprime coluna de copas */
	if( ImprimirColunaBase( CBSE_ColunaBaseCopas, CBSE_IndiceColunaCopas ) != COR_CondRetOK){

         return COR_CondRetErro;
	}
	/* Imprime coluna de espadas */
	if( ImprimirColunaBase( CBSE_ColunaBaseEspadas, CBSE_IndiceColunaEspadas ) != COR_CondRetOK){

		return COR_CondRetErro;
	}
	/* Imprime coluna de ouros */
	if( ImprimirColunaBase( CBSE_ColunaBaseOuros, CBSE_IndiceColunaOuros ) != COR_CondRetOK){

		return COR_CondRetErro;
	}
	/* Imprime coluna de paus */
	if( ImprimirColunaBase( CBSE_ColunaBasePaus, CBSE_IndiceColunaPaus ) != COR_CondRetOK){

		return COR_CondRetErro;
	}
	printf("\n");

	return COR_CondRetOK;

} /* Fim função: CBSE  &Imprimir Colunas Bases */

/***********************************************************************
*
*  $FC Função: CBSE  &Destruir Colunas Base
*****/

COR_tpCondRet CBSE_DestruirColunasBase()
{
	/* Destroi lista correspondente as 4 colunas base */
	LIS_DestruirLista(CBSE_ColunaBaseCopas);
	CBSE_ColunaBaseCopas=NULL;
	LIS_DestruirLista(CBSE_ColunaBaseEspadas);
	CBSE_ColunaBaseEspadas=NULL;
	LIS_DestruirLista(CBSE_ColunaBaseOuros);
	CBSE_ColunaBaseOuros=NULL;
	LIS_DestruirLista(CBSE_ColunaBasePaus);
	CBSE_ColunaBasePaus=NULL;
	/* Verifica se colunas foram destruidas */
	if( (  CBSE_ColunaBaseCopas  != NULL ) || (  CBSE_ColunaBaseEspadas  != NULL ) || (  CBSE_ColunaBaseOuros  != NULL ) || 
		(  CBSE_ColunaBasePaus  != NULL )  ){			

			return COR_CondRetErro;/* Erro ao destruir lista  */
	}

	return COR_CondRetOK;

} /* Fim função: CBSE  &Destruir Colunas Bases */

/***********************************************************************
*
*  $FC Função: CBSE  &Obter Carta Coluna Base
*****/

CRT_ptpCarta CBSE_ObterCartaColunaBase( int ixIndiceColuna )
{
	LIS_tppLista pColuna;
	CRT_ptpCarta pCartaAuxiliar;
	
	switch(ixIndiceColuna) {
		/* Caso coluna de Copas */
		case CBSE_IndiceColunaCopas:
			pColuna = CBSE_ColunaBaseCopas;
			break;
		/* Caso coluna de Espadas */
		case CBSE_IndiceColunaEspadas:
			pColuna = CBSE_ColunaBaseEspadas;
			break;
		/* Caso coluna de Ouros */	
		case CBSE_IndiceColunaOuros:
			pColuna = CBSE_ColunaBaseOuros;
			break;
		/* Caso coluna de Paus */
		case CBSE_IndiceColunaPaus:
			pColuna = CBSE_ColunaBasePaus;
			break;
		/* Caso indice nao corresponte a nenhuma coluna base */
		default:
			return NULL;
	}
	/* Obtem carta */
	pCartaAuxiliar = (CRT_ptpCarta)LIS_ObterValor(pColuna);

	return pCartaAuxiliar;
} /* Fim função: CBSE  &Obter Carta Coluna Base */

/***********************************************************************
*
*  $FC Função: CBSE  &Ir Final Coluna Base
*****/

COR_tpCondRet CBES_IrFinalColunaBase( int ixIndice){

	LIS_tppLista pColuna;
	
		switch(ixIndice) {
		/* Caso coluna de Copas */
		case CBSE_IndiceColunaCopas:
			pColuna = CBSE_ColunaBaseCopas;
			break;
		/* Caso coluna de Espadas */
		case CBSE_IndiceColunaEspadas:
			pColuna = CBSE_ColunaBaseEspadas;
			break;
		/* Caso coluna de Ouros */
		case CBSE_IndiceColunaOuros:
			pColuna = CBSE_ColunaBaseOuros;
			break;
		/* Caso coluna de Paus */
		case CBSE_IndiceColunaPaus:
			pColuna = CBSE_ColunaBasePaus;
			break;
		/* Caso indice nao correponda a nenhuma coluna base */
		default:
			return COR_CondRetErro;
	}
		/* Verifica se ponteiro para coluna é valido */
		if( pColuna == NULL ){

			return COR_CondRetErro;
		}
		/* Posiciona elemento corrente na ultima carta da coluna */
		LIS_IrFinalLista(pColuna);
		return COR_CondRetOK;

} /* Fim função: CBSE  &Ir Final Coluna Base */

/***********************************************************************
*
*  $FC Função: CBSE  &Ir Final Coluna Base
*****/

COR_tpCondRet CBES_IrInicioColunaBase( int ixIndice){

	LIS_tppLista pColuna;

	switch(ixIndice) {
		/* Caso coluna de Copas */
		case CBSE_IndiceColunaCopas:
			pColuna = CBSE_ColunaBaseCopas;
			break;
		/* Caso coluna de Espadas */
		case CBSE_IndiceColunaEspadas:
			pColuna = CBSE_ColunaBaseEspadas;
			break;
		/* Caso coluna de Ouros */
		case CBSE_IndiceColunaOuros:
			pColuna = CBSE_ColunaBaseOuros;
			break;
		/* Caso coluna de Paus */
		case CBSE_IndiceColunaPaus:
			pColuna = CBSE_ColunaBasePaus;
			break;
		/* Caso indice nao correponda a nenhuma coluna base */
		default:
			return COR_CondRetErro;
	}
		/* Verifica se ponteiro para coluna é valido */
		if( pColuna == NULL ){

			return COR_CondRetErro;
		}
	/* Posiciona elemento corrente na primeira carta da coluna */
	LIS_IrInicioLista(pColuna);
	return COR_CondRetOK;

} /* Fim função: CBSE  &Ir Final Coluna Base */

/***********************************************************************
*
*  $FC Função: CBSE  &Avançar Elem Corr Coluna Base
*****/
 
COR_tpCondRet CBSE_AvancarElemCorrColunaBase( CBSE_IndiceColunasBase ixIndice, int numElem) {

	LIS_tppLista pColuna;

		switch(ixIndice) {
		/* Caso coluna de Copas */
		case CBSE_IndiceColunaCopas:
			pColuna = CBSE_ColunaBaseCopas;
			break;
		/* Caso coluna de Espadas */
		case CBSE_IndiceColunaEspadas:
			pColuna = CBSE_ColunaBaseEspadas;
			break;
		/* Caso coluna de Ouros */
		case CBSE_IndiceColunaOuros:
			pColuna = CBSE_ColunaBaseOuros;
			break;
		/* Caso coluna de Paus */
		case CBSE_IndiceColunaPaus:
			pColuna = CBSE_ColunaBasePaus;
			break;
		/* Caso indice nao correponda a nenhuma coluna base */
		default:
			return COR_CondRetErro;
	}
		/* Verifica se ponteiro para coluna é valido */
		if( pColuna == NULL ){

			return COR_CondRetErro;
		}
		/* Avança elemento corrente da coluna até posicao desejada */
		if( LIS_AvancarElementoCorrente( pColuna , numElem ) != LIS_CondRetOK ) {
			return COR_CondRetErro;
		}

		return COR_CondRetOK;

} /* Fim função: CBSE  &Avançar Elem Corr Coluna Base*/

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: CBSE -Imprimir Coluna Base
*
*  $ED Descrição da função
*		A função ImprimirColunaBase imprime a ultima carta de uma coluna base
*
*  $EP Parâmetros
*		pListaColunaBase - ponteiro para a coluna base a ser impressa
*		ixIndice - indice indicando a coluna a ser impressa
*   
*  $FV tipo retornado
*		COR_CondRetOK, se a coluna foi impressa corretamente.
*		COR_CondRetErro, se ocorreu algum erro.
*
***********************************************************************/

COR_tpCondRet ImprimirColunaBase(LIS_tppLista pListaColunaBase, int ixIndice){

	CRT_ptpCarta ptpCarta;

	if(pListaColunaBase==NULL){

		return COR_CondRetErro;
	}

	LIS_IrFinalLista( pListaColunaBase ); /* Posiciona o elemento corrente da lista no final */
	ptpCarta = ( CRT_ptpCarta )LIS_ObterValor( pListaColunaBase ); /* Obtêm valor do ultimo
																	elemento da lista*/
    	
	if( ptpCarta == NULL ) {
		switch( ixIndice ) {
			
			case CBSE_IndiceColunaCopas:
				printf(" |   COPAS    |");
				break;
			case CBSE_IndiceColunaEspadas:
				printf(" |  ESPADAS   |");
				break;
			case CBSE_IndiceColunaOuros:
				printf(" |   OUROS    |");
				break;
			case CBSE_IndiceColunaPaus:
				printf(" |    PAUS    |"); 
				break;
			default:
				return COR_CondRetErro;
		}

	} else {
	
		CRT_ImprimirCarta(ptpCarta);
	}
	return COR_CondRetOK;

} /* Fim função: CBSE  &Imprimir Coluna Base */

/***********************************************************************
*
*  $FC Função: CBSE  &Inserir Carta na coluna base
*
*  $ED Descrição da função
*		A função InserirCartaColunaBase insere uma carta na ultima posição
*       da coluna se ela pertencer a sequencia.	
*
*  $EP Parâmetros
*		pListaColunaBase - Lista da coluna a se inserir a carta.
*       ptpCarta - Carta a ser inserida 
*
*  $FV tipo retornado
*	    Se executou corretamente retorna BSE_CondRetOK.
*       Se ocorreu algum erro, a função retornará BSE_CondRetErro.
*      
*		 Não será dada mais informação quanto ao problema ocorrido.
***********************************************************************/

COR_tpCondRet InserirCartaColunaBase( LIS_tppLista pListaColunaBase, CRT_ptpCarta ptpCarta ){

	CRT_ptpCarta ptpUltimaCarta;
	
	if(ptpCarta == NULL){ /* Carta invalida */
		return COR_CondRetErro;
	}

	if( LIS_VerificarEstruturaLista ( pListaColunaBase) != LIS_CondRetOK ) {
		return COR_CondRetErro;
	} /* Verificação estrutural da lista */

	if(pListaColunaBase == NULL){

		return COR_CondRetErro;

	}
    
	LIS_IrFinalLista( pListaColunaBase ); /* Posiciona o elemento corrente da lista no final */
	/* Obtêm valor do ultimo elemento da lista*/ 
	ptpUltimaCarta = ( CRT_ptpCarta )LIS_ObterValor( pListaColunaBase );

	/* Testa se coluna base está vazia e carta a ser inserida é um Ás */
	if ( ( ptpUltimaCarta == NULL ) && ( CRT_ObterValorCarta( ptpCarta ) == 1 ) ){
         
		LIS_InserirElementoAntes( pListaColunaBase, ptpCarta );

		if( LIS_VerificarEstruturaLista ( pListaColunaBase) != LIS_CondRetOK ) {
			return COR_CondRetErro;
		} /* Verificação estrutural da lista */

		return COR_CondRetOK;
	}
	
	/* Testa se valor da carta é o maior seguinte ao valor da ultima carta da coluna */
	if( ( CRT_ObterValorCarta( ptpUltimaCarta ) + 1 ) == CRT_ObterValorCarta( ptpCarta ) ){
		LIS_InserirElementoApos( pListaColunaBase, ptpCarta );
		
		if( LIS_VerificarEstruturaLista ( pListaColunaBase) != LIS_CondRetOK ) {
			return COR_CondRetErro;
		} /* Verificação estrutural da lista */

		return COR_CondRetOK;
	}

	if( LIS_VerificarEstruturaLista ( pListaColunaBase) != LIS_CondRetOK ) {
		return COR_CondRetErro;
	} /* Verificação estrutural da lista */

	return COR_CondRetAtoProibido;

} /* Fim função: CBSE  &Inserir Carta Coluna Base */


/********** Fim do módulo de implementação: CBSE Coluna Base **********/