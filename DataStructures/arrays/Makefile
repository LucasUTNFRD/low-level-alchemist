OBJECTS=  ./build/main.o ./build/array.o
INCLUDES= -I./

all: ${OBJECTS}
			gcc ${INCLUDES} ${OBJECTS} -g -o ./main

./build/main.o: ./main.c
			gcc main.c ${INCLUDES} -o ./build/main.o -g -c

./build/array.o: ./array.c
			gcc array.c ${INCLUDES} -o ./build/array.o -g -c

clean:
				rm ./main
				rm -rf ${OBJECTS}

