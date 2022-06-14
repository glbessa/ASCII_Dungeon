#ifndef JOGADOR_H
#define JOGADOR_H

#include "utils.h"

#define LIMITE_NOME 50

enum tiposObjeto{TipoArma, TipoComida};

typedef struct Inventario Inventario;
struct Inventario
{
  short tipoObjeto;
  void *objeto;
  Inventario *prox;
};

// estrutura que define os atributos que todas as armas devem ter
typedef struct Arma Arma;
struct Arma
{
    char *nome;
    int modAtaque;
    int limiteDano;
};

// estrutura que define os atributos de itens
//     vidaRecuperacao : recupera a vida do jogador
typedef struct Comida Comida;
struct Comida
{
    char *nome;
    int recuperacaoVida;
};

typedef struct Jogador Jogador;
struct Jogador
{
    Posicao *pos;
    char caractere;
    int vida;
    int dano;
    int vidaLimite;
    Arma *armaEquipada;
    Inventario *inventario;
};


/*JOGADOR*/
Jogador *criarJogador(unsigned int vida, unsigned int x, unsigned int y);
void moverJogador(Posicao * novaPosicao, Jogador * jogador);
void atribuirPosicaoJogador(int x, int y, Jogador *jogador);
int danoJogador(Jogador *jogador);
void limparJogador(Jogador *jogador);

/*ARMA*/
void equiparArma(Arma *novaArma, Jogador *jogador);
Arma *criarArma(char *nome, int modAtaque, int limiteDano);
Arma *criarAdaga();
Arma *criarRapiera();
Arma *criarEspada();
Arma *criarAlabarda();

/*COMIDA*/
Comida *criarComida(char *nome, int recuperacaoVida);
void comerComida(Comida *comida, Jogador *jogador);
int pegarDanoLimite(Jogador *jogador);

// manipulacao de objetos
Inventario *criarInventario(short tipoObjeto, void *objeto);
Inventario *pegarObjetoPorIndice(int indice, Inventario *inventario);
void removerObjetoPorEndereco(Inventario *inventario, Inventario *objeto);
void removerObjetoPorIndice(int indice, Inventario *inventario);
void limparInventario(Inventario *inventario);
int quantidadeObjetos(Inventario *inventario);
void inventarioParaArray(Inventario *inventario, char **arrayIdObjetos, int tamanhoArray);
char *armaParaString(Arma *arma);
char *comidaParaString(Comida *comida);

// BAU
void abrirBau(Inventario *inventario, int bausAbertos);

#endif
