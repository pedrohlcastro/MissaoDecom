class Tela{
	public:
		int telaAtual;
		GLint texturas[QTD_TELAS];
	public:
		Tela(std::vector<std::string>endTexturas);
		void desenhaTela();
		void desenhaTelaSprite(int x,int y);
		void setTela(int novaTela);
		int getTela();
};