#include "nivel.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "jogador.h"
#include "monstro.h"
#include "tela.h"
#include "utils.h"

// cria a struct nivel
Nivel *criarNivel()
{
  Nivel *nivel = (Nivel *) malloc(sizeof(Nivel));
  verificarPonteiro(nivel, "Erro ao alocar memoria para nivel!");
  return nivel;
}

// cria uma lista encadeada com cabeca para armazenar os baus
Baus *criarBaus()
{
  Baus *baus = (Baus *) malloc(sizeof(Baus));
  verificarPonteiro(baus, "Erro ao alocar memoria para baus!");
  baus->pos = NULL;
  baus->prox = NULL;
  return baus;
}

void adicionarBaus(Baus *baus, Posicao *pos)
{
  Baus *atual = baus;
  for (; atual->prox != NULL; atual = atual->prox);
  atual->prox = criarBaus();
  atual->prox->pos = pos;
}

// encontra na lista de baus aquele que esta em determinada posicao
Baus *pegarBauEm(Baus *baus, Posicao *pos)
{
  Baus *atual = baus->prox;
  while(!compararPosicao(pos, atual->pos) && atual->prox != NULL)
  {
    atual = atual->prox; 
  } 
  return atual;
}

void excluirBau(Baus *baus, Baus *bau)
{
  Baus *atual = baus, *temp;
  for(; atual->prox != bau; atual = atual->prox);
  temp = atual->prox;
  atual->prox = atual->prox->prox;
  free(temp->pos);
  free(temp);
}

void limparBaus(Baus *baus)
{
  Baus *atual = baus, *temp;
  while (atual != NULL)
  {
    temp = atual;
    atual = atual->prox;
    excluirPosicao(temp->pos);
    free(temp);
  }
}
// funcao para abrir arquivo que ira conter o mapa
Nivel *carregarNivel(const char *nomeArquivo)
{
  unsigned int xJog, yJog, quantMonstros, quantBaus;
  Nivel *nivel;
  
  FILE *arquivo = fopen(nomeArquivo, "r");
  verificarPonteiro(arquivo, "Erro ao abrir arquivo de mapa!");
  
  nivel = criarNivel();
  fscanf(arquivo, "%u %u", &nivel->comprimento, &nivel->altura);
  fscanf(arquivo, "%u %u", &xJog, &yJog);
  nivel->jogador = criarJogador(30, xJog, yJog);

  // criacao e config da primeira arma do jogador
  Arma *armaInicial = criarAdaga();
  equiparArma(armaInicial, nivel->jogador);
  nivel->jogador->inventario = criarInventario(TipoArma, (void *) armaInicial);

  // le a quantidade de monstros
  fscanf(arquivo, "%u", &quantMonstros);
  // cria uma lista encadeada com cabeca
  nivel->monstros = criarColecaoMonstros();
  for (int i = 0; i < quantMonstros; i++)
  {
    char caractere;
    unsigned int x, y;
    fscanf(arquivo, "%c %u %u", &caractere, &x, &y);
    switch(caractere)
    {
      case 'M':
        adicionarColecaoMonstros(nivel->monstros, criarAranha(x, y));
        break;
      case 'G':
        adicionarColecaoMonstros(nivel->monstros, criarGlobin(x, y));
        break;
      case 'E':
        adicionarColecaoMonstros(nivel->monstros, criarEsqueleto(x, y));
        break;
      case 'D':
        adicionarColecaoMonstros(nivel->monstros, criarDragao(x, y));     
        break;
      default:
        i--;
        break;
    }
  }

  fscanf(arquivo, "%u", &quantBaus);

  nivel->baus = criarBaus();
  nivel->bausAbertos = 0;
  
  for (int i = 0; i < quantBaus; i++)
  {
    unsigned int x, y;
    fscanf(arquivo, "%u %u", &x, &y);
    adicionarBaus(nivel->baus, criarPosicao(x, y));
  }
  
  nivel->mapa = (char *) malloc(sizeof(char) * nivel->altura * nivel->comprimento);

  for (int i = 0; i < nivel->altura; i++)
  {
    for (int j = 0; j < nivel->comprimento; j++)
    {
      
      char temp = fgetc(arquivo);
      switch(temp)
      {
        case ' ':
        case '|':
        case '=':
        case '#':
          *(nivel->mapa+((i*(nivel->comprimento))+j)) = temp;
          break;
        default:
          j--;
          break;
      }
    }      
  }
  return nivel;    
}

void limparNivel(Nivel *nivel)
{
  limparColecaoMonstros(nivel->monstros);
  limparJogador(nivel->jogador);
  limparBaus(nivel->baus);
  free(nivel->mapa);
}

/* checa a proxima posição do player, pra ver se ele anda, ataca algum monstro ou abre um bau */
void checarPosicao(WINDOW *janela, Nivel *nivel, Posicao *novaPosicao)
{
  char caracterPos = pegarCharPorPosicao(janela, novaPosicao);
  switch (caracterPos)
    {
      case ' ':
      case '#':
          moverJogador(novaPosicao, nivel->jogador);
          desenhaJogador(janela, nivel->jogador);
          break;
      case 'M':
      case 'G':
      case 'E':
      case 'D':
          ataqueJogador(nivel, pegarMonstroEm(novaPosicao, nivel->monstros));
          desenhaMonstros(janela, nivel->monstros);
          desenhaJogador(janela, nivel->jogador);
          break;
      case 'B':
          abrirBau(nivel->jogador->inventario, nivel->bausAbertos);
          nivel->bausAbertos += 1;
          excluirBau(nivel->baus, pegarBauEm(nivel->baus, novaPosicao));
          break;
      default:
          break;
    }

}

/* checa a proxima posição do monstro, para saber se ele anda ou ataca o player */
int checarPosicaoMonstro(WINDOW *janela, Monstro *monstro, Posicao *novaPosicao, Nivel *nivel)
{
    char caracterPos = pegarCharPorPosicao(janela, novaPosicao);
    switch (caracterPos)
    {
        case ' ':
            moverMonstro(monstro, novaPosicao);
            break;
        case '@':
            ataqueMonstro(monstro, nivel->jogador);
            break;
        default:
            break;
    }
  return 1;
}

/* funcao para os monstros se movimentarem */
void moverMonstros(WINDOW *janela, Nivel *nivel)
{
  ColecaoMonstros *atual = nivel->monstros->prox;
  for(; atual != NULL; atual = atual->prox)  
  {
    int aleatorio = numeroAleatorio(5);
    checarPosicaoMonstro(janela, atual->monstro,transDirecaoPosicao(aleatorio, atual->monstro), nivel);
  }
}

void ataqueJogador(Nivel *nivel, Monstro *monstro)
{
  /* ataque do jogador */
  monstro->vida -= danoJogador(nivel->jogador);
  if (monstro->vida > 0)
  {
    nivel->jogador->vida -= danoMonstro(monstro->caractere);
  }
  else
  {
    matarMonstro(monstro, nivel->monstros);
  } 
}

/* ataque do monstro */
void ataqueMonstro(Monstro *monstro, Jogador *jogador)
{
  jogador->vida -= danoMonstro(monstro->caractere);
  if (jogador->vida > 0)
  {
    monstro->vida -= danoJogador(jogador);
  }
}
