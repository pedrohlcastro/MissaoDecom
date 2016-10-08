#define TIPO_OBJ 5
class Obstaculo{
	public:
		ponto pontoObstaculo;
		int altura,largura;
		int img;
	public:
		Obstaculo(float x,float y,float largura,float altura,int img);
		void desenhaObstaculo();
		ponto getCoord();
		float getLargura();
		float getAltura();
};

class Mapa{
	private:
		int pontuacao;
		int vetorImagens[5];
		int tempoCriacao;
	public:
		Mapa();
		int getPontuacao();
		void desenhaObstaculos(std::vector<Obstaculo>vParedes);
		void zeraPontuacao();
		std::vector<Obstaculo> move (std::vector<Obstaculo> vParedes);
		int * getImagens();
		void aumentaTempoCriacao(int aumento,bool reset);
		int getTempoCriacao();
};
