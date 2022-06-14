#ifndef MONSTRO_H
#define MONSTRO_H

#include "utils.h"

// acima = 0, direita = 1, abaixo = 2, esquerda = 3, nenhuma = 4
enum Direcao{Acima, Direita, Abaixo, Esquerda, Nenhuma};

// estrutura que define os monstros
typedef struct Monstro Monstro;
struct Monstro
{
    char caractere;
    int vida;
    Posicao *pos;
};

// lista encadeada com cabeca que serve para armazenar tds monstros
typedef struct ColecaoMonstros ColecaoMonstros;
struct ColecaoMonstros
{
    Monstro *monstro;
    ColecaoMonstros *prox;
};

// operacoes com colecoes de monstros
ColecaoMonstros *criarColecaoMonstros();
void adicionarColecaoMonstros(ColecaoMonstros *inicio, Monstro *monstro);
void removerColecaoMonstros(ColecaoMonstros *inicio, Monstro *monstro);
void removerCMPorPosicao(ColecaoMonstros *inicio, Posicao *pos);
void limparColecaoMonstros(ColecaoMonstros *inicio);
// ------------------------------------------------------------------------

// operacoes com monstros
Monstro *criarMonstro(char caractere, int vida, unsigned int x, unsigned int y);
Monstro *criarAranha(unsigned int x, unsigned int y);
Monstro *criarGlobin(unsigned int x, unsigned int y);
Monstro *criarEsqueleto(unsigned int x, unsigned int y);
Monstro *criarDragao(unsigned int x, unsigned int y);
int danoMonstro(char caracterPos);
Monstro *pegarMonstroEm(Posicao *pos, ColecaoMonstros *monstros);
Posicao *transDirecaoPosicao(int direcao, Monstro *monstro);
Monstro *checarMonstrosPosicao(ColecaoMonstros *colecao, Posicao *posicao);
void matarMonstro(Monstro *monstro, ColecaoMonstros *colecao);

#endif
