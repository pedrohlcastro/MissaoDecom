#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <bits/stdc++.h>
#include "estruturasPrincipais.h"
#include "mapa.h"
#include "personagem.h"
using namespace std;

// personagem
Movimento *pers = new Movimento();

//func de desenha na tela
void desenhaTela(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1,1,1,1);

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
			break;
		case GLUT_KEY_DOWN:
			break;
		default:
			break;
	}

}

void update(int k){
	pers->move();
	glutPostRedisplay();
	glutTimerFunc(0, update, 0);
}

int main(int argc, char **argv){
	//INIT
	glutInit(&argc,argv);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	//usando buffer duplo
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//tamanho da tela
	glutInitWindowSize(700,300);
	glutCreateWindow("PacDecom");
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	//callbacks
	glutDisplayFunc(desenhaTela);
	glutReshapeFunc(ajustaTela);
	glutKeyboardFunc(teclasJogo);
	glutSpecialFunc(teclasJogoEsp);
	glutTimerFunc(0, update, 0);
	glutMainLoop();
	return 0;
}
