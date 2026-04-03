
#if ! defined( PrivilegioCarta_ )
#define PrivilegioCarta_
/***************************************************************************
*
*  $MCD Módulo de definição: PCRT Privilégio Carta
*
*  Arquivo gerado:              PrivilegioCarta.h
*  Letras identificadoras:      PCRT
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  $ED Descrição do módulo
*
*	  O campo Valor de cada carta pode variar entre 1 e 13.
*	  Os naipes podem ser: copas, espadas, paus e ouros.
*	  Os codigos estão relacionados as cartas que tem letras como símbolos, como o ÁS.
***************************************************************************/

#if defined( PrivilegioCarta_OWN )
   #define PrivilegioCarta_EXT
#else
   #define PrivilegioCarta_EXT extern
#endif

/***********************************************************************
*
*  $FC Função: PCRT  &Criar carta
*
*  $ED Descrição da função
*		A função CriarCarta aloca na memória uma nova estrutura         
*		do tipo carta, inserindo em seus campos os valores		        
*		recebidos como parâmetro	
*
*  $EP Parâmetros
*     Valor  - inteiro que indica o índice da carta na sequência ordenada(baralho)
*	  Naipe  - string que contém o naipe ao qual a carta pertence
*
*  $FV tipo retornado
*		Se executou corretamente retorna o ponteiro para a carta.
*     Este ponteiro será utilizado pelas funções que manipulem esta carta.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

CRT_ptpCarta PCRT_CriarCarta(int valor, char* naipe);

/***********************************************************************
*
*  $FC Função: CRT  &Destruir carta
*
*  $ED Descrição da função
*		A função desaloca os elementos da estrutura e a própria estrutura.	
*
*  $EP Parâmetros
*		carta - ponteiro para a estrutura carta a ser destruída
*
*
***********************************************************************/

void PCRT_DestruirCarta(CRT_ptpCarta carta);

#undef PrivilegioCarta_EXT

/********** Fim do módulo de definição: PCRT PrivilegioCarta ******************/

#else
#endif