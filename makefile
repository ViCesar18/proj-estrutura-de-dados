CC = gcc
COMPILER_FLAGS = -std=c99
LINKER_FLAGS = -lm
EXEC_NAME = siguel
OBJECTS = main.o inSVG.o outSVG.o Objetos/forms.o consulta.o lista.o Objetos/block.o Objetos/hydrant.o Objetos/radio.o Objetos/semaphore.o consultasLista.o

siguel: $(OBJECTS)
		$(CC) $(OBJECTS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

clean:
		rm -rf ./*.o
		rm -rf Objetos/*.o