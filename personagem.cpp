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
	this->pontos.y = CENTRO;
	this->largura = 30;
	this->altura = 50;
	this->gravidadePulo = .5;
	this->alturaPulo = 120;
	this->situacao = normal;
	this->variacaoSprite = 0;
	this->grauVariacao = 0.1;
}
Movimento::Movimento(std::string textura){
	this->pontos.x = -100;
	this->pontos.y = CENTRO;
	this->largura = 30;
	this->altura = 50;
	this->gravidadePulo = .5;
	this->alturaPulo = 120;
	this->situacao = normal;
	this->variacaoSprite = 0;
	this->grauVariacao = 0.1;

	this->textura = SOIL_load_OGL_texture(
	    textura.c_str(),
		SOIL_LOAD_AUTO,
    	SOIL_CREATE_NEW_ID,
    	SOIL_FLAG_INVERT_Y
	);
	if (this->textura == 0) {
		printf("Erro carregando textura: '%s'\n", SOIL_last_result());
	}
}

void Movimento::incPontoY(float inc){
	this->pontos.y += inc;
}

void Movimento::pula(){
	//cout << "x " << this->pontos.x << "y " << this->pontos.y << endl;
	if (this->pontos.y > CENTRO && this->pontos.y <= this->alturaPulo){
		this->pontos.y += 14 - this->gravidadePulo;
		this->gravidadePulo += 1;
	}
	if (this->pontos.y <= CENTRO){
		this->gravidadePulo = 0;
		this->pontos.y = CENTRO;

	}
	if (this->pontos.y > this->alturaPulo){ // CASO ELE CHEGUE NO LIM ESTABELECIDO, CAI.
		this->pontos.y -= .5;
		this->situacao = normal;
	}
}

bool Movimento::verificaColisao(vector<Obstaculo> vParedes){
	for (int i = 0; i < vParedes.size(); i++){
		// colisao por cima
		float xParede = vParedes[i].getCoord().x;
		float yParede = vParedes[i].getCoord().y;
		if (this->pontos.y + this->largura + PASSO_DO_PERSONAGEM > yParede && this->pontos.y + PASSO_DO_PERSONAGEM < yParede + vParedes[i].getAltura()){
			if (!(this->pontos.x + this->largura <= xParede || this->pontos.x >= xParede + vParedes[i].getLargura()))
				return true;
		}

		// colisao pelo lado esquerdo
		if (this->pontos.x - PASSO_DO_PERSONAGEM > xParede && this->pontos.x - PASSO_DO_PERSONAGEM < xParede + vParedes[i].getLargura()){
			if (!(this->pontos.y + this->largura <= yParede || this->pontos.y >= yParede + vParedes[i].getAltura()))
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
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->textura);
	glTranslatef(this->pontos.x, this->pontos.y, 1);
    glBegin(GL_POLYGON);

		glTexCoord2f(this->variacaoSprite, 0);						glVertex3f(0, 0, 0);
        glTexCoord2f(this->variacaoSprite+this->grauVariacao, 0); 	glVertex3f(this->largura, 0, 0);
        glTexCoord2f(this->variacaoSprite+this->grauVariacao, 1); 	glVertex3f(this->largura, this->altura, 0);
        glTexCoord2f(this->variacaoSprite, 1);						glVertex3f(0, this->altura, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glPopMatrix();

	this->variacaoSprite += 0.1;
	if (this->variacaoSprite > 1)
		this->variacaoSprite = 0;
}
