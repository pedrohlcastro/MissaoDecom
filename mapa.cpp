#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <bits/stdc++.h>
#include "estruturasPrincipais.h"
#include "mapa.h"
using namespace std;

//construtor da classe Obstaculo
Obstaculo::Obstaculo(float x,float y,float largura,float altura){
	this->pontoObstaculo.x = x;
	this->pontoObstaculo.y = y;
	this->largura = largura;
	this->altura = altura;
}

//desenha paredes
void Obstaculo::desenhaObstaculo(){
	glPushMatrix();
		glTranslatef(this->pontoObstaculo.x ,this->pontoObstaculo.y,0);
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(this->largura,0);
  			glVertex2f(this->largura,this->altura);
  			glVertex2f(0,this->altura);
		glEnd();
	glPopMatrix();
}

ponto Obstaculo::getCoord(){
	return this->pontoObstaculo;
}
float Obstaculo::getLargura(){
	return this->largura;
}
float Obstaculo::getAltura(){
	return this->altura;
}

void desenhaObstaculo(bool desenha, std::vector<Obstaculo> v){
	this->vParedes = v;
	for(int i=0; i<this->vParedes.size(); i++){
		this->vParedes[i]->desenhaObstaculo;
	}
}