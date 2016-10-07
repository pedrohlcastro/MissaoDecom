class Tela{
	public:
		int telaAtual;
		float posicaoTexturaMenu;
		GLint texturas[QTD_TELAS];
	public:
		Tela(std::vector<std::string>endTexturas);
		void desenhaTela();
		void desenhaTela(float limInferiorY, float limSuperiorY);
		void desenhaTelaSprite(float x,float y);
		void setTela(int novaTela);
		int getTela();
		float getPosicaoTexturaMenu();
		void setPosicaoTexturaMenu(float pos);
};
