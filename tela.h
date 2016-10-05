class Tela{
	public:
		int telaAtual;
		int texturas[QTD_TELAS];
	public:
		Tela(char enderecoTexturas[30][30],int tamanho);
		// Tela(std::vector<std::string>endTexturas);
		void desenhaTela();
		void desenhaTelaSprite(int x,int y);
		void setTela(int novaTela);
		int getTela();
};
