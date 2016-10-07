#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <SFML/Network.hpp>
#include <bits/stdc++.h>
#include "estruturasPrincipais.h"
#include "mapa.h"
#include "personagem.h"
#include "tela.h"
using namespace std;

int tempo = 0;
bool pause = false;
bool inGame = false; //caso esteja jogando

string nomeJogador;
//Mapa
Mapa *mapa = new Mapa();

// personagem
Movimento *pers = new Movimento();

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
bool gravado = false;//gravado arquivo rank

void update(int k){
	tempo++;
	//temporário
	if(pers->verificaColisao(vParedes)){
		inGame = false;
		gravado = false;
		vParedes.clear();
		controleTela->setTela(RANK);
	}
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
	enderecoTexturas.push_back("img/print2.png");
	controleTela = new Tela(enderecoTexturas);
	printf("SERVER:\n");
	conectServer();
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
			controleTela->desenhaTela();
			break;
		case JOGO:
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
	if(!pause && inGame){
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
	if(tecla == ESC){
		exit(0);
	}
	switch(controleTela->getTela()){
		case MENU:
			//TESTEEEEEE
			if(tecla == 'j'){
				controleTela->setTela(JOGO);
				inGame = true;
				glutTimerFunc(500,criaObstaculo,1);
			}
			break;
		case JOGO:
			if(tecla == 'p' || tecla  == 'P'){
				pause = true;
				controleTela->setTela(PAUSE);
			}
			break;
		case PAUSE:
			if(tecla == 'p' || tecla  == 'P'){
				pause = false;
				controleTela->setTela(JOGO);
				glutTimerFunc(500,criaObstaculo,1);
			}
			break;
		case RANK:
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
			if(tecla == 'r' || tecla == 'R'){
				rankJogadores.clear();
				controleTela->setTela(MENU);
			}
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
	glutTimerFunc(1000/DESIRED_FPS, update, 0);
	glutMainLoop();
	return 0;
}
