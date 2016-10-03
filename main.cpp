#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <bits/stdc++.h>
#include "estruturasPrincipais.h"
#include "mapa.h"
#include "personagem.h"
using namespace std;

int tempo = 0;
//Mapa
Mapa *mapa = new Mapa();

// personagem
Movimento *pers = new Movimento();

//Obstaculos
vector<Obstaculo> vParedes;

//func de desenha na tela
void desenhaTela(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1,1,1,1);
	mapa->desenhaObstaculos(vParedes);
	pers->desenhaPersonagem();
	glutSwapBuffers();
}

//ajuste de tela
void ajustaTela(int NewWidth,int NewHeight){
	float RazaoAspecto = (float)NewWidth/NewHeight;

    glViewport(0, 0, NewWidth, NewHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(RazaoAspecto*ESQUERDA_TELA, RazaoAspecto*DIREITA_TELA, FUNDO_TELA, TOPO_TELA, -3.0, 3.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//teclas de suporte no jogo
void teclasJogo(unsigned char tecla,int x,int y){
	if(tecla == ESC){
		exit(0);
	}
}

void teclasJogoEsp(int tecla, int x, int y){
	switch (tecla) {
		case GLUT_KEY_UP:
			pers->incPontoY(0.01);
			pers->mudaSituacao(cima);
			break;
		case GLUT_KEY_DOWN:
			pers->mudaSituacao(baixo);
			break;
		default:
			break;
	}

	cout << pers->getSituacao() << endl;
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

	cout << pers->getSituacao() << endl;
}

void update(int k){
	tempo++;

	vParedes = mapa->move(vParedes);
	glutPostRedisplay();
	glutTimerFunc(0, update, 0);
}

void criaObstaculo(int k){
	int randomX,randomLargura;
	randomX = rand() % 50  + DIREITA_TELA;
	randomLargura = 10*(1 + rand() % 3);
	Obstaculo *o = new Obstaculo(randomX,CENTRO,randomLargura,ALTURA);
	vParedes.push_back(*o);
	glutTimerFunc(10000,criaObstaculo,0);
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
	glutCreateWindow("PacDecom");
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	//callbacks
	glutDisplayFunc(desenhaTela);
	glutReshapeFunc(ajustaTela);
	glutKeyboardFunc(teclasJogo);
	glutSpecialFunc(teclasJogoEsp);
	glutSpecialUpFunc(teclasJogoEspOcioso);

	glutTimerFunc(0, update, 0);
	glutTimerFunc(500,criaObstaculo,1);
	glutMainLoop();
	return 0;
}
