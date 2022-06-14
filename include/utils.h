#ifndef UTILS_H
#define UTILS_H

// estrutura para controlar as coordenadas de uma determinada posicao
typedef struct Posicao Posicao;
struct Posicao
{
  unsigned int x;
  unsigned int y;
};

void verificarPonteiro(void *ptr, const char *msg);
Posicao *criarPosicao(unsigned int x, unsigned int y);
int compararPosicao(Posicao *pos1, Posicao *pos2);
void excluirPosicao(Posicao *pos);
int numeroAleatorio(int max);

#endif

