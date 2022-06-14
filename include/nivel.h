#ifndef NIVEL_H
#define NIVEL_H

#include <ncurses.h>
#include "jogador.h"
#include "monstro.h"
#include "utils.h"

// lista encadeada com cabeca para armazenar os baus
typedef struct Baus Baus;
struct Baus
{
  Posicao *pos;
  Baus *prox;
};

typedef struct Nivel Nivel;
struct Nivel
{
  unsigned int altura;
  unsigned int comprimento;
  char *mapa;
  Jogador *jogador;
  ColecaoMonstros *monstros;
  Baus *baus;
  int bausAbertos;
};

Nivel *criarNivel();
Nivel *carregarNivel(const char *nomeArquivo);
void limparNivel(Nivel *nivel);
void checarPosicao(WINDOW *janela, Nivel *nivel, Posicao *novaPosicao);
int checarPosicaoMonstro(WINDOW *janela, Monstro *monstro, Posicao *novaPosicao, Nivel *nivel);
void ataqueJogador(Nivel *nivel, Monstro *monstro);
void ataqueMonstro(Monstro *monstro, Jogador *jogador);
void moverMonstros(WINDOW *janela, Nivel *nivel);

/*baus*/
Baus *criarBaus();
void adicionarBaus(Baus *baus, Posicao *pos);
Baus *pegarBauEm(Baus *baus, Posicao *pos);
void excluirBau(Baus *baus, Baus *bau);

#endif
