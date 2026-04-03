/***************************************************************************
*  $MCI M�dulo de implementa��o: PERS PERSISTENCIA
*
*  pArq gerado:              PERSISTENCIA.c
*  Letras identificadoras:      PERS		
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
***************************************************************************/


#include "COLUNA_BASE.h"
#include "COLUNAS_ALEATORIAS.h"
#include "CELULA_TEMPORARIA.h"
#include "Baralho.h"
#include <stdio.h>

#define Persistencia_OWN
#include "PERSISTENCIA.h"
#undef Persistencia_OWN

char* szJogoSalvo="JogoSalvo.txt";

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

static COR_tpCondRet SalvarColunasAleatorias( FILE * pArq );

static COR_tpCondRet SalvarColunasBases(FILE * pArq);

static COR_tpCondRet SalvarCelulasTemporarias(FILE * pArq);

static COR_tpCondRet SalvarColunaBase(FILE * pArq, CBSE_IndiceColunasBase ixIndice );

static COR_tpCondRet CarregarColunasAleatorias(FILE * pArq );

static COR_tpCondRet CarregarColunasBases( FILE * pArq );

static COR_tpCondRet CarregarCelulaTemporaria( FILE * pArq );

static COR_tpCondRet CarregarCartas( FILE * pArq, COR_tpCondRet ( *inserirCarta )( CRT_ptpCarta, int ), int iQuantidade );

static int SalvarCarta(FILE * pArq, CRT_ptpCarta ptpCarta);


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: PERS  &Salvar Jogo
*  ****/

COR_tpCondRet PERS_SalvarJogo(){

	FILE* pArq;
	/* Abre arquivo para salvar o jogo */
	pArq = fopen( szJogoSalvo, "wt");
	if( pArq == NULL ){

		return COR_CondRetErro; /* Erro ao abrir arquivo */
	}
   
	if( SalvarCelulasTemporarias(pArq) != COR_CondRetOK ) {
		
		return COR_CondRetErro; /* Erro ao salvar celulas temporarias */
	}
	if( SalvarColunasBases(pArq) != COR_CondRetOK ) {
		return COR_CondRetErro; /* Erro ao salvar colunas base */
	}
	if(	SalvarColunasAleatorias(pArq) != COR_CondRetOK ) {
		return COR_CondRetErro; /* Erro ao salvar colunas aleatorias */
	}	
	fclose(pArq); /* Fecha arquivo */
	
    return COR_CondRetOK;

} /* Fim fun��o:  PERS  &Salvar Jogo */

/***************************************************************************
*
*  Fun��o: PERS &Carregar Jogo
*  ****/

COR_tpCondRet PERS_CarregarJogo(){

	FILE* pArq;
	/* Abre arquivo com jogo salvo */
	pArq = fopen( szJogoSalvo,"rt" );
	if( pArq == NULL ){

		return COR_CondRetErro; /* Nao foi possivel abrir arquivo */
	}
	/* Carregar colunas base, aleatoria e celula temporaria */
	if( ( CarregarCelulaTemporaria( pArq ) != COR_CondRetOK ) ||
		( CarregarColunasBases( pArq ) != COR_CondRetOK ) ||
		( CarregarColunasAleatorias( pArq ) != COR_CondRetOK ) )
	{	
			fclose( pArq ); /* Fecha arquivo */
			return COR_CondRetErro; /* Erro ao carregar colunas base, aleatoria ou celula temporaria */
	}
	
	fclose( pArq ); /* Fecha arquivo */

	return COR_CondRetOK;

} /* Fim fun��o:  PERS  &Salvar Jogo */

/***************************************************************************
*
*  Fun��o: PERS &Alterar nome do Arquivo
*  ****/

COR_tpCondRet PERS_AlterarNomeArquivo(char * szNomeArquivo){

	if( szNomeArquivo == NULL ){

		return COR_CondRetErro;	/* Nome invalido para arquivo */
	}

	szJogoSalvo = (char*)malloc(sizeof(char)*(strlen(szNomeArquivo)+1));

	strcpy(szJogoSalvo,szNomeArquivo); /* Altera nome do arquivo */

	return COR_CondRetOK;

}/* Fim fun��o:  PERS  &Alterar Nome do Arquivo */

/***************************************************************************
*
*  Fun��o: PERS &Verificar Jogo Salvo
*  ****/

int PERS_VerificarJogoSalvo(){
	/* Abre arquivo com jogo salvo */
	FILE* pArq = fopen( szJogoSalvo, "rt" );
	if ( pArq == NULL ){
		return 0; /* Jogo Salvo nao existe */
	}

	fclose(pArq); /* Fecha arquivo */
	return 1; /* Jogo Salvo existe */

}/* Fim fun��o:  PERS  &Verificar Jogo Salvo */

/***************************************************************************
*
*  Fun��o: PERS &Destruir Referencia Jogo Salvo
*  ****/

void PERS_DestruirReferenciaJogoSalvo(){
	free(szJogoSalvo);

} /* Fim fun��o:  PERS  &Destruir Referencia Jogo Salvo */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: PERS  &Salvar Colunas Aleat�rias
*
*  $ED Descri��o da fun��o
*		Salva as cartas de todas as colunas aleat�rias em um arquivo
*
*  $EP Par�metros
*		
*		pArq - ponteiro para o arquivo onde ser�o gravadas as cartas.
*
*  $FV tipo retornado
*		COR_CondRetOK se as cartas foram salvas corretamente
*		COR_CondRetErro se houve algum problema ao salvar cartas
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet SalvarColunasAleatorias( FILE * pArq ){
	
	int ixIndice;
	CRT_ptpCarta ptpCarta;
	int fim = 0;


	if( pArq == NULL) {
		return COR_CondRetErro; /* Arquivo invalido */
	}
	/* Posiciona elemento corrente no final de todas colunas aleatorias */
	for( ixIndice=1; ixIndice<=8; ixIndice++ ){
		
		CALT_IrFinalColunaAleatoria(ixIndice);

	}	

	ixIndice=1;
	do{
		/* Obtem carta coluna aleatoria */
		ptpCarta =  CALT_ObterCartaColunaAleatoria( ixIndice );
		fim=SalvarCarta(pArq, ptpCarta); /* Salva a carta */
		if( (CALT_AvancarElemCorrColunasAleatorias(ixIndice, -1) != COR_CondRetOK)) { /* Recua uma carta na coluna */
			if(ptpCarta!=NULL){
				SalvarCarta(pArq, NULL); 
			}
			fim = 1;

		}
		if(fim==1){
			/* Terminou de salvar uma coluna, come�a a salvar a proxima */
			ixIndice++;
		}


	}while(ixIndice <= 8);
	return COR_CondRetOK;

} /* Fim fun��o:  PERS  &Salvar Colunas Aleatorias */

/***********************************************************************
*
*  $FC Fun��o: PERS  &Salvar Colunas Bases
*
*  $ED Descri��o da fun��o
*		Salva as cartas de todas as colunas bases em um arquivo
*
*  $EP Par�metros
*		
*		pArq - ponteiro para o arquivo onde ser�o gravadas as cartas.
*
*  $FV tipo retornado
*		COR_CondRetOK se as cartas foram salvas corretamente
*		COR_CondRetErro se houve algum problema ao salvar cartas
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet SalvarColunasBases(FILE * pArq){

	if( pArq == NULL ) {
		return COR_CondRetErro;	/* Arquivo invalido */
	}
	if( (SalvarColunaBase(pArq, CBSE_IndiceColunaCopas ) != COR_CondRetOK ) ||
	    (SalvarColunaBase(pArq, CBSE_IndiceColunaEspadas ) != COR_CondRetOK ) ||
	    (SalvarColunaBase(pArq, CBSE_IndiceColunaOuros) != COR_CondRetOK) ||
		(SalvarColunaBase(pArq, CBSE_IndiceColunaPaus ) != COR_CondRetOK) ) {

			return COR_CondRetErro;	/* Erro ao salvar uma coluna base */
	}

	return COR_CondRetOK;

} /* Fim fun��o:  PERS  &Salvar Colunas Bases */

/***********************************************************************
*
*  $FC Fun��o: PERS  &Salvar Celulas Temporarias
*
*  $ED Descri��o da fun��o
*		Salva as cartas de todas as celulas temporarias em um arquivo
*
*  $EP Par�metros
*		
*		pArq - ponteiro para o arquivo onde ser�o gravadas as cartas.
*
*  $FV tipo retornado
*		COR_CondRetOK se as cartas foram salvas corretamente
*		COR_CondRetErro se houve algum problema ao salvar cartas
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet SalvarCelulasTemporarias(FILE * pArq){

	int ixIndex = 1;
	CRT_ptpCarta ptpCarta;

	if( pArq == NULL ){
		return COR_CondRetErro; /* Arquivo invalido */
	}
    
	while( ixIndex <=4 ) {
		/* Obtem carta a ser salva */
		ptpCarta = TMP_ObterCartaCelulaTemporaria( ixIndex );
		SalvarCarta( pArq, ptpCarta ); /* Salva a carta */
		if(ptpCarta!=NULL){

			SalvarCarta( pArq, NULL );

		}
		ixIndex++;
	}

	return COR_CondRetOK;

} /* Fim fun��o:  PERS  &Salvar Celulas Temporarias */

/***********************************************************************
*
*  $FC Fun��o: PERS  &Salvar Coluna Base
*
*  $ED Descri��o da fun��o
*		Salva as cartas de uma coluna base em um arquivo
*
*  $EP Par�metros
*		
*		pArq - ponteiro para o arquivo onde ser�o gravadas as cartas.
*		pListaColunaBase - ponteiro para a coluna base a ser gravada.
*
*  $FV tipo retornado
*		COR_CondRetOK se as cartas foram salvas corretamente
*		COR_CondRetErro se houve algum problema ao salvar cartas
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet SalvarColunaBase(FILE * pArq, CBSE_IndiceColunasBase ixIndiceColuna ){
	
	CRT_ptpCarta ptpCarta;
	int fim = 0;
    
	if( pArq == NULL ){
		return COR_CondRetErro; /* Arquivo invalido */
	}
	/* Posiciona elemento corrente na primeira carta da coluna */
	if(CBES_IrInicioColunaBase( ixIndiceColuna ) != COR_CondRetOK) {
		return COR_CondRetErro;
	}
	 
	do{
		ptpCarta =  CBSE_ObterCartaColunaBase( ixIndiceColuna ); /* Obtem carta a ser salva */
		fim=SalvarCarta(pArq, ptpCarta); /* Salva a carta */
		if( (CBSE_AvancarElemCorrColunaBase(ixIndiceColuna, 1) != COR_CondRetOK)) {
			if(ptpCarta!=NULL){
				SalvarCarta(pArq, NULL);
			}
			fim = 1;
	
		}		
		
	}while(fim != 1);

	return COR_CondRetOK;
	
}/* Fim fun��o:  PERS  &Salvar Coluna Base */

/***********************************************************************
*
*  $FC Fun��o: PERS  &Salvar Carta
*
*  $ED Descri��o da fun��o
*		Salva uma carta em um arquivo
*
*  $EP Par�metros
*		
*		pArq - ponteiro para o arquivo onde ser� gravada a carta.
*		ptpCarta - ponteiro para a carta a ser gravada.
*
*  $FV tipo retornado
*		COR_CondRetCartaNula, se a carta a ser gravada for nula
*		COR_CondRetOK, se a carta foi gravada corretamente
*		COR_CondRetErro, se ocorreu algum problema
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

int SalvarCarta( FILE * pArq, CRT_ptpCarta ptpCarta ){

	if(pArq == NULL) {
		return COR_CondRetErro; /* Arquivo invalido */
	}

	if ( ptpCarta == NULL ){ /* Marca final de coluna/celula */

		fprintf( pArq,"FIM\n" );
		return 1;
	}
	else{

		fprintf( pArq, "%s %d\n",CRT_ObterNaipeCarta( ptpCarta ), 
			CRT_ObterValorCarta( ptpCarta ) ); /* Grava em arquivo a carta */
		return 0;
	}

} /* Fim fun��o:  PERS  &Salvar Carta */


/***********************************************************************
*
*  $FC Fun��o: PERS  &Carregar Colunas Aleatorias
*
*  $ED Descri��o da fun��o
*		L� um arquivo com um jogo salvo e carrega as cartas de todas as colunas aleatorias
*
*  $EP Par�metros
*		
*		pArq - ponteiro para o arquivo onde ser�o lidas as cartas.
*
*  $FV tipo retornado
*		COR_CondRetOK se as cartas foram carregadas corretamente
*		COR_CondRetErro se houve algum problema ao carregas cartas
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet CarregarColunasAleatorias( FILE * pArq ){

	if(pArq == NULL) {
		return COR_CondRetErro; /* Arquivo invalido */
	}
	if( CarregarCartas( pArq, &CALT_InserirCartaColuna, 8 ) != COR_CondRetOK  ){

			return COR_CondRetErro; /* Erro ao carregar cartas das colunas aleatorias */
	}

	return COR_CondRetOK;

} /* Fim fun��o:  PERS  &Carregar Colunas Aleatorias */

/***********************************************************************
*
*  $FC Fun��o: PERS  &Carregar Colunas Bases
*
*  $ED Descri��o da fun��o
*		L� um arquivo com um jogo salvo e carrega as cartas de todas as colunas base
*
*  $EP Par�metros
*		
*		pArq - ponteiro para o arquivo onde ser�o lidas as cartas.
*
*  $FV tipo retornado
*		COR_CondRetOK se as cartas foram carregadas corretamente
*		COR_CondRetErro se houve algum problema ao carregas cartas
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet CarregarColunasBases( FILE * pArq ){

	if(pArq == NULL) {
		return COR_CondRetErro; /* Arquivo invalido */
	}

	if( CarregarCartas( pArq, &CBSE_InserirCartaColunasBases,4 ) != COR_CondRetOK  ){

			return COR_CondRetErro; /* Erro ao carregar cartas das colunas base */
	}

	return COR_CondRetOK;

} /* Fim fun��o:  PERS  &Carregar Colunas Bases  */

/***********************************************************************
*
*  $FC Fun��o: PERS  &Carregar Celulas Temporarias
*
*  $ED Descri��o da fun��o
*		L� um arquivo com um jogo salvo e carrega as cartas das celulas temporarias
*
*  $EP Par�metros
*		
*		pArq - ponteiro para o arquivo onde ser�o lidas as cartas.
*
*  $FV tipo retornado
*		COR_CondRetOK se as cartas foram carregadas corretamente
*		COR_CondRetErro se houve algum problema ao carregas cartas
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet CarregarCelulaTemporaria( FILE * pArq ){

	if(pArq == NULL) {
		return COR_CondRetErro; /* Arquivo invalido */
	}

	if( CarregarCartas( pArq, &TMP_InserirCartaCelulaTemp,4 ) != COR_CondRetOK ){

			return COR_CondRetErro; /* Erro ao carregar cartas das celulas temporarias */
	}

	return COR_CondRetOK;

} /* Fim fun��o:  PERS  &Carregar Celulas Temporarias  */

/***********************************************************************
*
*  $FC Fun��o: PERS  &Carregar Cartas
*
*  $ED Descri��o da fun��o
*		L� um arquivo com um jogo salvo e carrega as cartas das celulas temporarias
*
*  $EP Par�metros
*		
*		pArq - ponteiro para o arquivo onde ser�o lidas as cartas.
*		pLista - lista onde ser�o carregadas as cartas
*		(*inserirCarta) - ponteiro para a fun��o que insere uma carta na lista
*		iQuantidade - quantidade de cartas a serem carregadas
*
*  $FV tipo retornado
*		COR_CondRetOK se as cartas foram carregadas corretamente
*		COR_CondRetErro se houve algum problema ao carregas cartas
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

COR_tpCondRet CarregarCartas( FILE * pArq, COR_tpCondRet ( *inserirCarta )
							  ( CRT_ptpCarta, int ),int iQuantidade ){
 
	CRT_ptpCarta ptpCarta;
	char szNaipe[8];
	int iValor;
	char linha[10];
	int ixIndice=1;

	if ( (pArq == NULL) ){	

		return COR_CondRetErro; /* Arquivo invalido */
	}

	do{
		fgets( linha,121, pArq );//Pega uma linha do arquivo
		sscanf( linha, "%s %d", &szNaipe, &iValor );//inicializa par�metros com os valores de uma linha
		if( strcmp( szNaipe, "FIM" ) != 0 ){// compara se o valor � "FIM"

			ptpCarta = BAR_BuscarCartaBaralhoOrdenado( iValor, szNaipe );
			if ( ptpCarta == NULL ){

				return COR_CondRetErro; /* Carta n�o existe */
			}
			
			if( inserirCarta( ptpCarta, ixIndice ) != COR_CondRetOK ){
				
				return COR_CondRetErro; /* Erro ao inserir a carta */
			}
		}
		else {
			ixIndice++; //Se a linha lida � FIM, pula para a proxima coluna
		}
		
	}while( ixIndice <= iQuantidade );//Executa at� no numero de colunas existente for atingido

	return COR_CondRetOK;

}  /* Fim fun��o:  PERS  &Carregar Cartas  */


/********** Fim do m�dulo de implementa��o: PERS Persistencia **********/