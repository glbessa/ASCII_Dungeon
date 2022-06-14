#include "monstro.h"

#include <stdlib.h>
#include "utils.h"

// cria uma colecao de monstro atribuindo o monstro da mesma
ColecaoMonstros *criarColecaoMonstros() {
  ColecaoMonstros *colecao = (ColecaoMonstros *) malloc(sizeof(ColecaoMonstros));
  verificarPonteiro(colecao, "Erro ao alocar memoria para os monstros");
  return colecao;
}

// serve para adicionar um monstro ao final de uma colecao de monstros
void adicionarColecaoMonstros(ColecaoMonstros *inicio, Monstro *monstro) {
  ColecaoMonstros *atual = inicio;
  for (; atual->prox != NULL; atual = atual->prox);
  atual->prox = criarColecaoMonstros();
  atual->prox->monstro = monstro;
}

// serva para remover um monstro da colecao de monstros com base no endereco que
// esta armazenado determinado monstro
void removerColecaoMonstros(ColecaoMonstros *inicio, Monstro *monstro) {
  ColecaoMonstros *atual = inicio;
  for (; atual->prox->monstro != monstro; atual = atual->prox);
  ColecaoMonstros *temp = atual->prox;
  atual->prox = atual->prox->prox;
  free(temp->monstro);
  free(temp);
}

void limparColecaoMonstros(ColecaoMonstros *inicio)
{
  ColecaoMonstros *atual = inicio, *temp;
  while (atual != NULL)
  {
    temp = atual;
    atual = atual->prox;
    if (temp->monstro != NULL)
    {
	excluirPosicao(temp->monstro->pos);
    	free(temp->monstro);
    }
    free(temp);
  }
}

// funcao que cria qualquer tipo de monstro, pode ser usada para expandir a quantidade de tipos de monstro
Monstro *criarMonstro(char caractere, int vida, unsigned int x, unsigned int y) {
  Monstro *monstro = (Monstro *)malloc(sizeof(Monstro));
  verificarPonteiro(monstro, "Erro ao alocar monstro!");

  monstro->caractere = caractere;
  monstro->vida = vida;
  monstro->pos = criarPosicao(x, y);

  return monstro;
}

Monstro *criarAranha(unsigned int x, unsigned int y) {
  return criarMonstro('M', 10, x, y);
}

Monstro *criarGlobin(unsigned int x, unsigned int y) {
  return criarMonstro('G', 12, x, y);
}

Monstro *criarEsqueleto(unsigned int x, unsigned int y) {
  return criarMonstro('E', 15, x, y);
}

Monstro *criarDragao(unsigned int x, unsigned int y) {
  return criarMonstro('D', 25, x, y);
}

/* funcao para limitar e numerar o dano dos monstros */
int danoMonstro(char caracterPos) {
  int dano;
  int modAtq, limiteDano;

  switch (caracterPos) {
  case 'M':
    modAtq = 2;
    limiteDano = 4;
    break;
  case 'G':
    modAtq = 3;
    limiteDano = 6;
    break;
  case 'E':
    modAtq = 4;
    limiteDano = 8;
    break;
  case 'D':
    modAtq = 6;
    limiteDano = 11;
    break;
  }

  dano = numeroAleatorio(limiteDano) + modAtq;

  return dano;
}

/* funcao que move os monstros em direcao x e y */
void moverMonstro(Monstro *monstro, Posicao *pos)
{
  monstro->pos->x = pos->x;
  monstro->pos->y = pos->y;
  excluirPosicao(pos);
}

/* funcao para pegar o monstro da colecao */
Monstro *pegarMonstroEm(Posicao *pos, ColecaoMonstros *monstros)
{
  ColecaoMonstros *atual = monstros->prox;
  while (1)
  {
    if (atual == NULL)
      return NULL;
    else if (compararPosicao(pos, atual->monstro->pos))
      return atual->monstro;
  
    atual = atual->prox;
  }
}

Posicao *transDirecaoPosicao(int direcao, Monstro *monstro)
{
  Posicao *novaPosicao;
  switch(direcao)
  {
    case Acima:
      novaPosicao = criarPosicao(monstro->pos->x, (monstro->pos->y) - 1);
      break;
    case Direita:
      novaPosicao = criarPosicao((monstro->pos->x) + 1, monstro->pos->y);
      break;
    case Abaixo:
      novaPosicao = criarPosicao(monstro->pos->x, (monstro->pos->y) + 1);
      break;
    case Esquerda:
      novaPosicao = criarPosicao((monstro->pos->x) - 1, monstro->pos->y);
      break;
    case Nenhuma:
      novaPosicao = monstro->pos;
      break;
  }
  return novaPosicao;
}


Monstro *checarMonstrosPosicao(ColecaoMonstros *colecao, Posicao *posicao)
{
  ColecaoMonstros *atual = colecao;
  for (; compararPosicao(posicao, atual->monstro->pos) || atual != NULL; atual = atual->prox);
  return atual->monstro;
}

/* funcao para excluir o monstro quando ele for morto */
void matarMonstro(Monstro *monstro, ColecaoMonstros *colecao)
{
  removerColecaoMonstros(colecao, monstro);
}
