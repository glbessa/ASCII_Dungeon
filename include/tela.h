#ifndef TELA_H
#define TELA_H

#include <ncurses.h>
#include "jogador.h"
#include "nivel.h"

WINDOW *criarJanela(int altura, int comprimento, int y, int x);

void iniciarTela();
void encerrarTela();
void imprimirMenu(WINDOW *janela, int selecionado, char **opcoes, int tamanhoOpcoes);
void imprimirMapa(WINDOW *janela,Nivel *nivel);
void imprimirStatus(WINDOW *janela, Jogador *jogador, int maxY);
void imprimirNivel(WINDOW *janela, Nivel *nivel);
void imprimirInventario(WINDOW *janela, Inventario *inventario, int selecionado);
void imprimirMensagem(WINDOW *mae, char *mensagem, int tamanhoMsg, int tamanhoY);
void imprimirErro(const char *msg);

//Func desenhaJogador
void desenhaJogador(WINDOW *janela, Jogador *jogador);
//Func desenhaMonstros
void desenhaMonstros(WINDOW *janela, ColecaoMonstros *colecao);
void desenhaBaus(WINDOW *janela, Baus *bau);

char pegarCharPorPosicao(WINDOW *janela, Posicao *pos);

#endif