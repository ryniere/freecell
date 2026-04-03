##################################################
###
### Diretivas de MAKE para o construto: CriaLib
### Gerado a partir de: CriaLib.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = CriaLib


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
   $(Fobj)\carta.obj   $(Fobj)\lista.obj   $(Fobj)\tratamento_falha.obj \
   $(Fobj)\baralho.obj   $(Fobj)\celula_temporaria.obj   $(Fobj)\coluna_base.obj \
   $(Fobj)\colunas_aleatorias.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\carta.obj :  {$(Pc)}\carta.c \
    {$(Ph)}carta.h              {$(Ph)}condicao_retorno.h   {$(Ph)}lista.h              \
    {$(Ph)}privilegiocarta.h   
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    ..\\tabelas\\idtiposespaco.def ..\\tabelas\\tipoespacoslista.def {$(Ph)}cespdin.h            \
    {$(Ph)}conta.h              {$(Ph)}generico.h           {$(Ph)}lista.h              \
    {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\tratamento_falha.obj :  {$(Pc)}\tratamento_falha.c \
    {$(Ph)}baralho.h            {$(Ph)}carta.h              {$(Ph)}celula_temporaria.h  \
    {$(Ph)}coluna_base.h        {$(Ph)}colunas_aleatorias.h {$(Ph)}condicao_retorno.h   \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\baralho.obj :  {$(Pc)}\baralho.c \
    {$(Ph)}baralho.h            {$(Ph)}carta.h              {$(Ph)}condicao_retorno.h   \
    {$(Ph)}lista.h              {$(Ph)}privilegiocarta.h   
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\celula_temporaria.obj :  {$(Pc)}\celula_temporaria.c \
    {$(Ph)}carta.h              {$(Ph)}celula_temporaria.h  {$(Ph)}condicao_retorno.h   \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\coluna_base.obj :  {$(Pc)}\coluna_base.c \
    {$(Ph)}carta.h              {$(Ph)}coluna_base.h        {$(Ph)}condicao_retorno.h   \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\colunas_aleatorias.obj :  {$(Pc)}\colunas_aleatorias.c \
    {$(Ph)}baralho.h            {$(Ph)}carta.h              {$(Ph)}colunas_aleatorias.h \
    {$(Ph)}condicao_retorno.h   {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\carta.obj   $(Fobj)\lista.obj   $(Fobj)\tratamento_falha.obj \
   $(Fobj)\baralho.obj   $(Fobj)\celula_temporaria.obj   $(Fobj)\coluna_base.obj \
   $(Fobj)\colunas_aleatorias.obj
    cd $(Fobj)
    LIB $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: CriaLib
###
##################################################

