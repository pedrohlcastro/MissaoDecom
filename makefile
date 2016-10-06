CC = g++
OPCOES_COMPILADOR= -lSOIL -lGL -lglut -lGLEW -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network 
TODOS_ARQUIVOS_PONTOH = estruturasPrincipais.h mapa.h personagem.h tela.h
TODOS_ARQUIVOS_OBJ = main.o mapa.o personagem.o tela.o

%.o: ../%.cpp $(TODOS_ARQUIVOS_PONTOH)
	$(CC) $(OPCOES_COMPILADOR) -o  $@ -c $<

all: $(TODOS_ARQUIVOS_OBJ)
	$(CC) -o main $^ $(OPCOES_COMPILADOR)

run: all
	./main
	# Jogue com carinho!

install:
	sudo apt-get install build-essential
	sudo apt-get install freeglut3-dev
	sudo apt-get install libglew1.6-dev
	sudo apt-get install libsoil-dev
	sudo apt-get install libsfml-dev
	# Bibliotecas intaladas!

clean:
	rm *.o main
