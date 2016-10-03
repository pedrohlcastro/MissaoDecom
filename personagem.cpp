#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <bits/stdc++.h>
#include "estruturasPrincipais.h"
#include "personagem.h"
using namespace std;

//construtor da classe movimento
Movimento::Movimento(){
	this->pontos.x = 0;
	this->pontos.y = 0;
	this->comprimento = 20;
}

ponto Movimento::getCoord(){
	return this->pontos;
}

void Movimento::desenhaPersonagem(){
	glPushMatrix();
		glTranslatef(this->pontos.x, this->pontos.y, 1);
		//printf("%f %f\n",this->pontoParede.x, this->pontoParede.y );
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(this->comprimento,0);
			glVertex2f(this->comprimento,this->comprimento);
			glVertex2f(0,this->comprimento);
		glEnd();
	glPopMatrix();
}

