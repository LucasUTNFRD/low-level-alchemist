
OBJECTS=  ./build/linked_list.o ./build/tests.o
INCLUDES= -I./

all: ${OBJECTS}
	gcc main.c ${INCLUDES} ${OBJECTS} -g -o ./main 


./build/linked_list.o: ./linked_list.c
	gcc linked_list.c ${INCLUDES} -o ./build/linked_list.o -g -c

./build/tests.o: ./tests.c
	gcc tests.c ${INCLUDES} -o ./build/tests.o -g -c

clean:
	rm ./main
	rm -rf ${OBJECTS}
