#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <bits/stdc++.h>
#include "estruturasPrincipais.h"
#include "tela.h"
using namespace std;

//constutor para telas
Tela::Tela(char endTexturas[30][30], int tamanho){
// Tela::Tela(vector<string>endTexturas){
	//printf("NEM AQ\n");
	for(int i=0; i<tamanho; i++){
		this->texturas[i] = SOIL_load_OGL_texture(
		    "img/banan.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
 		);
 		if (this->texturas[i] == 0 ) {
    		printf("Erro carregando textura: '%s'\n", SOIL_last_result());
    		cout<<endTexturas[i]<<endl;
  		}
  		//printf("PLS\n");
	}
	//printf("MONTOU\n");
	this->telaAtual = MENU;
}

//desenha tela normal
void Tela::desenhaTela(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->texturas[this->telaAtual]);
	glPushMatrix();
		glTranslatef(-350 ,-350 ,0);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); 			glVertex2f(0,0);
			glTexCoord2f(1, 0);				glVertex2f(700,0);
			glTexCoord2f(1, 1); 			glVertex2f(700,700);
			glTexCoord2f(0, 1);				glVertex2f(0,700);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//desenha tela com sprite
void Tela::desenhaTelaSprite(int spriteBegin,int spriteEnd){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->texturas[this->telaAtual]);
	glPushMatrix();
		glTranslatef(-350 ,-350 ,0);
		glBegin(GL_POLYGON);
			glTexCoord2f(spriteBegin, 0); 			glVertex2f(0,0);
			glTexCoord2f(spriteEnd, 0);				glVertex2f(700,0);
			glTexCoord2f(spriteEnd, 1); 			glVertex2f(700,700);
			glTexCoord2f(spriteBegin, 1);			glVertex2f(0,700);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//set para mudar de tela
void Tela::setTela(int novaTela){
	this->telaAtual = novaTela;
}

//get para que retorna a tela atual
int Tela::getTela(){
	return this->telaAtual;
}
