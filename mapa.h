class Obstaculo{
	private:
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
	public:
		//Mapa(std::string textura);
		Mapa();
		void desenhaObstaculos(bool desenha, std::vector<Obstaculo>vParedes);
};