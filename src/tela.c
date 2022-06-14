#include "tela.h"

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"
#include "nivel.h"

WINDOW *criarJanela(int altura, int comprimento, int y, int x)
{
  WINDOW *janela;

  janela = newwin(altura, comprimento, y, x); //cria uma nova janela
  box(janela, 0, 0); //cria uma borda em toda a volta da janela
  keypad(janela, TRUE);
  wrefresh(janela);

  return janela;
}

void iniciarTela()
{
    initscr();
    noecho(); // impede que o usuario escreva diretamente na tela
    cbreak();
    curs_set(0);
    refresh();
}

void encerrarTela()
{
  echo();
  endwin();
}

void imprimirMenu(WINDOW *janela, int selecionado, char **opcoes, int tamanhoOpcoes)
{
  int maxX, maxY;
  getmaxyx(janela, maxY, maxX);
  for (int i = 0; i < tamanhoOpcoes; i++)
  {
    int tamanhoStr = strlen(opcoes[i]);
    if(i == selecionado)
      wattron(janela, A_REVERSE);
    mvwprintw(janela, i+1, (maxX - tamanhoStr)/2 , "%s", opcoes[i]);
    wattroff(janela, A_REVERSE);
  }
  wrefresh(janela);
}

void imprimirMapa(WINDOW *janela, Nivel *nivel)
{
  for (int i = 0; i < nivel->altura; i++)
  {
    for (int j = 0; j < nivel->comprimento; j++)
    {
      // imprime um caracter naquele local especifico
      mvwaddch(janela, i, j, *(nivel->mapa+((i*nivel->comprimento)+j)));   
    }
  }
}

void imprimirStatus(WINDOW *janela, Jogador *jogador, int y)
{
  mvwprintw(janela, y, 0, "Vida: %d || %s - %d/%d  --- i (abrir inventario) - q (sair)", jogador->vida, jogador->armaEquipada->nome, jogador->armaEquipada->modAtaque, pegarDanoLimite(jogador));
}

void imprimirNivel(WINDOW *janela, Nivel *nivel)
{
  imprimirMapa(janela, nivel);
  imprimirStatus(janela, nivel->jogador, nivel->altura);
  desenhaJogador(janela, nivel->jogador);
  desenhaMonstros(janela, nivel->monstros);
  desenhaBaus(janela, nivel->baus);
  wrefresh(janela);
}

void imprimirMensagem(WINDOW *mae, char *mensagem, int tamanhoMsg, int tamanhoY)
{
  // usado para definir o meio da tela
  int maxX, maxY;
  WINDOW *janela;
  getmaxyx(stdscr, maxY, maxX);
  
  //stdout, stdin, stderr
  janela = criarJanela(tamanhoY, tamanhoMsg+2, (maxY - tamanhoY)/2, (maxX - tamanhoMsg+2)/2);
  mvwprintw(janela, tamanhoY/2, 1, "%s", mensagem);
  // wrefresh(janela);
  wrefresh(janela);
  getch(); // espera entrada usuario
  delwin(janela); //exclui
}

void imprimirErro(const char *msg)
{
  int maxX, maxY, altura=5, comprimento=100;
  getmaxyx(stdscr, maxY, maxY);

  char *aperteParaSair = "Aperte qualquer tecla para sair...";
  WINDOW *janela = criarJanela(altura, comprimento, (maxY - altura)/2, (maxX - comprimento)/2);
  mvwprintw(janela, 0, ((comprimento-2)-strlen(msg))/2, "%s", msg);
  mvwprintw(janela, 2, ((comprimento-2)-strlen(aperteParaSair))/2, "%s", aperteParaSair);
  getch();
  werase(janela);
  delwin(janela);
}

// Função renderiza o jogador na tela
void desenhaJogador(WINDOW *janela, Jogador *jogador)
{
    mvwaddch(janela, jogador->pos->y, jogador->pos->x, '@');
    //move(jogador->pos->y, jogador->pos->x);
}

// Função renderiza os monstros na tela
void desenhaMonstros(WINDOW *janela, ColecaoMonstros *colecao)
{
  ColecaoMonstros *atual = colecao->prox;
  for(;atual != NULL; atual = atual->prox)
  {
    mvwaddch(janela, atual->monstro->pos->y, atual->monstro->pos->x, atual->monstro->caractere);
  }
}

// Função renderiza os baus na tela
void desenhaBaus(WINDOW *janela, Baus *bau)
{
  Baus *atual = bau->prox;
  for(;atual != NULL; atual = atual->prox)
    {
      mvwaddch(janela, atual->pos->y, atual->pos->x, 'B');
    }
}

char pegarCharPorPosicao(WINDOW *janela, Posicao *pos)
{
  return mvwinch(janela, pos->y, pos->x);
}

void imprimirInventario(WINDOW *janela, Inventario *inventario, int selecionado)
{
  Inventario *atual = inventario;
  for(int i = 0; atual != NULL; atual = atual->prox)
  {
    if(i == selecionado)
      wattron(janela, A_REVERSE);
    switch(atual->tipoObjeto)
    {
      case TipoArma:
        {
          Arma *arma = (Arma *) atual->objeto;
          mvwprintw(janela, i+1, 1, "%s - Dano: %d/%d", arma->nome, arma->modAtaque, arma->limiteDano);
          break;
        }
      case TipoComida:
        {
          Comida *comida = (Comida *) atual->objeto;
          mvwprintw(janela, i+1, 1, "%s - Recuperacao: %d", comida->nome, comida->recuperacaoVida);
          break;
        }
      default:
        {
          break;
        }
      
    }
    wattroff(janela, A_REVERSE);
    i++;
  }
  wrefresh(janela);
}