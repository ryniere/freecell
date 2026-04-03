# FreeCell

Reimaginacao moderna do jogo FreeCell, originalmente desenvolvido como trabalho final da disciplina **INF1301 — Programacao Modular** na **PUC-Rio**, em junho de 2009.

## Origem

O projeto original foi desenvolvido em C para Windows XP por:

- **Carla Galdino**
- **Eliana Goldner**
- **Ryniere Silva**

A implementacao original seguia uma arquitetura modular com modulos separados para Carta, Baralho, Coluna Base, Coluna Aleatoria, Celula Temporaria, Lista Generica, Persistencia, Gerenciador, entre outros — todos com testes automatizados via scripts e um framework de testes proprio do curso. O codigo fonte em C, a documentacao e os scripts de teste originais estao preservados na pasta `INF1301-Trab04-CGWELGRSS/`.

## Esta versao

Em 2026, Ryniere decidiu recriar o jogo como uma aplicacao web moderna, mantendo o visual inspirado no FreeCell classico do Windows.

### Stack

- **React 19** + **TypeScript**
- **Vite** (bundler)
- **Tailwind CSS v4**

### Como rodar

```bash
npm install
npm run dev
```

O jogo abre em `http://localhost:5173`.

### Funcionalidades

- Jogo completo de FreeCell com regras classicas
- Drag and drop para mover cartas
- Duplo-clique para enviar cartas automaticamente para a base (com animacao)
- Auto-supermove: move cartas bloqueadas automaticamente usando celulas livres
- Desfazer (Ctrl+Z), Novo Jogo (Ctrl+N)
- Salvar/Carregar jogo no localStorage
- Estatisticas de partidas
- Tema claro/escuro
- Efeitos sonoros
- Animacao de vitoria com confetti

## Licenca

Projeto academico / pessoal.
