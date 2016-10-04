class Movimento{
	private:
		ponto pontos;
		Sentido situacao;
		float comprimento;
		int gravidadePulo;
		int alturaPulo;
	public:
        Movimento();
        ponto getCoord();
		Sentido getSituacao();
		void incPontoY(float inc);
        void desenhaPersonagem();
		void pula();
		void mudaSituacao(Sentido situacao);
		bool verificaColisao(std::vector<Obstaculo> vParedes);
};
