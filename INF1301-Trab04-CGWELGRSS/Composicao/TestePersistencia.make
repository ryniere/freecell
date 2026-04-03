##################################################
###
### Diretivas de MAKE para o construto: TestePersistencia
### Gerado a partir de: TestePersistencia.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TestePersistencia


### Nomes de paths

Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diretórios para geração

Fh                   = ..\Fontes
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes
Fc                   = ..\Fontes

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\testpersistencia.obj   $(Fobj)\persistencia.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\testpersistencia.obj :  {$(Pc)}\testpersistencia.c \
    {$(Ph)}baralho.h            {$(Ph)}carta.h              {$(Ph)}celula_temporaria.h  \
    {$(Ph)}coluna_base.h        {$(Ph)}colunas_aleatorias.h {$(Ph)}condicao_retorno.h   \
    {$(Ph)}generico.h           {$(Ph)}lerparm.h            {$(Ph)}lista.h              \
    {$(Ph)}persistencia.h       {$(Ph)}privilegiocarta.h    {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\persistencia.obj :  {$(Pc)}\persistencia.c \
    {$(Ph)}baralho.h            {$(Ph)}carta.h              {$(Ph)}celula_temporaria.h  \
    {$(Ph)}coluna_base.h        {$(Ph)}colunas_aleatorias.h {$(Ph)}condicao_retorno.h   \
    {$(Ph)}lista.h              {$(Ph)}persistencia.h      
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\testpersistencia.obj   $(Fobj)\persistencia.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TestePersistencia
###
##################################################

