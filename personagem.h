class Movimento{
	private:
		ponto pontos;
		Sentido situacao;
		float comprimento;
		int gravidadePulo;
		int alturaPulo;
		int textura;

		float grauVariacao;
		float variacaoSprite;
	public:
        Movimento();
        Movimento(std::string textura);
        ponto getCoord();
		Sentido getSituacao();
		void incPontoY(float inc);
        void desenhaPersonagem();
		void pula();
		void mudaSituacao(Sentido situacao);
		bool verificaColisao(std::vector<Obstaculo> vParedes);
};
