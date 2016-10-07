#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "estruturasPrincipais.h"
#include "mapa.h"
#include "personagem.h"
#include "tela.h"
using namespace std;

int tempo = 0;
//bool pause = false; == controleTela->getTela() == PAUSE
//bool inGame = false; //caso esteja jogando ===  controleTela->getTela() == JOGO
sf::Music musicaJogo;
string nomeJogador;
//Mapa
Mapa *mapa = new Mapa();

// personagem
Movimento *pers;

//Obstaculos
vector<Obstaculo> vParedes;

//Telas
Tela *controleTela;

//(((((((RANK)))))))
// Create a new FTP client
sf::Ftp ftp;
// Connect to the server
sf::Ftp::Response response = ftp.connect("rankgamedecom.orgfree.com");
vector<jogador> rankJogadores;
bool gravado = false; //gravado arquivo rank

void update(int k){
	tempo++;
	//temporário
	if(pers->verificaColisao(vParedes)){
		gravado = false;
		vParedes.clear();
		controleTela->setTela(GAME_OVER);
		// controleTela->setTela(RANK); // retirei rank por enquanto
	}
	if (controleTela->getTela() == JOGO)
		vParedes = mapa->move(vParedes);

	glutPostRedisplay();
	glutTimerFunc(1000/DESIRED_FPS, update, 0);
}

void escreveTexto(void * font, string s, float x, float y, float z){
    int i;
    glRasterPos3f(x, y, z);

    for (i=0; i < s.size(); i++)
       glutBitmapCharacter(font, s[i]);
}

void conectServer(){
	if(response.isOk())
    	std::cout << "Connected" << std::endl;
	// Log in
	response = ftp.login("rankgamedecom.orgfree.com", "123456");
	if(response.isOk())
		std::cout << "Logged in" << std::endl;
	ftp.keepAlive();
}

void init(){
	std::vector<string> enderecoTexturas;
	enderecoTexturas.push_back("img/fundo_menu.png");
	enderecoTexturas.push_back("img/fundo_creditos.png");
	enderecoTexturas.push_back("img/fundopause.png");
	enderecoTexturas.push_back("img/fundo_perdeu.png");
	enderecoTexturas.push_back("img/fundo_cenario.jpg");

	controleTela = new Tela(enderecoTexturas);
	pers = new Movimento("img/pers.png");
	printf("SERVER:\n");
	conectServer();

	musicaJogo.openFromFile("sound/game.ogg");
	musicaJogo.play();
}

bool sortJogadores(jogador a, jogador b){
	return (a.pontos > b.pontos);
}

void montaRank(){
	string line,line2;
	jogador aux;
	vector<jogador> jogadores;
	int number = 0;
	bool arqVazio = true;
	//baixa rank
	ftp.download("rank.txt", "", sf::Ftp::Ascii);
	cout<<"Download Completed"<<endl;
	ifstream file1 ("rank.txt");
	if (file1.is_open()){
		while(getline (file1,line) && getline (file1,line2)){
			number = 0;
			arqVazio = false;
			aux.nome = line;
			for(int i=0; i<line2.size()-1; i++){
				number += (line2[i] - 48) * pow(10,line2.size() - i - 2);
			}
			aux.pontos = number;
			jogadores.push_back(aux);
		}
		aux.nome = nomeJogador;
		aux.pontos = mapa->getPontuacao();
		jogadores.push_back(aux);
		sort(jogadores.begin(),jogadores.end(),sortJogadores);
		file1.close();
	}
	for(int i=0; i<jogadores.size() && i<7; i++){
		rankJogadores.push_back(jogadores[i]);
	}
	ofstream myfile ("rank.txt",ofstream::out);
	cout<<"Upload Complete"<<endl;
	if(myfile.is_open() && !gravado){
		for(int i=0; i<rankJogadores.size(); i++){
			myfile<<rankJogadores[i].nome<<endl<<rankJogadores[i].pontos<<endl;
		}
		myfile.close();
		gravado = true;
		nomeJogador.clear();
		mapa->zeraPontuacao();
		ftp.upload("rank.txt", "/", sf::Ftp::Ascii);
	}
}

//func de desenha na tela
void desenhaTela(){
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glColor4f(1,1,1,1);

	// escreve pontuação (PASSAR PARA ORIENTAÇÃO)
	string pontos;
	ostringstream convert;
	convert << mapa->getPontuacao();
	pontos = convert.str();
	escreveTexto(GLUT_BITMAP_HELVETICA_18, pontos, 250, 300, 0);
	// fim escreve pontuação

	switch(controleTela->getTela()){
		case MENU:
			controleTela->desenhaTelaSprite(controleTela->getPosicaoTexturaMenu(),controleTela->getPosicaoTexturaMenu()+0.25);
			break;
		case PAUSE:
			controleTela->desenhaTela();
			break;
		case GAME_OVER:
			controleTela->desenhaTela();
			break;
		case CONF:
			break;
		case CREDITOS:
			controleTela->desenhaTela();
			break;
		case JOGO:
			controleTela->desenhaTela(345, 500);
			mapa->desenhaObstaculos(vParedes);
			pers->desenhaPersonagem();
			break;
		case RANK:
			escreveTexto(GLUT_BITMAP_HELVETICA_18, "Digite Seu Nome para RANK:", ESQUERDA_TELA + 20, 30, 0);
			escreveTexto(GLUT_BITMAP_HELVETICA_18, nomeJogador, ESQUERDA_TELA + 35, 0, 0);
			escreveTexto(GLUT_BITMAP_HELVETICA_18, "Aperte ENTER e Aguarde...!!!", CENTRO, FUNDO_TELA + 20, 0);
			break;
		case LISTA_RANK:
			escreveTexto(GLUT_BITMAP_HELVETICA_18, "RANK:", ESQUERDA_TELA + 20, 200, 0);
			string line;
			int conta = 0;
			int desloca = 35;
			ifstream myfile1 ("rank.txt");
			if (myfile1.is_open()){
				while ( getline (myfile1,line) || conta == 6){
					conta++;
					escreveTexto(GLUT_BITMAP_HELVETICA_18,line , ESQUERDA_TELA + desloca, 200 - (conta * 30), 0);
					line.clear();
					if(desloca == 35)
						desloca = 45;
					else
						desloca = 35;
				}
				myfile1.close();
  			}
			else cout<<"NAO DEU PRA ABRIR RANK"<<endl;
			break;


	}
	glutSwapBuffers();
}

//funcao que cria obstaculos de tempo em tempo
void criaObstaculo(int k){
	int randomX,randomLargura;
	if(controleTela->getTela() == JOGO){ // mudei disso !pause && inGame pra isso <<
		randomX = rand() % 50  + DIREITA_TELA;
		randomLargura = 10*(1 + rand() % 3);
		Obstaculo *o = new Obstaculo(randomX,CENTRO,randomLargura,ALTURA);
		vParedes.push_back(*o);
		glutTimerFunc(3000,criaObstaculo,0);
	}
}

//ajuste de tela
void ajustaTela(int NewWidth,int NewHeight){
	float RazaoAspecto = (float)NewWidth/NewHeight;
    glViewport(0, 0, NewWidth, NewHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(RazaoAspecto*ESQUERDA_TELA, RazaoAspecto*DIREITA_TELA, FUNDO_TELA, TOPO_TELA, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//teclas de suporte no jogo
void teclasJogo(unsigned char tecla,int x,int y){
	switch(controleTela->getTela()){
		case MENU:
			//TESTEEEEEE
			if(tecla == ESC)
				exit(0);

			if(tecla == 'j'){
				controleTela->setTela(JOGO);
				glutTimerFunc(500,criaObstaculo,1);
			}
			break;
		case GAME_OVER:
			if (tecla == 13)
			controleTela->setTela(MENU);
			init(); // reinicia (nao sei se ta certo, nao vi)
			break;
		case CREDITOS:
			if(tecla == ESC)
				controleTela->setTela(MENU);
			break;
		case JOGO:
			if(tecla == ESC)
				exit(0);
			if(tecla == 'p' || tecla  == 'P')
				controleTela->setTela(PAUSE);

			break;
		case PAUSE:
			if(tecla == 'p' || tecla  == 'P'){
				controleTela->setTela(JOGO);
				glutTimerFunc(500,criaObstaculo,1);
			}
			break;
		case RANK:
			if(tecla == ESC)
				exit(0);
			if(tecla == BACKSPACE && nomeJogador.size() > 0)
				nomeJogador.erase(nomeJogador.size()-1);
			else if(tecla == ENTER){
				montaRank();
				controleTela->setTela(LISTA_RANK);
			}
			else
				nomeJogador+=tecla;
			break;
		case LISTA_RANK:
			if(tecla == ESC)
				exit(0);

			if(tecla == 'r' || tecla == 'R'){
				rankJogadores.clear();
				controleTela->setTela(MENU);
			}
			break;
		 default:
			if(tecla == ESC)
				exit(0);
			break;

	}
}

void teclasJogoEsp(int tecla, int x, int y){
	switch (tecla) {
		case GLUT_KEY_UP:
			pers->incPontoY(0.02);
			break;
		case GLUT_KEY_DOWN:
			pers->mudaSituacao(baixo);
			break;
		default:
			break;
	}
}

void teclasJogoEspOcioso(int tecla, int x, int y){
	switch (tecla) {
		case GLUT_KEY_UP:
			pers->mudaSituacao(normal);
			break;
		case GLUT_KEY_DOWN:
			pers->mudaSituacao(normal);
			break;
		default:
			break;
	}
}

void mouseControlCliqueMenu (int button, int state, int x, int y){
    // Botões clicáveis no menu =o
    if (controleTela->getTela() == MENU && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if (controleTela->getPosicaoTexturaMenu() == 0.0){
            controleTela->setTela(JOGO);
			glutTimerFunc(500,criaObstaculo,1);

		}
        else if (controleTela->getPosicaoTexturaMenu() == 0.25)
			controleTela->setTela(CONF);
        else if (controleTela->getPosicaoTexturaMenu() == 0.50)
			controleTela->setTela(CREDITOS);
        else if (controleTela->getPosicaoTexturaMenu() == 0.75)
            exit(0);
    }
}


void mouseControl (int x, int y){
    // Recebe tamanho de tela
    float tamW = (float) glutGet(GLUT_WINDOW_WIDTH);
    float tamH = (float) glutGet(GLUT_WINDOW_HEIGHT);
    int mouseX = x;
    int mouseY = y;

    // Calcula valor percentual na tela na posição do mouse
    float mousePorcentagemX = 100 * mouseX / tamW;
    float mousePorcentagemY = 100 * mouseY / tamH;

	// Menu com mouse (valores atribuidos de acordo com limites dos botões)
	  if (mousePorcentagemX > 45 && mousePorcentagemX < 65 && mousePorcentagemY > 45 && mousePorcentagemY < 53)
	  	controleTela->setPosicaoTexturaMenu(0.0);
	  if (mousePorcentagemX > 45 && mousePorcentagemX < 65 && mousePorcentagemY > 59 && mousePorcentagemY < 67)
	      controleTela->setPosicaoTexturaMenu(0.25);
	  if (mousePorcentagemX > 45 && mousePorcentagemX < 65 && mousePorcentagemY > 74 && mousePorcentagemY < 81)
	      controleTela->setPosicaoTexturaMenu(0.50);
	  if (mousePorcentagemX > 45 && mousePorcentagemX < 65 && mousePorcentagemY > 86 && mousePorcentagemY < 93)
	      controleTela->setPosicaoTexturaMenu(0.75);

}

int main(int argc, char **argv){
	//INIT
	srand(time(0));

	glutInit(&argc,argv);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	//usando buffer duplo
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//tamanho da tela
	glutInitWindowSize(700,700);
	glutCreateWindow("MissaoDecom");
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	init();
	//callbacks
	glutDisplayFunc(desenhaTela);
	glutReshapeFunc(ajustaTela);
	glutKeyboardFunc(teclasJogo);
	glutSpecialFunc(teclasJogoEsp);
	glutSpecialUpFunc(teclasJogoEspOcioso);

	glutMouseFunc(mouseControlCliqueMenu);
	glutPassiveMotionFunc(mouseControl);

	glutTimerFunc(1000/DESIRED_FPS, update, 0);
	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR); // Muda desenhinho do mouse
	glutMainLoop();

	return 0;
}
