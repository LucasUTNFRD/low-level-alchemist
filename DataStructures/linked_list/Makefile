
OBJECTS=  ./build/linked_list.o 
INCLUDES= -I./

all: ${OBJECTS}
	gcc main.c ${INCLUDES} ${OBJECTS} -g -o ./main 


./build/linked_list.o: ./linked_list.c
	gcc linked_list.c ${INCLUDES} -o ./build/linked_list.o -g -c

clean:
	rm ./main
	rm -rf ${OBJECTS}
