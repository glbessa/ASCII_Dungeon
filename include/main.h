#ifndef MAIN_H
#define MAIN_H

#include <ncurses.h>
#include "nivel.h"
// #include "monstro.h"
#include "jogador.h"
// #include "utils.h"

int main();
Posicao *detectarInput(WINDOW *janela, char input, Jogador *jogador);
void loopJogo(Nivel *nivel);
int controleMenu(char **opcoes, int tamanho, int maxX, int maxY);
int inicialMenu(int maxX, int maxY);
void inventarioMenu(Jogador *jogador, int maxX, int maxY);

#endif
