class Obstaculo{
	public:
		ponto pontoObstaculo;
		int altura,largura;
	public:
		Obstaculo(float x,float y,float largura,float altura);
		void desenhaObstaculo();
		ponto getCoord();
		float getLargura();
		float getAltura();
};

class Mapa{
	private:
		int pontuacao;
	public:
		//Mapa(std::string textura);
		Mapa();
		int getPontuacao();
		void desenhaObstaculos(std::vector<Obstaculo>vParedes);
		void zeraPontuacao();
		std::vector<Obstaculo> move (std::vector<Obstaculo> vParedes);
};
