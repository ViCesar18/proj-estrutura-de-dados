CC = gcc
COMPILER_FLAGS = -std=c99
LINKER_FLAGS = -lm
EXEC_NAME = siguel
OBJECTS = main.o inSVG.o outSVG.o objects/forms.o queryForms.o queryBuildings.o operations.o data_structures/rbtree.o data_structures/hash_table.o objects/block.o objects/hydrant.o objects/radio_tower.o objects/traffic_light.o objects/building.o objects/wall.o heapsort.o segment.o point.o vertex.o bomb.o
#OBJECTS = main.o inSVG.o outSVG.o Objetos/forms.o queryForms.o queryBuildings.o queryResident.o queryStore.o operations.o list.o interactive.o Objetos/block.o Objetos/hydrant.o Objetos/radio_tower.o Objetos/traffic_light.o Objetos/building.o Objetos/wall.o Objetos/store.o Objetos/person.o Objetos/resident.o heapsort.o segment.o bomb.o point.o vertex.o

siguel: $(OBJECTS)
		$(CC) $(OBJECTS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

clean:
		rm -rf ./*.o
		rm -rf objects/*.o
		rm -rf data_structures/*.o
		rm siguel
