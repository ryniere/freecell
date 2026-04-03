/***************************************************************************
*
*  $MCD Módulo de implementação: GER Gerenciador
*
*  Arquivo gerado:              Gerenciador.c
*  Letras identificadoras:      GER
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  
***************************************************************************/

#include <stdlib.h>
#include "Gerenciador.h"
#include "Baralho.h"
#include "CELULA_TEMPORARIA.H"
#include "COLUNA_BASE.H"
#include "COLUNAS_ALEATORIAS.H"
#include "PERSISTENCIA.H"

#define Gerenciador_OWN
#include "Gerenciador.h"
#undef Gerenciador_OWN

char szAleatoria[] = "aleatoria";
char szBase[] = "base";
char szTemporaria[] = "temporaria";

/* Respostas recebidas do usuário */
char RESPOSTA_SIM = 'S';
char RESPOSTA_NAO = 'N';

/***** Protótipos das funções encapuladas no módulo *****/

 /* Função que efetua a troca de posição da carta no jogo */
 GER_tpCondRet GER_MoverCartaGenerica( 
				CRT_ptpCarta (*RetirarCarta)(int), 
				CRT_ptpCarta (*ObterCarta) (int),
				COR_tpCondRet (*InserirCarta)(CRT_ptpCarta, int ), 
				int ixColunaOrigem, 
				int ixColunaDestino);

 GER_tpCondRet TestarFimColuna( int ixIndiceColuna );

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: GER  &Iniciar Jogo
*****/

GER_tpCondRet GER_IniciarJogo(int iRecuperarJogo)
{	
	/* Cria colunas base */
	if( CBSE_CriarColunasBase() != COR_CondRetOK ) {
		return GER_CondRetErro;	/* Erro ao criar colunas base */
	}
	/* Cria celulas temporarias */
	if( TMP_CriarCelulasTemp() != COR_CondRetOK ) {
		return GER_CondRetErro; /* Erro ao criar celulas temporarias */
	}
	/* Cria baralho */
	if( BAR_CriarBaralho() != COR_CondRetOK ) {
		return GER_CondRetErro;	/* Erro ao criar baralho */
	}
	/* Cria Colunas aleatorias */
	if( CALT_CriarColunasAleatorias() != COR_CondRetOK ) {
		return GER_CondRetErro; /* Erro ao criar colunas aleatorias */
	}
	/* Testa se deve carregar jogo */
	if( iRecuperarJogo == 1 ) {
		if( !PERS_VerificarJogoSalvo() ) {
			printf("Nao foi possivel recuperar o ultimo jogo.\n Arquivo de configuracoes nao existe.\n\n"); /* Arquivo de jogo salvo não existe */
			return GER_CondRetErroArquivo;	/* Jogo salvo nao existe */
		}

		if( PERS_CarregarJogo() != GER_CondRetOK ) {
			return GER_CondRetErro; /* Erro ao carregar jogo */
		}
	} else if(iRecuperarJogo == 0) { /* Inicar novo jogo */

		if( BAR_Embaralhar() != COR_CondRetOK ) {
			return GER_CondRetErro; /* Erro ao  embaralhar */
		}

		if( CALT_PreencherColunasAleatorias() != COR_CondRetOK ) {
			return GER_CondRetErro; /* Distribui cartas em colunas aleatorias */
		}

	} else {
		return GER_CondRetErroParametros;
	}

	return GER_CondRetOK;
}/* Fim função: GER  &Iniciar Jogo */

/***********************************************************************
*
*  $FC Função: GER  &EncerrarJogo
*****/

 GER_tpCondRet GER_EncerrarJogo(char cSalvarJogo)
 {
	 /* Testa se deve salvar o jogo */
	if( cSalvarJogo == RESPOSTA_SIM) {
		PERS_SalvarJogo();
	}
	/* Destroi colunas base, aleatorias, celulas temporarias e baralho e referencias nao desalocadas */
	 TMP_DestruirCelulasTemporarias();
	 CBSE_DestruirColunasBase();
	 CALT_DestruirColunasAleatorias();
	 BAR_DestruirBaralho();
	 PERS_DestruirReferenciaJogoSalvo();

	 return GER_CondRetOK;

 } /* Fim função: GER  &Encerrar Jogo */


  /***********************************************************************
*
*  $FC Função: GER  &Mover Carta
*****/

 GER_tpCondRet GER_MoverCarta( 
				GER_tpLocalMovido localOrigem, 
				GER_tpLocalMovido localDestino, 
				int ixColunaOrigem, 
				int ixColunaDestino)
 {

	CRT_ptpCarta (*RetirarCarta)(int);
	CRT_ptpCarta (*ObterCarta) (int);
	COR_tpCondRet (*InserirCarta)(CRT_ptpCarta, int);
	/* Acerta ponteiros para função de retirar e obter carta, de acordo com o local de origem escolhido pelo usuario */
	switch(localOrigem) {
		case GER_LocalColunaAleatoria:
			RetirarCarta = &CALT_RetirarCartaSequenciaColuna;
			ObterCarta = &CALT_ObterCartaColunaAleatoria;
			break;

		case GER_LocalCelulaTemporaria:
			RetirarCarta = &TMP_RetirarCartaCelulaTemp;
			ObterCarta = &TMP_ObterCartaCelulaTemporaria;
			break;

		case GER_LocalColunaBase:
			return GER_CondRetAtoProibido;

		default:
			return GER_CondRetErroParametros;
	}
	/* Acerta ponteiro para a função de inserir carta de acordo com o local destino escolhido pelo usuario */
	switch(localDestino) {
		case GER_LocalColunaAleatoria:
			InserirCarta = &CALT_InserirCartaSequenciaColuna;
			break;

		case GER_LocalCelulaTemporaria:
			InserirCarta = &TMP_InserirCartaCelulaTemp;
			break;

		case GER_LocalColunaBase:
			InserirCarta = &CBSE_InserirCartaColunasBases;
			break;

		default:
			return GER_CondRetErroParametros;
	}

	return GER_MoverCartaGenerica( 
				RetirarCarta,
				ObterCarta,
				InserirCarta, 
				ixColunaOrigem, 
				ixColunaDestino);

 } /* Fim função: GER  &Mover Carta */


  /***********************************************************************
*
*  $FC Função: GER  &Atualizar tela
*****/

 GER_tpCondRet GER_AtualizarTela()
 {	
	 /* Imprime colunas base */
	if( CBSE_ImprimirColunasBases() != COR_CondRetOK ) {
		return GER_CondRetErro; /* Erro ao imprimir colunas base */
	}
	
	printf("\n\n");
	/* Imprime celelas temporarias */
	if( TMP_ImprimirCelulasTemporarias() != COR_CondRetOK ) {
		return GER_CondRetErro; /* Erro ao imprimir celulas temporarias */
	}

	printf("\n\n");
	/* Imprime colunas aleatorias */
	if( CALT_ImprimirColunasAleatorias() != COR_CondRetOK ) {
		return GER_CondRetErro; /* Erro ao imprimir colunas aleatorias */
	}
	
	printf("\n\n");

	return GER_CondRetOK;

 }/* Fim função: GER  &Atualizar tela */

  /***********************************************************************
*
*  $FC Função: GER  &Testar Fim Jogo
*****/

 GER_tpCondRet GER_TestarFimJogo() {

	if( (TestarFimColuna(CBSE_IndiceColunaPaus) != GER_CondRetOK ) ||
		(TestarFimColuna(CBSE_IndiceColunaOuros) != GER_CondRetOK ) ||
		(TestarFimColuna(CBSE_IndiceColunaEspadas) != GER_CondRetOK ) ||
		(TestarFimColuna(CBSE_IndiceColunaCopas) != GER_CondRetOK) ) {
			return GER_CondRetErro; /* Nao foi obtido o fim do jogo */
	}

	return GER_CondRetOK; /* Foi obtido o fim do jogo */

 } /* Fim função: GER  &Testar Fim Jogo */

  /***********************************************************************
*
*  $FC Função: GER  &Exibir Regras
*****/

 void GER_ExibirRegras()
 {
	printf("O objetivo do jogo freecell eh preencher as colunas base de todos os naipes \n");
	printf("com cartas que comecam em A e vao ate o K. Para isso, o jogador dispoe de 4 \n");
	printf("celulas temporarias que auxiliarao a passagem das cartas que comecam nas co-\n");
	printf("lunas aleatorias para as colunas base. Ha uma serie de comandos que promovem\n");
	printf("as jogadas, sao eles:\n\n");
	printf("iniciar - Inicia o jogo, mostrando na tela a disponibilizacao das cartas nas\n");
	printf("				colunas de distribuicao aleatoria.\n\n");
	printf("mover <lugarOrigem> indice1 <lugarDestino> indice2 - Move a carta de um lugar\n");
	printf("				para outro. Lugar de origem e destino sao preenchidos de acordo\n");
	printf("				com sua jogada. Eles podem ser: aleatoria, base e temporaria.\n");
	printf("				indice1 eh o indice da coluna ou celula de onde a carta movida\n");
	printf("				e indice2 eh o indice da coluna ou celula para onde a carta \n");
	printf("				serah movida.\n\n");
	printf("fim - interrompe o jogo corrente e o encerra.\n\n");
 }

   /***********************************************************************
*
*  $FC Função: GER  &Obter Local Movido
*****/

 GER_tpLocalMovido GER_ObterLocalMovido(char szLocalMovido[])
 {
	 
	 if( strcmp( szAleatoria, szLocalMovido) == 0 ) {
		/* Caso local movido = colunas aleatorias */
		return GER_LocalColunaAleatoria;

	 } else if( strcmp(szBase, szLocalMovido) == 0 ) {
		/* Caso local movido = colunas base */
		return GER_LocalColunaBase;

	 } else if( strcmp(szTemporaria, szLocalMovido) == 0 ) {
		/* Caso local movido = celulas temporarias */
		return GER_LocalCelulaTemporaria;

	 }
	 return GER_LocalInexistente; /* Nao existe tal local movido */
 }

 /******** Código das funções encapsuladas no módulo *************/

  /***********************************************************************
*  $FC Função: GER  &Mover Carta
*
*  $ED Descrição da função
*     Efetua a troca de posição de uma carta no jogo de uma coluna(ou célula) 
*	  para outra coluna(ou célula).
*
*  $EP Parâmetros
*		void* (*RetirarCarta)(void*) - ponteiro para a função que retira a última (ou única) carta de uma coluna
*				(célula), ela deve retornar um ponteiro para carta.
*
*		void* (*InserirCarta)(void*) - ponteiro para a função que insere a última (ou única) carta em uma coluna
*				(célula), retornar uma condição de retorno.
*
*		ixColunaOrigem - índice da coluna aleatória da qual se deseja mover a carta
*       (pode variar de 1 a 8).
*
*		ixColunaDestino - índice da coluna aleatória para qual a carta deve ser movida
*       (pode variar de 1 a 8).
*
*  $FV tipo retornado
*		Se executou corretamente retorna GER_CondRetOK .
*		Se não é permitido mover a carta, retorna GER_CondRetAtoProibido.
*		Se ocorreu qualquer outro tipo de erro, retorna GER_CondRetErro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/
 GER_tpCondRet GER_MoverCartaGenerica( 
				CRT_ptpCarta (*RetirarCarta)(int),
				CRT_ptpCarta (*ObterCarta) (int),
				COR_tpCondRet (*InserirCarta)(CRT_ptpCarta, int ), 
				int ixColunaOrigem, 
				int ixColunaDestino)
 {

	CRT_ptpCarta pCartaAuxiliar;
	int iCondRetObtida;

	/* Verifica validade de ponteiros para função */
	if( ((RetirarCarta) == NULL) || ((ObterCarta) == NULL) || 
		((InserirCarta) == NULL)) {
		return GER_CondRetErroParametros;
	}
	/* Obtem carta da coluna origem*/
	pCartaAuxiliar = (*ObterCarta)(ixColunaOrigem);

	/* Se a carta nao existe, retorna Ato Proibido*/
	if( pCartaAuxiliar == NULL ) {
		return GER_CondRetAtoProibido;
	}
	/* Insere carta em local destino */
	iCondRetObtida = InserirCarta( pCartaAuxiliar, ixColunaDestino );

	if( iCondRetObtida == COR_CondRetAtoProibido ){
		return GER_CondRetAtoProibido; /* Nao é permitido inserir carta */
	}

	if( iCondRetObtida == COR_CondRetErro ) {
		return GER_CondRetErro; /* Erro ao inserir carta */
	}
	/* Retira carta da coluna origem */
	(*RetirarCarta)(ixColunaOrigem);

	return GER_CondRetOK;

 } /* Fim função: GER  &Mover Carta Generica */


  /***********************************************************************
*  $FC Função: GER  &Testar Fim Coluna
*
*  $ED Descrição da função
*		Testa se uma coluna base está completa, ou seja, possui as 13 cartas de um naipe.
*
*  $EP Parâmetros
*		ixIndiceColuna - indice indicando a coluna a ser testada
*
*  $FV tipo retornado
*		GER_CondRetOK, se a coluna está completa
*		GER_CondRetErro, se a coluna nao está completa, ou se ocorreu alguma erro.
*
*     Não será dada mais informação quanto ao problema ocorrido.
***********************************************************************/

 GER_tpCondRet TestarFimColuna( int ixIndiceColuna ) {

	 int iValor;
	 char* szNaipe;
	 CRT_ptpCarta ptpCarta;
	 
	/* Posiciona elemento corrente no ultimo elemento da coluna */
	if( CBES_IrFinalColunaBase(ixIndiceColuna) != COR_CondRetOK ) {
		 return GER_CondRetErro;
	}
	/* Obtém naipe e valor da ultima carta da coluna */
	ptpCarta = CBSE_ObterCartaColunaBase(ixIndiceColuna);

	if( ptpCarta == NULL ) {
		return GER_CondRetErro; /* Coluna está vazia */
	}

	szNaipe = (char*)malloc(sizeof(char)*(strlen( CRT_ObterNaipeCarta( ptpCarta ) ) + 1 ) );
	szNaipe = CRT_ObterNaipeCarta( ptpCarta );
	iValor = CRT_ObterValorCarta(ptpCarta);
	
	/* Testa se a ultima carta da coluna é o rei (13) do naipe equivalente */
	switch(ixIndiceColuna) {

		case CBSE_IndiceColunaCopas:
			if((strcmp( szNaipe, CRT_STRING_COPAS ) != 0) || (iValor != 13)) {
				free(szNaipe);
				return GER_CondRetErro;
			}
			break;
		case CBSE_IndiceColunaEspadas:
			if((strcmp( szNaipe, CRT_STRING_ESPADAS ) != 0) || (iValor != 13)) {
				free(szNaipe);
				return GER_CondRetErro;
			}
			break;
		case CBSE_IndiceColunaOuros:
			if((strcmp( szNaipe, CRT_STRING_OUROS ) != 0) || (iValor != 13)) {
				free(szNaipe);
				return GER_CondRetErro;
			}
			break;
		case CBSE_IndiceColunaPaus:
			if((strcmp( szNaipe, CRT_STRING_PAUS ) != 0) || (iValor != 13)) {
				free(szNaipe);
				return GER_CondRetErro;
			}
			break;
		default:
			free(szNaipe);
			return GER_CondRetErro; /* Indice nao corresponde a a nenhuma coluna base */
	}

	free(szNaipe);
	return  GER_CondRetOK;

 } /* Fim função: GER  &Testar Fim Coluna */

	
/********** Fim do módulo de implementação: GER Gerenciador **********/
