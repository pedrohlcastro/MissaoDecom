#define ESC 27
#define TOPO_TELA 350
#define FUNDO_TELA -350
#define ESQUERDA_TELA -350
#define DIREITA_TELA 350
#define CENTRO 0
#define ALTURA 20
#define PASSO_DO_PERSONAGEM 0.001
#define QTD_TELAS 5
enum Sentido {normal, cima, baixo, perdeu};
enum Telas {MENU=0, JOGO, PAUSE, GAME_OVER, WIN};


//estrutura de ponto ou cordenada
typedef struct Coordenadas{
	float x,y; //2D
}ponto;
