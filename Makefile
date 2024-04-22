OBJECTS=  ./build/vector.o ./build/lexer.o 
INCLUDES= -I./

all: ${OBJECTS}
	gcc main.c ${INCLUDES} ${OBJECTS} -g -o ./main 


./build/lexer.o: ./lexer.c
	gcc lexer.c ${INCLUDES} -o ./build/lexer.o -g -c

./build/vector.o: ./vector.c
	gcc vector.c ${INCLUDES} -o ./build/vector.o -g -c

clean:
	rm ./main
	rm -rf ${OBJECTS}
