#include "main.h"

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "nivel.h"
#include "monstro.h"
#include "jogador.h"
#include "tela.h"
#include "utils.h"

#define PERDEU "Você Morreu!"
#define GANHOU "Parabens!"
#define ARQUIVO_NIVEL_1 "./niveis/nivel1.txt"

int main()
{
  srand(time(NULL));
  iniciarTela();
  // pega o tamanho da tela
  int maxX, maxY, selecionado;
  getmaxyx(stdscr, maxY, maxX);

  // menu inicial
  do
  {
    selecionado = inicialMenu(maxX, maxY);
    clear(); // limpa a tela
    switch(selecionado)
    {
      case 0:
        // loop do jogo que recebe o nivel
        loopJogo(carregarNivel(ARQUIVO_NIVEL_1));
        break;
    }
  } while (selecionado != 1);
  encerrarTela();
  return 0;
}

// loop principal
void loopJogo(Nivel *nivel)
{
  int maxX, maxY;
  int entrada;
  // pegando o tamanho da tela
  getmaxyx(stdscr, maxY, maxX);
  // --------------------------

  // cria uma janela para centralizar tudo
  WINDOW *janela = newwin(nivel->altura+1, nivel->comprimento, 0, (maxX - nivel->comprimento)/2);

  clear();
  imprimirNivel(janela, nivel);
  while((entrada = wgetch(janela)) != 'q')
  {
    // pega a entrada do jogador e transforma numa posicao
    Posicao *novaPos = detectarInput(janela, entrada, nivel->jogador);
    // verifica oq o jogador vai fazer se ir para aquela posicao, por exemplo, ficar parado
    checarPosicao(janela, nivel, novaPos);
    moverMonstros(janela, nivel);
    // verifica se o jogador morreu
    if (nivel->jogador->vida <= 0)
    {
      imprimirNivel(janela, nivel);
      imprimirMensagem(janela, PERDEU, strlen(PERDEU), 5);
      delwin(janela);
      clear();
      refresh();
      limparNivel(nivel);
      return;
    }
    else if (nivel->monstros->prox == NULL)
    {
      imprimirNivel(janela, nivel);
      imprimirMensagem(janela, GANHOU, strlen(GANHOU), 5);
      delwin(janela);
      clear();
      refresh();
      limparNivel(nivel);
      return;
    }
    refresh();
    imprimirNivel(janela, nivel);
  }
}

Posicao *detectarInput(WINDOW *janela, char input, Jogador *jogador)
{
  int maxX, maxY;
  getmaxyx(janela, maxY, maxX);
  Posicao *novaPosicao;
  switch (input)
  {
    /* mover pra cima */
    case 'w':
    case 'W':
      novaPosicao = criarPosicao(jogador->pos->x, (jogador->pos->y) - 1);
      break;
    /* mover pra baixo */
    case 's':
    case 'S':
      novaPosicao = criarPosicao(jogador->pos->x, (jogador->pos->y) + 1);
      break;
    /* mover para direita */
    case 'd':
    case 'D':
      novaPosicao = criarPosicao((jogador->pos->x) + 1, jogador->pos->y);
      break;
    /* mover para esquerda */
    case 'a':
    case 'A':
      novaPosicao = criarPosicao((jogador->pos->x) - 1, jogador->pos->y);
      break;
    case 'i':
    case 'I':
      inventarioMenu(jogador, maxX, maxY);
    default:
        break;
    }
    return novaPosicao;
}

// ------------------------------------------------------------
// MENUs ------------------------------------------------------

int controleMenu(char **opcoes, int tamanho, int maxX, int maxY)
{
  int selecionado = 0;
  int escolha = 0;
  WINDOW *janela;
  int alturaJanela=tamanho+2, comprimentoJanela=LIMITE_NOME+2;
  // ---------------------------------------
  
  // tentando criar a janela no meio da tela
  janela = criarJanela(alturaJanela, comprimentoJanela, ((maxY - alturaJanela)/2), (maxX - comprimentoJanela)/2);
    
  imprimirMenu(janela, selecionado, opcoes, tamanho);
  do
  { 
    switch (escolha)
    {
      case KEY_UP:
        selecionado--;
        if (selecionado <= -1)
          selecionado = 0;
        break;
      case KEY_DOWN:
        selecionado++;
        if (selecionado >= tamanho)
          selecionado = tamanho - 1;
        break;
      
      default:
        break;
    }

    imprimirMenu(janela, selecionado, opcoes, tamanho);
  } while((escolha = wgetch(janela)) != 10);

  delwin(janela);
  
  return selecionado;
}

int inicialMenu(int maxX, int maxY)
{
  const int tamanho = 2;
  char *opcoes[] = {
    "NIVEL 1",
    "SAIR"
  };

  return controleMenu(opcoes, tamanho, maxX, maxY);
}

void inventarioMenu(Jogador *jogador, int maxX, int maxY)
{
  int selecionado = 0;
  int escolha = 0;
  int tamanho = quantidadeObjetos(jogador->inventario);
  
  // atributos da janela de menu
  WINDOW *janela;
  int alturaJanela=tamanho+2, comprimentoJanela=LIMITE_NOME+2;
  // ---------------------------------------

// tentando criar a janela no meio da tela
  janela = criarJanela(alturaJanela, comprimentoJanela, ((maxY - alturaJanela)/2), (maxX - comprimentoJanela)/2);
    
  imprimirInventario(janela, jogador->inventario, selecionado);
  do
  { 
    if (escolha == 'q')
      break;
    switch (escolha)
    {
      case KEY_UP:
        selecionado--;
        if (selecionado <= -1)
          selecionado = 0;
        break;
      case KEY_DOWN:
        selecionado++;
        if (selecionado >= tamanho)
          selecionado = tamanho - 1;
        break; 
      default:
        break;
    }
    imprimirInventario(janela, jogador->inventario, selecionado);
  } while((escolha = wgetch(janela)) != 10);

  delwin(janela);
  
  Inventario *obj = pegarObjetoPorIndice(selecionado, jogador->inventario);
  
  switch(obj->tipoObjeto)
  {
    case TipoArma:
      equiparArma((Arma *) obj->objeto, jogador);
      break;
    case TipoComida:
      comerComida((Comida *) obj->objeto, jogador);
      removerObjetoPorEndereco(jogador->inventario, obj);
      break;
    default:
      break;
  }
}
// ---------------------------------------------------------------------- //
