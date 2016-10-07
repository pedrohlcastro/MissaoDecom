#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <bits/stdc++.h>
#include "estruturasPrincipais.h"
#include "mapa.h"
using namespace std;

//construtor da classe Obstaculo
Obstaculo::Obstaculo(float x,float y,float largura,float altura,int img){
	this->pontoObstaculo.x = x;
	this->pontoObstaculo.y = y;
	this->largura = largura;
	this->altura = altura;
	this->img = img;
}


//desenha paredes
void Obstaculo::desenhaObstaculo(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->img);
	glPushMatrix();
		glTranslatef(this->pontoObstaculo.x ,this->pontoObstaculo.y ,0);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); 			glVertex2f(0,0);
			glTexCoord2f(1, 0);				glVertex2f(this->largura,0);
			glTexCoord2f(1, 1); 			glVertex2f(this->largura,this->altura);
			glTexCoord2f(0, 1);				glVertex2f(0,this->altura);
		glEnd();
		glDisable(GL_TEXTURE_2D);
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

int * Mapa::getImagens(){
	return this->vetorImagens;
}

std::vector<Obstaculo> Mapa::move (std::vector<Obstaculo> vParedes){
	for(int i=0; i < vParedes.size(); i++){
		vParedes[i].pontoObstaculo.x -= 10*PASSO_DO_PERSONAGEM;
		if(vParedes[i].pontoObstaculo.x < ESQUERDA_TELA - 5){//5 de erro
			vParedes.erase(vParedes.begin()+i);
			this->pontuacao += 20;
		}
	}
	return vParedes;
}

Mapa::Mapa(){
	this->pontuacao = 0;
	this->vetorImagens[0] =  SOIL_load_OGL_texture(
	    "img/python.png",
		SOIL_LOAD_AUTO,
    	SOIL_CREATE_NEW_ID,
    	SOIL_FLAG_INVERT_Y
		);
	if (vetorImagens[0] == 0 ) {
		printf("Erro carregando textura: '%s'\n", SOIL_last_result());
	}
	this->vetorImagens[1] =  SOIL_load_OGL_texture(
	    "img/ruby.png",
		SOIL_LOAD_AUTO,
    	SOIL_CREATE_NEW_ID,
    	SOIL_FLAG_INVERT_Y
		);
	if (vetorImagens[1] == 0 ) {
		printf("Erro carregando textura: '%s'\n", SOIL_last_result());
	}
	this->vetorImagens[2] =  SOIL_load_OGL_texture(
	    "img/Java.png",
		SOIL_LOAD_AUTO,
    	SOIL_CREATE_NEW_ID,
    	SOIL_FLAG_INVERT_Y
		);
	if (vetorImagens[2] == 0 ) {
		printf("Erro carregando textura: '%s'\n", SOIL_last_result());
	}
	this->vetorImagens[3] =  SOIL_load_OGL_texture(
	    "img/android.png",
		SOIL_LOAD_AUTO,
    	SOIL_CREATE_NEW_ID,
    	SOIL_FLAG_INVERT_Y
		);
	if (vetorImagens[3] == 0 ) {
		printf("Erro carregando textura: '%s'\n", SOIL_last_result());
	}
	this->vetorImagens[4] =  SOIL_load_OGL_texture(
	    "img/apple.png",
		SOIL_LOAD_AUTO,
    	SOIL_CREATE_NEW_ID,
    	SOIL_FLAG_INVERT_Y
		);
	if (vetorImagens[4] == 0 ) {
		printf("Erro carregando textura: '%s'\n", SOIL_last_result());
	}
}

int Mapa::getPontuacao(){
	return this->pontuacao;
}

void Mapa::desenhaObstaculos(std::vector<Obstaculo> vParedes){
	for(int i=0; i < vParedes.size(); i++){
		vParedes[i].desenhaObstaculo();
	}
}

void Mapa::zeraPontuacao(){
	this->pontuacao = 0;
}
