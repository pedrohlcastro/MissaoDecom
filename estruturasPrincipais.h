#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define TOPO_TELA 250
#define FUNDO_TELA -250
#define ESQUERDA_TELA -250
#define DIREITA_TELA 250
#define TELA_LARGURA 700
#define TELA_ALTURA 350
#define CENTRO -100
#define ALTURA 30
#define PASSO_DO_PERSONAGEM 0.3
#define QTD_TELAS 5
#define DESIRED_FPS 60
#define AUMENTO_VELOCIDADE 5

enum Sentido {normal, cima, baixo, perdeu};
enum Telas {ABERTURA = 0, MENU, CREDITOS, PAUSE, GAME_OVER, CONF, JOGO, RANK,LISTA_RANK};

//estrutura de ponto ou cordenada
typedef struct Coordenadas{
	float x,y; //2D
}ponto;

typedef struct Jogador{
	std::string nome;
	int pontos;
}jogador;
