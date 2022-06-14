#include "jogador.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "monstro.h"

#define LIMITE_NOME 50

/* funcao para criar o jogador */
Jogador *criarJogador(unsigned int vida, unsigned int x, unsigned int y)
{
  Jogador *jogador = (Jogador *) malloc(sizeof(Jogador));
  verificarPonteiro(jogador, "Erro ao alocar memoria para jogador");
  jogador->vida = vida;
  jogador->pos = criarPosicao(x, y);
  return jogador;
}

void limparJogador(Jogador *jogador)
{
  limparInventario(jogador->inventario);
  excluirPosicao(jogador->pos);
  free(jogador);
}

/* funcao para a criacao de armas */
Arma *criarArma(char *nome, int modAtaque, int limiteDano)
{
  Arma *arma = (Arma *) malloc(sizeof(Arma));
  verificarPonteiro(arma, "Erro ao alocar memoria para arma");
  arma->nome = nome;
  arma->modAtaque = modAtaque;
  arma->limiteDano = limiteDano;
  return arma;
}

//adaga - (0 - 8) + 3
Arma *criarAdaga()
{
  return criarArma("Adaga", 3, 8);
}

//rapiera - (0 - 9) + 4
Arma *criarRapiera()
{
  return criarArma("Rapiera", 4, 9);
}

//espada - (0 - 10) + 5
Arma *criarEspada()
{
  return criarArma("Espada", 5, 10);
}

//alabarda - (0 - 12) + 7
Arma *criarAlabarda()
{
  return criarArma("Alabarda", 7, 12);
}

/* funcao para criar comidas */
Comida *criarComida(char *nome, int recuperacaoVida)
{
  Comida *comida = (Comida *) malloc(sizeof(Comida));
  verificarPonteiro(comida, "Erro ao alocar memoria para comida");
  comida->nome = nome;
  comida->recuperacaoVida = recuperacaoVida;
  return comida;
}

Comida *criarMaca()
{
  return criarComida("Maça", 5);
}

Comida *criarPera()
{
  return criarComida("Pera", 7);
}

Comida *criarUva()
{
  return criarComida("Uva", 10);
}

Comida *criarManga()
{
  return criarComida("Manga", 4);
}

Comida *criarMorango()
{
  return criarComida("Morango", 10);
}

/* funcao que move o jogador */
void moverJogador(Posicao *novaPosicao, Jogador *jogador)
{
    jogador->pos->y = novaPosicao->y;
    jogador->pos->x = novaPosicao->x;
    excluirPosicao(novaPosicao);
}

/* funcao para equipar armas */
void equiparArma(Arma *novaArma, Jogador *jogador)
{
  jogador->armaEquipada = novaArma;
}

/* funcao para comer a comida */
void comerComida(Comida *comida, Jogador *jogador)
{
  jogador->vida += comida->recuperacaoVida;
}

/* funcao para limitar o dano das armas */
int pegarDanoLimite(Jogador *jogador)
{
  if (jogador->armaEquipada == NULL)
    return 0;
  return jogador->armaEquipada->limiteDano;
}

/* funcao que cria o inventario */
Inventario *criarInventario(short tipoObjeto, void *objeto)
{
  Inventario *inventario = (Inventario *) malloc(sizeof(Inventario));
  verificarPonteiro(inventario, "Erro ao alocar memoria para inventario!");
  inventario->tipoObjeto = tipoObjeto;
  inventario->objeto = objeto;
  inventario->prox = NULL;
  return inventario;
}

/* funcao para adicionar o inventario */
void adicionarInventario(Inventario *inventario, Inventario *objeto)
{
  Inventario *atual = inventario;
  for (; atual->prox != NULL; atual = atual->prox);
  atual->prox = objeto;
}

Inventario *pegarObjetoPorIndice(int indice, Inventario *inventario)
{
  Inventario *atual = inventario;
  for (int i = 0; atual->prox != NULL && i != indice; i++)
  {
    atual = atual->prox;
  }
  return atual;
}

void removerObjetoPorEndereco(Inventario *inventario, Inventario *objeto)
{
  Inventario *atual = inventario, *temp;
  for(; atual->prox != objeto; atual = atual->prox);
  temp = atual->prox;
  atual->prox = atual->prox->prox;
  free(temp);
}

void removerObjetoPorIndice(int indice, Inventario *inventario)
{
  Inventario *temp;
  if (indice == 0)
  {
    temp = inventario;
    inventario = inventario->prox;
  }
  else
  {
    Inventario *atual = inventario;
    for (int i = 0; atual->prox != NULL || i != indice - 1; i++)
    {
      atual = atual->prox;
    }
    temp = atual->prox;
    atual->prox = atual->prox->prox;
  }
  free(temp);
}

void limparInventario(Inventario *inventario)
{
  Inventario *atual = inventario, *temp;
  while (atual != NULL)
  {
    temp = atual;
    atual = atual->prox;
    free(temp->objeto);
    free(temp);
  }
}

int quantidadeObjetos(Inventario *inventario)
{
  Inventario *atual = inventario;
  int i = 0;
  for (; atual != NULL; i++)
  {
    atual = atual->prox;
  }
  return i;
}

/* funcao para abrir os baus */
void abrirBau(Inventario *inventario, int bausAbertos){
  switch(bausAbertos){
    case 0://-comida   
      adicionarInventario(inventario, criarInventario(TipoComida, criarMaca()));
      break;
    case 1: //-arma
      adicionarInventario(inventario, criarInventario(TipoArma, criarRapiera()));
      break;
    case 2: //-comida
      adicionarInventario(inventario, criarInventario(TipoComida, criarManga()));
      break;
    case 3: //-arma
      adicionarInventario(inventario, criarInventario(TipoArma, criarEspada()));
      break;
    case 4: //-arma
      adicionarInventario(inventario, criarInventario(TipoComida, criarMorango()));
      break;
    case 5: //-comida
      adicionarInventario(inventario, criarInventario(TipoArma, criarAlabarda()));
      break;
  }
  bausAbertos++;
}

/* funcao para gerar o dano do jogador */
int danoJogador(Jogador *jogador)
{
  return numeroAleatorio(jogador->armaEquipada->limiteDano) + jogador->armaEquipada->modAtaque;
}
