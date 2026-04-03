/***************************************************************************
*  $MCI Módulo de implementação: CALT Colunas Aleatorias
*
*  Arquivo gerado:              SEQUENCIA_ALEATORIA.c
*  Letras identificadoras:      CALT
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
***************************************************************************/


#define ColunasAleatorias_OWN
#include "COLUNAS_ALEATORIAS.H"
#undef ColunasAleatorias_OWN



/***** Protótipos das funções encapsuladas no módulo *****/

static COR_tpCondRet InserirCartaAleatoria(LIS_tppLista sequencia, int ixIndice);

static COR_tpCondRet InserirCartaSequencia( CRT_ptpCarta pCarta, LIS_tppLista pColuna);

static CRT_ptpCarta RetirarCartaSequencia( LIS_tppLista  pColuna);

static int ImprimeLinhaColunaAleatoria(LIS_tppLista pColuna);


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: CALT  &Criar Colunas Aleatorias
*  ****/

COR_tpCondRet CALT_CriarColunasAleatorias() {
	
		
	CALT_coluna1 = LIS_CriarLista();
	if(  CALT_coluna1  == NULL ){			
		
		return COR_CondRetErro;/* Erro ao criar a lista 1 */
	}

	CALT_coluna2 = LIS_CriarLista();
	if(  CALT_coluna2  == NULL ){			

		return COR_CondRetErro;/* Erro ao criar a lista 2 */
	}

	CALT_coluna3 = LIS_CriarLista();
	if(  CALT_coluna3  == NULL ){			

		return COR_CondRetErro;/* Erro ao criar a lista 3 */
	}

	CALT_coluna4 = LIS_CriarLista();
	if(  CALT_coluna4  == NULL ){			

		return COR_CondRetErro;/* Erro ao criar a lista 4 */
	}

	CALT_coluna5 = LIS_CriarLista();
	if(  CALT_coluna5  == NULL ){			

		return COR_CondRetErro;/* Erro ao criar a lista 5 */
	}

	CALT_coluna6 = LIS_CriarLista();
	if(  CALT_coluna6  == NULL ){			

		return COR_CondRetErro;/* Erro ao criar a lista 6 */
	}

	CALT_coluna7 = LIS_CriarLista();
	if(  CALT_coluna7  == NULL ){			

		return COR_CondRetErro;/* Erro ao criar a lista 7 */
	}

	CALT_coluna8 = LIS_CriarLista();
	if(  CALT_coluna8  == NULL ){			

		return COR_CondRetErro;/* Erro ao criar a lista 8 */
	}

	return COR_CondRetOK;
} /* Fim função:  CALT  &Criar colunas Aleatorias */

/***************************************************************************
*
*  Função: CALT  &Destruir Colunas Aleatorias
*  ****/

COR_tpCondRet CALT_DestruirColunasAleatorias() {

	/* Destroi as 8 colunas aleatorias */
	LIS_DestruirLista(CALT_coluna1);
	CALT_coluna1=NULL;
	LIS_DestruirLista(CALT_coluna2);
	CALT_coluna2=NULL;
	LIS_DestruirLista(CALT_coluna3);
	CALT_coluna3=NULL;
	LIS_DestruirLista(CALT_coluna4);
	CALT_coluna4=NULL;
	LIS_DestruirLista(CALT_coluna5);
	CALT_coluna5=NULL;
	LIS_DestruirLista(CALT_coluna6);
	CALT_coluna6=NULL;
	LIS_DestruirLista(CALT_coluna7);
	CALT_coluna7=NULL;
	LIS_DestruirLista(CALT_coluna8);
	CALT_coluna8=NULL;

	/* Verifica se colunas foram destruidas corretamente */
	if( (  CALT_coluna1  != NULL ) || (  CALT_coluna2  != NULL ) || (  CALT_coluna3  != NULL ) || 
		(  CALT_coluna4  != NULL ) || (  CALT_coluna5  != NULL ) || (  CALT_coluna6  != NULL ) ||
		(  CALT_coluna7  != NULL ) || (  CALT_coluna8  != NULL ) ){			

		return COR_CondRetErro;/* Erro ao destruir a lista  */
	}

	return COR_CondRetOK;
} /* Fim função:  CALT  &Destruir Colunas Aleatorias */


/***************************************************************************
*
*  Função: CALT  &Inserir Carta Sequencia Coluna
*  ****/

COR_tpCondRet CALT_InserirCartaSequenciaColuna( CRT_ptpCarta pCarta, int ixIndice) {

	if(pCarta == NULL){ /* Carta invalida */
		return COR_CondRetErro;
	}

	if(ixIndice == 1){
		/* Caso coluna aleatoria 1*/
		return InserirCartaSequencia( pCarta, CALT_coluna1);
	}

	if(ixIndice == 2){
		/* Caso coluna aleatoria 2 */
		return InserirCartaSequencia( pCarta, CALT_coluna2);
	}
	if(ixIndice == 3){
		/* Caso coluna aleatoria 3 */
		return InserirCartaSequencia( pCarta, CALT_coluna3);
	}
	if(ixIndice == 4){
		/* Caso coluna aleatoria 4 */
		return InserirCartaSequencia( pCarta, CALT_coluna4);
	}
	if(ixIndice == 5){
		/* Caso coluna aleatoria 5 */
		return InserirCartaSequencia( pCarta, CALT_coluna5);
	}
	if(ixIndice == 6){
		/* Caso coluna aleatoria 6 */
		return InserirCartaSequencia( pCarta, CALT_coluna6);
	}
	if(ixIndice == 7){
		/* Caso coluna aleatoria 7 */
		return InserirCartaSequencia( pCarta, CALT_coluna7);
	}
	if(ixIndice == 8){
		/* Caso coluna aleatoria 8 */
		return InserirCartaSequencia( pCarta, CALT_coluna8);
	}

	return COR_CondRetErro;	/* Coluna não existe */

} /* Fim função:  CALT  &Inserir Carta Sequencia Coluna  */

/***************************************************************************
*
*  Função: CALT  &Retirar Carta Sequencia Coluna
*  ****/

CRT_ptpCarta CALT_RetirarCartaSequenciaColuna( int ixIndice ) {
	
	if(ixIndice == 1){
		/* Caso coluna aleatoria 1 */
		return RetirarCartaSequencia( CALT_coluna1 );
	}

	if(ixIndice == 2){
		/* Caso coluna aleatoria 2 */
		return RetirarCartaSequencia( CALT_coluna2 );
	}
	if(ixIndice == 3){
		/* Caso coluna aleatoria 3 */
		return RetirarCartaSequencia( CALT_coluna3 );
	}
	if(ixIndice == 4){
		/* Caso coluna aleatoria 4 */
		return RetirarCartaSequencia( CALT_coluna4 );
	}
	if(ixIndice == 5){
		/* Caso coluna aleatoria 5 */
		return RetirarCartaSequencia( CALT_coluna5 );
	}
	if(ixIndice == 6){
		/* Caso coluna aleatoria 6 */
		return RetirarCartaSequencia( CALT_coluna6 );
	}
	if(ixIndice == 7){
		/* Caso coluna aleatoria 7 */
		return RetirarCartaSequencia( CALT_coluna7 );
	}
	if(ixIndice == 8){
		/* Caso coluna aleatoria 8 */
		return RetirarCartaSequencia( CALT_coluna8 );
	}

	return NULL;	/* Coluna não existe */

} /* Fim função:  CALT  &Retirar Carta Sequencia */

/***************************************************************************
*
*  Função: CALT  &Imprimir Colunas Aleatorias
*  ****/

COR_tpCondRet CALT_ImprimirColunasAleatorias() {
	
	int bColuna1=1,
		bColuna2=1,
		bColuna3=1,
		bColuna4=1,
		bColuna5=1,
		bColuna6=1,
		bColuna7=1,
		bColuna8=1;
	/* Verifica se colunas aleatorias existem */
	if( ( CALT_coluna1 == NULL ) || ( CALT_coluna2 == NULL ) || ( CALT_coluna3 == NULL ) ||
		 ( CALT_coluna4 == NULL ) || ( CALT_coluna5 == NULL ) || ( CALT_coluna6 == NULL ) ||
		  ( CALT_coluna7 == NULL ) || ( CALT_coluna8 == NULL ) ){

		return COR_CondRetErro;
	}
	/* Posiciona elemento corrente na primeira carta de todas as colunas aleatorias */
	LIS_IrInicioLista( CALT_coluna1 );
	LIS_IrInicioLista( CALT_coluna2 );
	LIS_IrInicioLista( CALT_coluna3 );
	LIS_IrInicioLista( CALT_coluna4 );
	LIS_IrInicioLista( CALT_coluna5 );
	LIS_IrInicioLista( CALT_coluna6 );
	LIS_IrInicioLista( CALT_coluna7 );
	LIS_IrInicioLista( CALT_coluna8 );
	/* Imprime colunas aleatorias */
    printf("COLUNAS ALEATORIAS\n");
	do {
		if(bColuna1==1){

			bColuna1=ImprimeLinhaColunaAleatoria(CALT_coluna1);
		}
		else{
			printf("         ");
		}

		if(bColuna2==1){
			bColuna2=ImprimeLinhaColunaAleatoria(CALT_coluna2);
		}
		else{
			printf("         ");
		}

		if(bColuna3==1){
			bColuna3=ImprimeLinhaColunaAleatoria(CALT_coluna3);
		}
		else{
			printf("         ");
		}

		if(bColuna4==1){
			bColuna4=ImprimeLinhaColunaAleatoria(CALT_coluna4);
		}
		else{
			printf("         ");
		}

		if(bColuna5==1){
			bColuna5=ImprimeLinhaColunaAleatoria(CALT_coluna5);
		}
		else{
			printf("         ");
		}

		if(bColuna6==1){
			bColuna6=ImprimeLinhaColunaAleatoria(CALT_coluna6);
		}
		else{
			printf("         ");
		}

		if(bColuna7==1){
			bColuna7=ImprimeLinhaColunaAleatoria(CALT_coluna7);
		}
		else{
			printf("         ");
		}

		if(bColuna8){
			bColuna8=ImprimeLinhaColunaAleatoria(CALT_coluna8);
		}
		else{
			printf("         ");
		}

		printf("\n");/* Pula para a proxima linha das colunas */


	}while( ( bColuna1 ) || ( bColuna2 ) || ( bColuna3 ) || ( bColuna4 ) || 
		( bColuna5 ) || ( bColuna6 ) || ( bColuna7 ) || ( bColuna8 ) );


	return COR_CondRetOK;

}  /* Fim função:  CALT  &Imprimir Colunas Aleatorias */

/***************************************************************************
*
*  Função: CALT  &Preencher Colunas Aleatorias
*  ****/

COR_tpCondRet CALT_PreencherColunasAleatorias()
{
	int iCondRet, ixIndice = 0;
	
	while(ixIndice < QTD_CARTAS) { /* Insere um carta em cada sequencia 
								   até que o baralho acabe */
        
		iCondRet = InserirCartaAleatoria(CALT_coluna1, ixIndice);
		
		if( iCondRet == COR_CondRetErro) {	/* Erro ao inserir a carta */
			return COR_CondRetErro;
		}
		ixIndice++;
		if(ixIndice == QTD_CARTAS) {	/* Fim do baralho, sai do while */
			break;
		}

		iCondRet = InserirCartaAleatoria(CALT_coluna2, ixIndice);
		if( iCondRet == COR_CondRetErro) {	/* Erro ao inserir a carta */
			return COR_CondRetErro;
		}
		ixIndice++;
		if(ixIndice == QTD_CARTAS) {	/* Fim do baralho, sai do while */
			break;
		}

		iCondRet = InserirCartaAleatoria(CALT_coluna3, ixIndice);
		if( iCondRet == COR_CondRetErro) {	/* Erro ao inserir a carta */
			return COR_CondRetErro;
		}
		ixIndice++;
		if(ixIndice == QTD_CARTAS) {	/* Fim do baralho, sai do while */
			break;
		}

		iCondRet = InserirCartaAleatoria(CALT_coluna4, ixIndice);
		if( iCondRet == COR_CondRetErro) {	/* Erro ao inserir a carta */
			return COR_CondRetErro;
		}
		ixIndice++;
		if(ixIndice == QTD_CARTAS) {	/* Fim do baralho, sai do while */
			break;
		}

		iCondRet = InserirCartaAleatoria(CALT_coluna5, ixIndice);
		if( iCondRet == COR_CondRetErro) {	/* Erro ao inserir a carta */
			return COR_CondRetErro;
		}
		ixIndice++;
		if(ixIndice == QTD_CARTAS) {	/* Fim do baralho, sai do while */
			break;
		}

		iCondRet = InserirCartaAleatoria(CALT_coluna6, ixIndice);
		if( iCondRet == COR_CondRetErro) {	/* Erro ao inserir a carta */
			return COR_CondRetErro;
		}
		ixIndice++;
		if(ixIndice == QTD_CARTAS) {	/* Fim do baralho, sai do while */
			break;
		}

		iCondRet = InserirCartaAleatoria(CALT_coluna7, ixIndice);
		if( iCondRet == COR_CondRetErro) {	/* Erro ao inserir a carta */
			return COR_CondRetErro;
		}
		ixIndice++;
		if(ixIndice == QTD_CARTAS) {	/* Fim do baralho, sai do while */
			break;
		}

		iCondRet = InserirCartaAleatoria(CALT_coluna8, ixIndice);
		if( iCondRet == COR_CondRetErro) {	/* Erro ao inserir a carta */
			return COR_CondRetErro;
		}
		ixIndice++;
		if(ixIndice == QTD_CARTAS) {	/* Fim do baralho, sai do while */
			break;
		}
	}	
return COR_CondRetOK;

} /* Fim função:  CALT  &Preencher Colunas Aleatorias */

/***************************************************************************
*
*  Função: CALT  &Inserir Carta Coluna
*  ****/

COR_tpCondRet CALT_InserirCartaColuna( CRT_ptpCarta pCarta, int ixIndice) {

	if(pCarta == NULL){ /* Carta invalida */
		return COR_CondRetErro;
	}

	/* Verifica se indice é valido */
	if( (ixIndice < 1 ) || (ixIndice > 8)) {
		return COR_CondRetErro;
	}

	if(ixIndice == 1){
		/* Caso coluna aleatoria 1 */
		if( LIS_InserirElementoAntes(CALT_coluna1, pCarta) != LIS_CondRetOK){
			return COR_CondRetErro;
		}
	}

	if(ixIndice == 2){
		/* Caso coluna aleatoria 2 */
		if( LIS_InserirElementoAntes(CALT_coluna2, pCarta) != LIS_CondRetOK){
			return COR_CondRetErro;
		}
	}
	if(ixIndice == 3){
		/* Caso coluna aleatoria 3 */
		if(LIS_InserirElementoAntes(CALT_coluna3, pCarta) != LIS_CondRetOK) {
			return COR_CondRetErro;
		}
	}
	if(ixIndice == 4){
		/* Caso coluna aleatoria 4 */
		if(LIS_InserirElementoAntes(CALT_coluna4, pCarta) != LIS_CondRetOK) {
			return COR_CondRetErro;
		}
	}
	if(ixIndice == 5){
		/* Caso coluna aleatoria 5 */
		if(LIS_InserirElementoAntes(CALT_coluna5, pCarta) != LIS_CondRetOK) {
			return COR_CondRetErro;
		}
	}
	if(ixIndice == 6){
		/* Caso coluna aleatoria 6*/
		if(LIS_InserirElementoAntes(CALT_coluna6, pCarta) != LIS_CondRetOK) {
			return COR_CondRetErro;
		}
	}
	if(ixIndice == 7){
		/* Caso coluna aleatoria 7 */
		if(LIS_InserirElementoAntes(CALT_coluna7, pCarta) != LIS_CondRetOK) {
			return COR_CondRetErro;
		}
	}
	if(ixIndice == 8){
		/* Caso coluna aleatoria 8 */
		if(LIS_InserirElementoAntes(CALT_coluna8, pCarta) != LIS_CondRetOK) {
			return COR_CondRetErro;
		}
	}

	return COR_CondRetOK;	

} /* Fim função:  CALT  &Inserir Carta Coluna  */

/***************************************************************************
*
*  Função: CALT  &Obter Carta Coluna Aleatória
*  ****/


CRT_ptpCarta CALT_ObterCartaColunaAleatoria( int ixIndiceColuna )
{
	LIS_tppLista pColuna;
	CRT_ptpCarta pCartaAuxiliar;

	switch(ixIndiceColuna) {
		/* Caso coluna aleatoria 1 */
		case 1:
			pColuna = CALT_coluna1;
			break;
		/* Caso coluna aleatoria 2 */
		case 2:
			pColuna = CALT_coluna2;
			break;
		/* Caso coluna aleatoria 3 */
		case 3:
			pColuna = CALT_coluna3;
			break;
		/* Caso coluna aleatoria 4 */
		case 4:
			pColuna = CALT_coluna4;
			break;
		/* Caso coluna aleatoria 5 */
		case 5:
			pColuna = CALT_coluna5;
			break;
		/* Caso coluna aleatoria 6 */
		case 6:
			pColuna = CALT_coluna6;
			break;
		/* Caso coluna aleatoria 7 */
		case 7:
			pColuna = CALT_coluna7;
			break;
		/* Caso coluna aleatoria 8 */
		case 8:
			pColuna = CALT_coluna8;
			break;
		/* Caso indice coluna aleatoria seja invalido */
		default:
			return NULL;
	}

	/* Obtem carta */
	pCartaAuxiliar = (CRT_ptpCarta)LIS_ObterValor(pColuna);

	return pCartaAuxiliar;
}/* Fim função:  CALT  &Obter Carta Coluna Aleatoria  */

/***************************************************************************
*
*  Função: CALT  &Ir Final Coluna Aleatória
*  ****/


COR_tpCondRet CALT_IrFinalColunaAleatoria( int ixIndiceColuna )
{
	LIS_tppLista pColuna;

	switch(ixIndiceColuna) {
		/* Caso coluna aleatoria 1 */
		case 1:
			pColuna = CALT_coluna1;
			break;
		/* Caso coluna aleatoria 2 */
		case 2:
			pColuna = CALT_coluna2;
			break;
		/* Caso coluna aleatoria 3 */
		case 3:
			pColuna = CALT_coluna3;
			break;
		/* Caso coluna aleatoria 4 */
		case 4:
			pColuna = CALT_coluna4;
			break;
		/* Caso coluna aleatoria 5 */
		case 5:
			pColuna = CALT_coluna5;
			break;
		/* Caso coluna aleatoria 6 */
		case 6:
			pColuna = CALT_coluna6;
			break;
		/* Caso coluna aleatoria 7 */
		case 7:
			pColuna = CALT_coluna7;
			break;
		/* Caso coluna aleatoria 8 */
		case 8:
			pColuna = CALT_coluna8;
			break;
		/* Caso indice coluna aleatoria seja invalido */
		default:
			return COR_CondRetErro;
	}
	/* Verifica se coluna existe */
	if( pColuna == NULL ){

		return COR_CondRetErro;
	}
	/* Posiciona elemento corrente na ultima carta da coluna */
	LIS_IrFinalLista(pColuna);
	return COR_CondRetOK;

}/* Fim função:  CALT  &Ir Final Coluna Aleatoria  */

COR_tpCondRet CALT_AvancarElemCorrColunasAleatorias( int ixIndiceColuna, int numElem)
{
	LIS_tppLista pColuna;

	switch(ixIndiceColuna) {
		/* Caso coluna aleatoria 1 */
		case 1:
			pColuna = CALT_coluna1;
			break;
		/* Caso coluna aleatoria 2 */
		case 2:
			pColuna = CALT_coluna2;
			break;
		/* Caso coluna aleatoria 3 */
		case 3:
			pColuna = CALT_coluna3;
			break;
		/* Caso coluna aleatoria 4 */
		case 4:
			pColuna = CALT_coluna4;
			break;
		/* Caso coluna aleatoria 5 */
		case 5:
			pColuna = CALT_coluna5;
			break;
		/* Caso coluna aleatoria 6 */
		case 6:
			pColuna = CALT_coluna6;
			break;
		/* Caso coluna aleatoria 7 */
		case 7:
			pColuna = CALT_coluna7;
			break;
		/* Caso coluna aleatoria 8 */
		case 8:
			pColuna = CALT_coluna8;
			break;
		/* Caso indice coluna aleatoria seja invalido */
		default:
			return COR_CondRetErro;
	}

	/* Avança elemento corrente até posiçao desejada */
	if( LIS_AvancarElementoCorrente( pColuna , numElem ) != LIS_CondRetOK ) {
		return COR_CondRetErro;	/* Erro ao avançar elemento */
	}

	return COR_CondRetOK;

}/* Fim função:  CALT  &Ir Final Coluna Aleatoria  */

/*****  Código das funções encapsuladas no módulo  *****/

/***************************************************************************
*
*  Função: CALT  &Inserir Carta Aleatoria
*
*  $ED Descrição da função
*		Insere uma carta no final de uma sequencia.
*
*  $EP Parâmetros
*		coluna - coluna onde será inserida a carta
*		ixIndice - indice do elemento do vetor de cartas contendo a carta a ser inserida. 
*
*  $FV tipo retornado
*		COR_CondRetOK, se a carta foi inserida corretamente
*		COR_CondRetErro, se ocorreu algum problema ao inserir a carta.
*
*		Não será dada mais informação quanto ao problema ocorrido.
***********************************************************************/

COR_tpCondRet InserirCartaAleatoria( LIS_tppLista coluna, int ixIndice )
{
	
	/* Insere uma carta no final de uma sequencia */
   int iCondRet = LIS_InserirElementoApos(coluna, vtBaralho[ixIndice] );
	
	if(iCondRet == LIS_CondRetOK){	/* Carta inserida corretamente */
		return COR_CondRetOK;
	}
	return COR_CondRetErro;

} /* Fim função:  CALT  &Inserir Carta Aleatoria */

/***********************************************************************
*
*  $FC Função: CALT  &Inserir Carta Sequencia
*
*  $ED Descrição da função
*		Para inserir uma carta em uma sequencia aleatoria é necessario que esta possua o menor 
*		valor seguinte ao da ultima carta da coluna e uma cor diferente.
*		A função InserirCartaSequencia insere uma carta no final de uma lista de cartas,	
*		testando as condições citadas acima.
*
*  $EP Parâmetros
*		pCarta - ponteiro para a Carta que deve ser inserida.
*		pColuna - ponteiro para a sequencia onde será inserida a Carta.
*
*  $FV tipo retornado
*		Se executou corretamente retorna COR_CondRetOK .
*		Se não é permitido inserir a carta, retorna COR_CondRetAtoProibido.
*		Se ocorreu qualquer outro tipo de erro, retorna COR_CondRetErro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet InserirCartaSequencia( CRT_ptpCarta pCarta, LIS_tppLista pColuna) {

	int icondRet;
	CRT_ptpCarta pCartaAuxiliar;
	if(pColuna==NULL){

		return COR_CondRetErro;

	}
	
	if(pCarta == NULL){ /* Carta invalida */
		return COR_CondRetErro;
	}

	LIS_IrFinalLista( pColuna );		/* Posiciona elemento corrente no final da lista */
	/* Obtêm valor (carta) do ultimo elemento da lista */
	pCartaAuxiliar = (CRT_ptpCarta) LIS_ObterValor( pColuna );

	if(pCartaAuxiliar == NULL){
		icondRet = LIS_InserirElementoApos( pColuna , pCarta );
		if( icondRet == LIS_CondRetOK ) {
			return COR_CondRetOK;
		}
		return COR_CondRetErro;

	}
	/* Testa se a ultima carta da coluna é vermelha */
	if( (strcmp(CRT_ObterNaipeCarta(pCartaAuxiliar), CRT_STRING_COPAS) == 0) ||
		(strcmp(CRT_ObterNaipeCarta(pCartaAuxiliar), CRT_STRING_OUROS) == 0) ) {
			/* Testa se a carta a ser inserida é preta e possui o menor valor seguinte a ultima carta da coluna */
			if( ( (strcmp(CRT_ObterNaipeCarta(pCarta), CRT_STRING_PAUS) == 0) ||
				(strcmp(CRT_ObterNaipeCarta(pCarta), CRT_STRING_ESPADAS) == 0) ) && 
				( CRT_ObterValorCarta(pCarta) == (CRT_ObterValorCarta(pCartaAuxiliar) - 1 ) ) ) {

					icondRet = LIS_InserirElementoApos( pColuna , pCarta );
					if( icondRet == LIS_CondRetOK ) {
						return COR_CondRetOK;
					}
					return COR_CondRetErro;
			}
	}
	else { /* A ultima carta da coluna é preta */

		/* Testa se carta a ser inserida é vermelha e possui o menor valor seguinte a ultima carta da coluna */
		if( ( (strcmp(CRT_ObterNaipeCarta(pCarta), CRT_STRING_OUROS) == 0) ||
			(strcmp(CRT_ObterNaipeCarta(pCarta), CRT_STRING_COPAS) == 0) ) && 
			( CRT_ObterValorCarta(pCarta) == (CRT_ObterValorCarta(pCartaAuxiliar) - 1 ) ) ){

				icondRet = LIS_InserirElementoApos( pColuna ,pCarta );
				if( icondRet == LIS_CondRetOK ) {
					return COR_CondRetOK;
				}
				return COR_CondRetErro;
		}
	}

	return COR_CondRetAtoProibido;	/* Carta não pode ser inserida nessa coluna */

} /* Fim função:  CALT  &Inserir Carta Sequencia */

/***********************************************************************
*
*  $FC Função: CALT  &Retirar Carta Sequencia
*
*  $ED Descrição da função
*		A função RetirarCartaSequencia remove a ultima carta de uma lista de cartas.
*
*  $EP Parâmetros
*		pColuna - ponteiro para a Lista onde será retirada a Carta.
*
*  $FV tipo retornado
*		Ponteiro para a carta removida.
*		NULL, se a lista está vazia. 
*
***********************************************************************/

CRT_ptpCarta RetirarCartaSequencia( LIS_tppLista  pColuna) {

	CRT_ptpCarta pCarta;
	if(pColuna==NULL){

		return NULL;

	}
	LIS_IrFinalLista( pColuna );	/* Posiciona elemento corrente no final da lista */

	/* Guarda valor (carta) do ultimo elemento da lista */
	pCarta = (CRT_ptpCarta) LIS_ObterValor( pColuna );
    
	if( pCarta == NULL) {	/* Lista está vazia, retorna NULL */
		return NULL;
	}
	
	LIS_ExcluirElemento( pColuna ) ;	/* Retira a carta da coluna */

	return pCarta;

} /* Fim função:  CALT  &Retirar Carta Sequencia */

/***********************************************************************
*
*  $FC Função: CALT  &Imprimir Linha Coluna Aleatoria
*
*  $ED Descrição da função
*		Imprime a carta de uma linha de uma coluna.
*
*  $EP Parâmetros
*		pColuna - ponteiro para a coluna.
*
*  $FV tipo retornado
*		1 se ainda tem cartas a se imprimir.
*		0, se a não tem mais cartas. 
*
***********************************************************************/

int ImprimeLinhaColunaAleatoria(LIS_tppLista pColuna){

	CRT_ptpCarta pCarta;
	pCarta = (CRT_ptpCarta) LIS_ObterValor( pColuna );	/* Atualiza o valor de pCarta */
	if(pCarta == NULL){
		printf(" |------|");
		return 0;
	}
	else{
		CRT_ImprimirCarta(pCarta);
		if(LIS_AvancarElementoCorrente( pColuna , 1)== LIS_CondRetFimLista ){

			return 0;
		}
		else{
			return 1;
		}
	}
}/* Fim função:  CALT  &Imprimir Linha Coluna Aleatoria */

/********** Fim do módulo de implementação: CALT Colunas Aleatorias **********/