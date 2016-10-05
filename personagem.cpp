#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <bits/stdc++.h>
#include "estruturasPrincipais.h"
#include "mapa.h"
#include "personagem.h"

using namespace std;

//construtor da classe movimento
Movimento::Movimento(){
	this->pontos.x = -100;
	this->pontos.y = 0;
	this->comprimento = 20;
	this->gravidadePulo = 1.5;
	this->alturaPulo = 80;
	this->situacao = normal;
}

void Movimento::incPontoY(float inc){
	this->pontos.y += inc;
}

void Movimento::pula(){
	cout << "x " << this->pontos.x << "y " << this->pontos.y << endl;
	if (this->pontos.y > 0 && this->pontos.y <= this->alturaPulo){
		this->pontos.y += 8 - this->gravidadePulo;
		this->gravidadePulo += 0.18;
	}
	if (this->pontos.y <= 0){
		this->gravidadePulo = 0;
		this->pontos.y = 0;

	}
	if (this->pontos.y > this->alturaPulo){ // CASO ELE CHEGUE NO LIM ESTABELECIDO, CAI.
		this->pontos.y -= 4;
	}

}

bool Movimento::verificaColisao(vector<Obstaculo> vParedes){
	for (int i = 0; i < vParedes.size(); i++){
		// colisao por cima
		if (this->pontos.y + this->comprimento + PASSO_DO_PERSONAGEM > vParedes[i].getCoord().y && this->pontos.y + PASSO_DO_PERSONAGEM < vParedes[i].getCoord().y + vParedes[i].getAltura()){
			if (!(this->pontos.x + this->comprimento <= vParedes[i].getCoord().x || this->pontos.x >= vParedes[i].getCoord().x + vParedes[i].getLargura()))
				return true;
		}

		// colisao pelo lado esquerdo
		if (this->pontos.x - PASSO_DO_PERSONAGEM > vParedes[i].getCoord().x && this->pontos.x - PASSO_DO_PERSONAGEM < vParedes[i].getCoord().x + vParedes[i].getLargura()){
			if (!(this->pontos.y + this->comprimento <= vParedes[i].getCoord().y || this->pontos.y >= vParedes[i].getCoord().y + vParedes[i].getAltura()))
				return true;
		}
	}

	return false;
}


Sentido Movimento::getSituacao (){
	return this->situacao;
}

void Movimento::mudaSituacao(Sentido situacao){
	this->situacao = situacao;
}

ponto Movimento::getCoord(){
	return this->pontos;
}

void Movimento::desenhaPersonagem(){

	Movimento::pula();

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
