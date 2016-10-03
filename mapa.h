class Obstaculo{
	private:
		ponto pontoObstaculo;
		int altura,largura;
	public:
		Obstaculo(float x,float y,float largura,float altura);
		void desenhaObstaculo();
};

class Mapa{
	private:
		std::vector<Obstaculo> vParedes;
	public:
		//Mapa(std::string textura);
		Mapa();
		void desenhaObstaculos(bool desenha, std::vector<Obstaculo> v);
};