#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define TOPO_TELA 350
#define FUNDO_TELA -350
#define ESQUERDA_TELA -350
#define DIREITA_TELA 350
#define TELA_LARGURA 700
#define TELA_ALTURA 350
#define CENTRO 0
#define ALTURA 20
#define PASSO_DO_PERSONAGEM 0.3
#define QTD_TELAS 5
#define DESIRED_FPS 60

enum Sentido {normal, cima, baixo, perdeu};
enum Telas {MENU=0, CREDITOS, PAUSE, GAME_OVER, JOGO, CARREGANDO, CONF, WIN,RANK,LISTA_RANK};

//estrutura de ponto ou cordenada
typedef struct Coordenadas{
	float x,y; //2D
}ponto;

typedef struct Jogador{
	std::string nome;
	int pontos;
}jogador;
