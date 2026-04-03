/***************************************************************************
*  $MCI Módulo de implementação: TMP Celula Temporaria
*
*  Arquivo gerado:              CELULA_TEMPORARIA.c
*  Letras identificadoras:      TMP
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
***************************************************************************/

#include "CELULA_TEMPORARIA.H"

#define CelulaTemp_OWN
#include "CELULA_TEMPORARIA.H"
#undef CelulaTemp_OWN



/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TMP  &Criar Celulas temporarias
*  ****/

COR_tpCondRet TMP_CriarCelulasTemp()
{
	int iCondRet = COR_CondRetOK, ixIndex = 0;
	TMP_celulaTemporaria = LIS_CriarLista(); /* Cria lista para celulas temp */

	if( LIS_VerificarEstruturaLista(TMP_celulaTemporaria) != LIS_CondRetOK ) {
		return COR_CondRetErro;
	}

	while(ixIndex < QTD_CELULAS_TEMPORARIAS) {
		iCondRet = LIS_InserirElementoApos(TMP_celulaTemporaria, NULL); /* Preenche com NULL
																		cada celula*/
		if( iCondRet != LIS_CondRetOK ) {
			return COR_CondRetErro;		/* Erro ao inserir elemento */
		}
		ixIndex++;
	}

	if( LIS_VerificarEstruturaLista ( TMP_celulaTemporaria) != LIS_CondRetOK ) {
		return COR_CondRetErro;
	}

	return COR_CondRetOK;

} /* Fim função:  TMP  &Criar Celulas temporarias */

/***************************************************************************
*
*  Função: TMP  &Inserir Carta Celula Temporaria
*  ****/

COR_tpCondRet TMP_InserirCartaCelulaTemp( CRT_ptpCarta pCarta, int ixIndice )
{
	CRT_ptpCarta pCartaAuxiliar;

	if(pCarta == NULL){ /* Carta invalida */
		return COR_CondRetErro;
	}

	if( LIS_VerificarEstruturaLista ( TMP_celulaTemporaria) != LIS_CondRetOK ) {
		return COR_CondRetErro;
	} /* Verificação estrutural da lista */

	/* Garante que a lista esteja no início ao começar a interação. */
	LIS_IrInicioLista(TMP_celulaTemporaria);

	/* Deixa o elemento corrente da lista apontando para o elemento correspondente ao índice 
	passado por parâmetro. Os índices vão de 1 a 4, por isso a quantidade de elementos avançados é 
	 índice -1 */
	LIS_AvancarElementoCorrente( TMP_celulaTemporaria , ixIndice -1 );

	pCartaAuxiliar = (CRT_ptpCarta)LIS_ObterValor(TMP_celulaTemporaria);

		/* Verifica se esta posição está vazia */
		if(pCartaAuxiliar == NULL) {

			/* Substitui o elemento vazio da lista por um que contenha a carta */
			if( LIS_InserirElementoAntes(TMP_celulaTemporaria, pCarta) != LIS_CondRetOK) {

				/* Erro ao inserir Elemento nas células temporárias */
				return COR_CondRetErro;
			}

			/* Posiciona ponteiro no elemento nulo */
			if(LIS_AvancarElementoCorrente( TMP_celulaTemporaria , 1 ) != LIS_CondRetOK) {
				return COR_CondRetErro;
			}

			if( LIS_ExcluirElemento(TMP_celulaTemporaria) != LIS_CondRetOK) {
				/* Erro ao excluir Elemento das células temporárias */
				return COR_CondRetErro;
			}

			if( LIS_VerificarEstruturaLista ( TMP_celulaTemporaria) != LIS_CondRetOK ) {
				return COR_CondRetErro;
			} /* Verificação estrutural da lista */
		} else {
			/* A célula correspondente ao índice já possui uma carta */
			return COR_CondRetAtoProibido;
		}

	if( LIS_VerificarEstruturaLista ( TMP_celulaTemporaria) != LIS_CondRetOK ) {
		return COR_CondRetErro;
	} /* Verificação estrutural da lista */

	return COR_CondRetOK;

} /* Fim função:  TMP  &Inserir carta celula temporaria */


/***************************************************************************
*
*  Função: TMP  &Retirar Carta Celula Temporaria
*  ****/

CRT_ptpCarta TMP_RetirarCartaCelulaTemp( int iPosicao )
{
	CRT_ptpCarta pCartaTemporaria;
	int ixIndex = 1;

	if( iPosicao < 1 || iPosicao > 4) {
		/* Posição inválida */
		return NULL; 
	}
	
	if( LIS_VerificarEstruturaLista ( TMP_celulaTemporaria) != LIS_CondRetOK ) {
		return NULL;
	} /* Verificação estrutural da lista */

	/*Garante que a lista esteja no início ao começar a interação.*/
	LIS_IrInicioLista(TMP_celulaTemporaria);
	do {
		if (iPosicao == ixIndex){
			break;
		}
		ixIndex++;

	}while( LIS_AvancarElementoCorrente( TMP_celulaTemporaria , 1)!= LIS_CondRetFimLista );

	/*Guarda o valor da carta a ser excluída*/
	pCartaTemporaria = (CRT_ptpCarta)LIS_ObterValor(TMP_celulaTemporaria);

	/* Adiciona elemento nulo para ocupar o lugar da carta retirada */
	if( LIS_InserirElementoAntes(TMP_celulaTemporaria, NULL) != LIS_CondRetOK) {
		/*Erro ao inserir elemento nulo */
		return NULL;
	}
	/* Avança elemento corrente para que ele aponte para a carta a ser retirada */
	if( LIS_AvancarElementoCorrente( TMP_celulaTemporaria , 1) != LIS_CondRetOK) {
		/*Erro ao avançar elemento */
		return NULL;
	}
	/* Exclui a carta da lista de celulas temporárias */
	if( LIS_ExcluirElemento(TMP_celulaTemporaria) != LIS_CondRetOK) {
		/*Erro ao excluir elemento na lista*/
		return NULL;
	}

	if( LIS_VerificarEstruturaLista ( TMP_celulaTemporaria) != LIS_CondRetOK ) {
		return NULL;
	} /* Verificação estrutural da lista */

	/* Retorna o valor contido na carta já excluída da lista */
	return pCartaTemporaria;

}  /* Fim função:  TMP  &Retirar carta celula temporaria */

/***************************************************************************
*
*  Função: TMP  &Imprimir Celulas Temporarias
*  ****/

COR_tpCondRet TMP_ImprimirCelulasTemporarias()
{
	int ixIndex = 1;

	/* Imprime na tela o título */
	printf("\n CELULAS TEMPORARIAS: \n");

	/* Garante que a lista esteja no início antes da interação */
	LIS_IrInicioLista(TMP_celulaTemporaria);

	/* Percorre as células temporárias */
	while(ixIndex <= QTD_CELULAS_TEMPORARIAS) {

		/* Imprime na tela o conteúdo da célula temporária */
		printf(" Celula %d :", ixIndex);
		CRT_ImprimirCarta((CRT_ptpCarta)LIS_ObterValor(TMP_celulaTemporaria));
		LIS_AvancarElementoCorrente( TMP_celulaTemporaria , 1);
		ixIndex++;
		printf("\n");
	}
	printf("\n");

	if( ixIndex == QTD_CELULAS_TEMPORARIAS + 1) {
		return COR_CondRetOK;
	}
	return COR_CondRetErro;

} /* Fim função:  TMP  &Imprimir Celulas Temporarias */

/***************************************************************************
*
*  Função: TMP  &Destruir Celulas Temporarias
*  ****/

COR_tpCondRet TMP_DestruirCelulasTemporarias() {

	LIS_DestruirLista( TMP_celulaTemporaria );
	TMP_celulaTemporaria = NULL;
	if ( TMP_celulaTemporaria!=NULL ){

		return COR_CondRetErro;
	}
	return COR_CondRetOK;
}/* Fim função:  TMP  &Destruir Celulas Temporarias */


/***************************************************************************
*
*  Função: TMP  &Obter Celula Temporaria
*  ****/

CRT_ptpCarta TMP_ObterCartaCelulaTemporaria( int ixIndiceCelula )
{
	CRT_ptpCarta pCartaAuxiliar;
	int iIndice = 1;
	/* Verifica se o indice corresponte a celula é válido */
	if( ( ixIndiceCelula < 1) || ( ixIndiceCelula > 4 ) ) {
		return NULL;
	}
	/* Verifica se o ponteiro para a celula não é nulo*/
	if( TMP_celulaTemporaria == NULL ){

		return NULL;

	}
	/* Posiciona elemento corrente na primeira celula temporaria */
	LIS_IrInicioLista(TMP_celulaTemporaria);
	
	/* Posiciono o elemento corrente na celula desejada*/
	for(; iIndice < ixIndiceCelula; iIndice++ ) {
		
		LIS_AvancarElementoCorrente(TMP_celulaTemporaria,1);
	}
	/* Obtem a carta */
	pCartaAuxiliar = (CRT_ptpCarta)LIS_ObterValor(TMP_celulaTemporaria);

	return pCartaAuxiliar;

}/* Fim função:  TMP  &Obter Carta Celula Temporaria */

/********** Fim do módulo de implementação: TMP Celula Temporaria **********/