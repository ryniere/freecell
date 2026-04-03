#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Gerenciador.h"

#define TRUE 1
#define FALSE 0

/* Respostas recebidas do usuário */
extern char RESPOSTA_SIM;
extern char RESPOSTA_NAO;


char szMover[] = "mover";
char szFim[] = "fim";
char szAjuda[] = "ajuda";

int menuInicial(){

	int iopcao;
	
	printf( "---------MENU---------\n" );
	printf( "1 - Iniciar jogo Novo\n" );
	printf( "2 - Iniciar jogo salvo\n" );
	printf( "3 - Ajuda\n" );
	printf( "4 - Sair\n" );
	printf( "----------------------\n" );
	do {
		printf( "Escolha uma opcao\n" );
		scanf( "%d", &iopcao );
		if( (iopcao != 1) && (iopcao != 2) && (iopcao != 3) && (iopcao != 4) ) {
			printf("Opcao invalida!");
		}
	}while( (iopcao != 1) && (iopcao != 2) && (iopcao != 3) && (iopcao != 4) ); /* Pede opção para usuario ate que 
																				seja valida */

	return iopcao;

}

void IniciarInterfaceUsuario()
{
	int iOpcao, iCondRet;

	printf( "Bem vindo ao mundo do FREECELL!!\n" );
	printf( "Um jogo que testa sua capacidade de raciocinio de forma divertida!\n" );
	printf( "Divirta-se!\n" );
	iOpcao = menuInicial(); /* Obtem uma opção de ação do usuario */

	do{
		if( iOpcao == 3 ) { /* Exibe regras e pede outra opção de ação para usuário */
			GER_ExibirRegras();
			iOpcao = menuInicial();
		}

		if(iOpcao == 2) { /* Tenta iniciar jogo salvo */
			iCondRet = GER_IniciarJogo(TRUE);
			if( iCondRet == GER_CondRetOK){
				break;
			} else { /* Caso jogo salvo nao exista, pede outra opçao de ação ao usuario */
				iOpcao = menuInicial();
			}

		}
	}while((iOpcao == 2) || (iOpcao == 3));

	
	switch(iOpcao) {
		case 1:
			GER_IniciarJogo(FALSE); /* Inicia um novo jogo */
			break;
		case 2:
			break; /* Jogo já iniviado corretamente */
		case 4:
			exit(0); /* Opção sair */
			break;
		default: /* Opção obtida é invalida */
			printf("Ocorreu um erro na execução do programa. Ele será fechado.\n");
			exit(0);
	}
	
	printf("O jogo foi iniciado.\n Agora basta mover as cartas!");
	printf("Para mais informacoes sobre o jogo, digite ajuda\n para encerra-lo, digite fim\n Boa sorte!\n");

	GER_AtualizarTela(); /* Imprime jogo */

}

int main(void)
{
	int iIndiceColunaOrigem, iIndiceColunaDestino;
	char szComando[100];
	char szTipoColunaOrigem[100];
	char szTipoColunaDestino[100];
	char cOpcao;
	char cSalvarJogo;
	GER_tpCondRet iCondRet;

	IniciarInterfaceUsuario();
	
	do{
		printf("Entre com um comando:"); /* Obtem comando do usuario */
		scanf("%s",szComando);

		if(strcmp(szComando, szAjuda) == 0) {

			GER_ExibirRegras(); /* Se o comando é ajuda, exibe regras */

		} else if(strcmp(szComando, szMover) == 0) { /* se o comando é mover, obtem outras instruções */
			
			scanf("%s", szTipoColunaOrigem);
			scanf("%d", &iIndiceColunaOrigem);
			scanf("%s", szTipoColunaDestino);
			scanf("%d", &iIndiceColunaDestino);

			 iCondRet = GER_MoverCarta( 
				GER_ObterLocalMovido(szTipoColunaOrigem), 
				GER_ObterLocalMovido(szTipoColunaDestino), 
				iIndiceColunaOrigem, 
				iIndiceColunaDestino); /* move carta */

			 if(iCondRet ==  GER_CondRetAtoProibido) { /* Regras nao permitem movimento ordenado pelo usuario */
				printf("As regras nao permitem que esse movimento seja realizado.\n Tente Novamente!\n");
			 }

			 if(iCondRet == GER_CondRetErroParametros) { /* Paramentros passados pelo usuario sao invalidos */
				printf("Os locais de origem e/ou destino nao sao validos.\n");
			 }

			 if(iCondRet == GER_CondRetOK) { /* Carta foi movida corretamente */
				GER_AtualizarTela(); /* Imprime colunas e celulas */
				if( GER_TestarFimJogo() == GER_CondRetOK ) { /* Verifica se o final do jogo foi obtido */
					printf("Parabens!! Voce ganhou!!");
					printf("Deseja jogar novamente? (Digite 'S' para sim e 'N' para nao)\n");
					scanf(" %c", &cOpcao);
					if(cOpcao == RESPOSTA_NAO) { /* Caso usuario nao deseje jogar novamente */
						return 0;
					} else if( cOpcao == RESPOSTA_SIM ) { /* Caso usuario deseje jogar novamente, inicia nova interface */
						GER_EncerrarJogo( RESPOSTA_NAO );
						IniciarInterfaceUsuario();						
					} else {
						printf("Opcao invalida. O jogo sera encerrado.\n"); /* Resposta obtida invalida*/
						GER_EncerrarJogo(RESPOSTA_NAO);
						return 0;
					}
				}
			 }

		} else if(strcmp(szComando, szFim) != 0) { /* Caso comando nao seja valido */
			printf("Comando invalido.\n");
		}
	} while( strcmp(szComando, szFim) != 0); /* Obtem comando até que seja ordenado fim do jogo */

	do { /* Verifica se usuario deseja salvar o jogo */
		printf("Deseja salvar o jogo? (Digite S para sim e N para nao.)\n");
		scanf(" %c", &cSalvarJogo);

	} while( (cSalvarJogo != RESPOSTA_SIM) && (cSalvarJogo != RESPOSTA_NAO) ); /* Pergunta até ser obtida uma resposta valida */

	GER_EncerrarJogo(cSalvarJogo); /* Encerra jogo */
	return 0;
}