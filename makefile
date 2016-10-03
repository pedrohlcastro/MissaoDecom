CC = g++
OPCOES_COMPILADOR= -lglut -lGLU -lGLEW -lSOIL -lsfml-audio -lGL
TODOS_ARQUIVOS_PONTOH = estruturasPrincipais.h personagem.h
TODOS_ARQUIVOS_OBJ = main.o personagem.o

%.o: ../%.cpp $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	$(CC) -o main $^ $(OPCOES_COMPILADOR)

run: all
	./main
	# Jogue com carinho!
	# GG EZ kappa CYKA

install:
	sudo apt-get install build-essential
	sudo apt-get install freeglut3-dev
	sudo apt-get install libglew1.6-dev
	sudo apt-get install libsoil-dev
	sudo apt-get install libsfml-dev
	# Bibliotecas intaladas!

clean:
	rm *.o main
