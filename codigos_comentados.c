//strncpy(arrayIdObjetos[i], "Vazio", LIMITE_NOME);

/*char pegarCharPorPosicao(Nivel *nivel, Posicao *pos)
{
  return *(nivel->mapa+((pos->y*nivel->altura) + pos->x));
}*/  

// void atribuirPosicaoJogador(int x, int y, Jogador *jogador)
// {
//   jogador->pos = criarPosicao(x, y);
// }

/*void inventarioParaArray(Inventario *inventario, char **arrayIdObjetos, int tamanhoArray)
{
  Inventario *atual = inventario;
  for(int i = 0; atual != NULL; atual = atual->prox)
  {
    switch(atual->tipoObjeto)
    {
      case TipoArma:
        {
          Arma *arma = (Arma *) atual->objeto;
          char *info = armaParaString(arma);
          sscanf(arrayIdObjetos[i], "%s", info);
          break;
        }
      case TipoComida:
        {
          Comida *comida = (Comida *) atual->objeto;
          char *info = comidaParaString(comida);
          sscanf(arrayIdObjetos[i], "%s", info);
          break;
        }
      default:
        {
          //strncpy(arrayIdObjetos[i], "Vazio", LIMITE_NOME);
          break;
        }
       
    }
    i++;
  }
}*/

// char *armaParaString(Arma *arma)
// {
//   char *str = (char *) malloc(sizeof(char) * LIMITE_NOME);
//   sscanf(str, "%s - Dano: %d/%d", arma->nome, &arma->modAtaque, &arma->limiteDano);
//   return str;
// }

// char *comidaParaString(Comida *comida)
// {
//   char *str = (char *) malloc(sizeof(char) * LIMITE_NOME);
//   sscanf(str, "%s - Recuperacao: %d", comida->nome, &comida->recuperacaoVida);
//   return str;
// }

//int mvwaddch(WINDOW *win, int y, int x, const chtype ch)

//void combate(Jogador *jogador, char caracterPos);

//void atacarMonstro(Jogador *jogador, Monstro *monstro);
//void moverJogador(Sala *sala);

/*
// lista encadeada sem cabeca que armazena uma sequencia de armas
typedef struct ColecaoArmas ColecaoArmas;
struct ColecaoArmas
{
    Arma arma;
    ColecaoArmas *prox;
};

// lista encadeada sem cabeca que armazena uma sequencia de itens
typedef struct ColecaoItens ColecaoItens;
struct ColecaoItens
{
    Item item;
    ColecaoItens *prox;
};
*/
//void destruirMonstro(Monstro *monstro); funcao para implementar
//void atacarJogador(Monstro *monstro, Jogador *jogador);
