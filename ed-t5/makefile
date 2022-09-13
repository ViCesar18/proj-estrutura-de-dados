CC = gcc
COMPILER_FLAGS = -std=c99
LINKER_FLAGS = -lm
EXEC_NAME = siguel
OBJECTS = main.o inGEO.o inQRY.o outSVG.o geometry/forms.o queryForms.o queryBuildings.o queryFire.o queryResident.o queryStore.o queryUtils.o queryPolygon.o queryVia.o utils/operations.o data_structures/rbtree.o data_structures/hash_table.o data_structures/graph.o data_structures/priority_queue.o city_elements/block.o city_elements/hydrant.o city_elements/radio_tower.o city_elements/traffic_light.o city_elements/building.o city_elements/wall.o sort/heapsort.o geometry/polygon.o geometry/segment.o geometry/point.o geometry/vertex.o utils/bomb.o utils/interactive.o city_elements/store.o city_elements/person.o city_elements/resident.o city_elements/storeType.o

siguel: $(OBJECTS)
		$(CC) $(OBJECTS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

clean:
		rm -rf ./*.o
		rm -rf city_elements/*.o
		rm -rf data_structures/*.o
		rm -rf geometry/*.o
		rm -rf utils/*.o
		rm -rf sort/*.o
		rm siguel
