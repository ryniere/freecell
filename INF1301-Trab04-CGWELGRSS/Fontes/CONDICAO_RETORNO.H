#if ! defined( Condicao_Retorno_ )
#define Condicao_Retorno

/***************************************************************************
* 
*  $MCD Módulo de definição: COR Condicao Retorno
*
*  Arquivo gerado:              CONDICAO_RETORNO.H
*  Letras identificadoras:      COR
*
*
*  Projeto: INF 1301 / 1628 FREECELL
*  Autores: Carla Galdino Wanderley, Eliana Leite Goldner, Ryniere dos Santos Silva
*
*  $ED Descrição do módulo
*
*	Este módulo contém as condições de retorno genéricas.
*	
*	
***************************************************************************/

#include <stdio.h>
#include "Carta.h"
#include "Lista.h"

#if defined( Condicao_Retorno_OWN )
#define Condicao_Retorno_EXT
#else
#define Condicao_Retorno_EXT extern
#endif

/* Declarações exportadas pelo módulo */


typedef enum {

	COR_CondRetOK ,
	/* Concluiu corretamente */

	COR_CondRetAtoProibido ,
	/* Erro ao preencher célula */

	COR_CondRetErro,
	/* Erro ao preencher célula */

	COR_CondRetErroParametros,
	/* Parametros de entrada da função tem valores inesperados */

}COR_tpCondRet ;

#undef Condicao_Retorno_EXT

/********** Fim do módulo de definição: COR Condicao Retorno ******************/

#else
#endif