#define ESC 27
#define TOPO_TELA 350
#define FUNDO_TELA -350
#define ESQUERDA_TELA -350
#define DIREITA_TELA 350
#define CENTRO 0
#define PASSO_DO_PERSONAGEM 0.001
enum Sentido { parado, direita, esquerda, cima, baixo };

//estrutura de ponto ou cordenada
typedef struct Coordenadas{
	float x,y; //2D
}ponto;

typedef struct Perso {
    float x, y;
	float comprimento;
    Sentido sentido;
} perso;
