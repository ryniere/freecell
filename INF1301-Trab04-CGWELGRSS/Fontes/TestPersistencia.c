/***************************************************************************
*  $MCI Módulo de implementação: TPERS Teste Persistencia
*
*  Arquivo gerado:              TestPersistencia.c
*  Letras identificadoras:      TPERS
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
#include "PERSISTENCIA.H"
#include "COLUNA_BASE.H"
#include "CELULA_TEMPORARIA.H"
#include    "Baralho.h"
#include    "PrivilegioCarta.h"


static const char SALVAR_JOGO_CMD                             [ ] = "=salvarjogo";
static const char CARREGAR_JOGO_CMD                           [ ] = "=carregarjogo";
static const char VERIFICAR_JOGO_SALVO_CMD                    [ ] = "=verificarjogosalvo";
static const char ALTERAR_NOME_ARQUIVO_CMD                    [ ] = "=alterarnomearquivo";

typedef void (*tipoTeste) ();

/***** Protótipos das funções encapsuladas no módulo *****/

static void TestarSalvarColunasBasesVazias();

static void TestarSalvarColunasBasesPreenchidas();

static void TestarSalvarColunasAleatoriasVazias();

static void TestarSalvarColunasAleatoriasPreenchidas();

static void TestarSalvarCelulasTemporariasVazias();

static void TestarSalvarCelulasTemporariasPreenchidas();

static void TestarSalvarTudoVazio();

static void TestarSalvarTudoPreenchido();

static void CriarEstruturaJogo();

static void DestruirEstruturaJogo();

static void PreencherCelulasTemporarias();

static void PreencherColunasAleatorias();

static void PreencherColunasBase();

static void ImprimirJogo();


tipoTeste   vtFuncoes[] = {TestarSalvarColunasBasesVazias, TestarSalvarColunasBasesPreenchidas,
							TestarSalvarColunasAleatoriasVazias, TestarSalvarColunasAleatoriasPreenchidas,
							TestarSalvarCelulasTemporariasVazias, TestarSalvarCelulasTemporariasPreenchidas,
                            TestarSalvarTudoVazio, TestarSalvarTudoPreenchido } ;



#define DIM_VALOR     100

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPERS &Testar Persistencia
*
*  $ED Descrição da função
*      Podem ser criadas até 8 tipos de situação de jogo
*     
*
*     Comandos disponíveis:
*
*     =salvarjogo                              tipo CondRetEsp         
*     =carregarjogo                            CondRetEsp               
*     =verificarjogosalvo                      CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

	int numLidos   = -1 ,
		CondRetEsp = -1,
		CondRet  = -1,
	    tipo =-1;

	char   StringDado[  DIM_VALOR ] ;

	tipoTeste tpFuncao;

 
     
	 if ( strcmp( ComandoTeste , SALVAR_JOGO_CMD ) == 0 )
	{
		
       
		numLidos = LER_LerParametros( "ii" ,&tipo,
			&CondRetEsp ) ;

         
		if ( ( numLidos != 2 ) || ( tipo < 0 )|| 
			( tipo > 7) )
		{
			return TST_CondRetParm ;
		} /* if */


		if( CondRetEsp!=2 ){

			CriarEstruturaJogo();
			tpFuncao = vtFuncoes[tipo];
			tpFuncao();
			ImprimirJogo();

		}
        
        

		

		CondRet = PERS_SalvarJogo();

		if( CondRetEsp!=2 ){

			DestruirEstruturaJogo();

		}

		
		return TST_CompararInt( CondRetEsp , CondRet ,
			"Condicao de retorno errada ao salvar jogo" ) ;

	} /* fim ativa: Testar Salvar Jogo */

	 else if ( strcmp( ComandoTeste , CARREGAR_JOGO_CMD ) == 0 )
	 {


		 numLidos = LER_LerParametros( "i" ,
			 &CondRetEsp ) ;


		 if ( ( numLidos != 1 ) )
		 {
			 return TST_CondRetParm ;
		 } /* if */

		 if( CondRetEsp!=2 ){

			 CriarEstruturaJogo();

		 }
		 

		 CondRet = PERS_CarregarJogo();

		 if( CondRetEsp!=2 ){

			 ImprimirJogo();

		 }

		 


		 return TST_CompararInt( CondRetEsp , CondRet ,
			 "Condicao de retorno errada ao carregar jogo" ) ;

	 } /* fim ativa: Testar Carregar Jogo */

	 else if ( strcmp( ComandoTeste , VERIFICAR_JOGO_SALVO_CMD ) == 0 )
	 {


		 numLidos = LER_LerParametros( "i" ,
			 &CondRetEsp ) ;


		 if ( ( numLidos != 1 ) )
		 {
			 return TST_CondRetParm ;
		 } /* if */


		 
		 if( PERS_VerificarJogoSalvo()!= COR_CondRetOK){

			 return TST_CondRetErro;
		 }

		return TST_CondRetOK;

	 } /* fim ativa: Testar Verificar Jogo Salvo */

	 else if ( strcmp( ComandoTeste , ALTERAR_NOME_ARQUIVO_CMD ) == 0 )
	 {


		 numLidos = LER_LerParametros( "si" , StringDado,
			 &CondRetEsp ) ;


		 if ( ( numLidos != 2 ) )
		 {
			 return TST_CondRetParm ;
		 } /* if */

		
		 CondRet = PERS_AlterarNomeArquivo( StringDado );


		 return TST_CompararInt( CondRetEsp , CondRet ,
			 "Condicao de retorno errada ao carregar jogo" ) ;

	 } /* fim ativa: Testar Alterar Nome Arquivo */

	return TST_CondRetNaoConhec ;

} /* Fim função: TPERS &Testar Persistencia */

/*****  Código das funções encapsuladas no módulo  *****/

void TestarSalvarColunasBasesVazias(){

	PreencherCelulasTemporarias();
	PreencherColunasAleatorias();


}

void TestarSalvarColunasBasesPreenchidas(){

	PreencherColunasBase();

}

void TestarSalvarColunasAleatoriasVazias(){

	PreencherColunasBase();
	PreencherCelulasTemporarias();
	
}

void TestarSalvarColunasAleatoriasPreenchidas(){

	PreencherColunasAleatorias();
	
}

void TestarSalvarCelulasTemporariasVazias(){

	PreencherColunasBase();
	PreencherColunasAleatorias();
	
}

void TestarSalvarCelulasTemporariasPreenchidas(){

	PreencherCelulasTemporarias();
	
}

void TestarSalvarTudoVazio(){

	
}

void TestarSalvarTudoPreenchido(){

	PreencherColunasBase();
	PreencherCelulasTemporarias();
	PreencherColunasAleatorias();

}

void CriarEstruturaJogo(){

	BAR_CriarBaralho();
	TMP_CriarCelulasTemp();
	CBSE_CriarColunasBase();
	CALT_CriarColunasAleatorias();
	
}

void DestruirEstruturaJogo(){

	TMP_DestruirCelulasTemporarias();
	CBSE_DestruirColunasBase();
	CALT_DestruirColunasAleatorias();
	BAR_DestruirBaralho();

}

void PreencherColunasBase(){

	CRT_ptpCarta ptpCarta;

	ptpCarta = PCRT_CriarCarta(1,"copas");
	CBSE_InserirCartaColunasBases(ptpCarta,1);
	ptpCarta = PCRT_CriarCarta(2,"copas");
	CBSE_InserirCartaColunasBases(ptpCarta,1);

	ptpCarta = PCRT_CriarCarta(1,"espadas");
	CBSE_InserirCartaColunasBases(ptpCarta,2);
	ptpCarta = PCRT_CriarCarta(2,"espadas");
	CBSE_InserirCartaColunasBases(ptpCarta,2);

	ptpCarta = PCRT_CriarCarta(1,"ouros");
	CBSE_InserirCartaColunasBases(ptpCarta,3);
	ptpCarta = PCRT_CriarCarta(2,"ouros");
	CBSE_InserirCartaColunasBases(ptpCarta,3);

	ptpCarta = PCRT_CriarCarta(1,"paus");
	CBSE_InserirCartaColunasBases(ptpCarta,4);
	ptpCarta = PCRT_CriarCarta(2,"paus");
	CBSE_InserirCartaColunasBases(ptpCarta,4);

}

void PreencherCelulasTemporarias(){

	CRT_ptpCarta ptpCarta;

	ptpCarta = PCRT_CriarCarta(3,"copas");
	TMP_InserirCartaCelulaTemp(ptpCarta,1);

	ptpCarta = PCRT_CriarCarta(11,"espadas");
	TMP_InserirCartaCelulaTemp(ptpCarta,2);
	

	ptpCarta = PCRT_CriarCarta(7,"ouros");
	TMP_InserirCartaCelulaTemp(ptpCarta,3);
	

	ptpCarta = PCRT_CriarCarta(4,"paus");
	TMP_InserirCartaCelulaTemp(ptpCarta,4);

}

void PreencherColunasAleatorias(){

	BAR_Embaralhar();
	CALT_PreencherColunasAleatorias();
}

void ImprimirJogo(){

	CBSE_ImprimirColunasBases();
	TMP_ImprimirCelulasTemporarias();
	CALT_ImprimirColunasAleatorias();

}


/********** Fim do módulo de implementação: TCALT Colunas Aleatorias **********/