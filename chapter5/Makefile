OBJECTS=  ./build/vector.o ./build/lexer.o 
# ./build/parser.o ./build/ast.o
INCLUDES= -I./

all: ${OBJECTS}
	gcc main.c ${INCLUDES} ${OBJECTS} -g -o ./main 


./build/lexer.o: ./lexer.c
	gcc lexer.c ${INCLUDES} -o ./build/lexer.o -g -c

./build/vector.o: ./vector.c
	gcc vector.c ${INCLUDES} -o ./build/vector.o -g -c

# ./build/parser.o: ./parser.c
# 	gcc parser.c ${INCLUDES} -o ./build/parser.o -g -c
#
# ./build/ast.o: ./ast.c
# 	gcc ast.c ${INCLUDES} -o ./build/ast.o -g 
clean:
	rm ./main
	rm -rf ${OBJECTS}
