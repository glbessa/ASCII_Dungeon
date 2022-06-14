#include "utils.h"

#include <stdlib.h>
#include "tela.h"

// funcao que verifica se o ponteiro esta disponivel para utilizacao, caso nao esteja imprime mensagem de aviso em stderr
void verificarPonteiro(void *ptr, const char *msg)
{
    if (ptr == NULL)
    {
        imprimirErro(msg);
        encerrarTela();
        exit(1);
    }
}

// serve para simplificar a criacao de posicoes
Posicao *criarPosicao(unsigned int x, unsigned int y)
{
    Posicao *novaPosicao = (Posicao *) malloc(sizeof(Posicao));
    novaPosicao->x = x;
    novaPosicao->y = y;

    return novaPosicao;
}

// 0 diferentes, 1 iguais
int compararPosicao(Posicao *pos1, Posicao *pos2)
{
  if (pos1->x == pos2->x && pos1->y == pos2->y)
    return 1;
  return 0;
}

// limpa uma posicao antiga da memoria
void excluirPosicao(Posicao *pos)
{
    free(pos);
}

// funcao que implementa a criacao de numeros aleatorios
//    argumento max eh exclusivo, ou seja, caso o numero retornado pela funcao rand seja igual a max, essa funcao ira retornar [0, max)
int numeroAleatorio(int max)
{
    return rand() % max;
}
