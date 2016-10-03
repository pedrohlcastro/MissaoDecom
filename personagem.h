class Movimento{
	private:
		ponto pontos;
		float comprimento;
	public:
        Movimento();
        ponto getCoord();
        void move();
        void desenhaPersonagem();
};
