TARGET = bin/dbview
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default
	./$(TARGET) -f ./mynewdb.db -n
	./$(TARGET) -f ./mynewdb.db -a "Timmy H.,123 Sheshire Ln.,120"

default: $(TARGET)

clean:
	rm -f obj/*.o
	rm -f bin/*
	rm -f *.db

$(TARGET): $(OBJ)
	gcc -Wall -o $@ $?

obj/%.o : src/%.c
	gcc -Wall -c $< -o $@ -Iinclude -g

test: obj/parse.o
	gcc -Wall -c test/test.c -o test/test.o -Iinclude -g
	gcc -Wall -o bin/test -ggdb -g obj/parse.o test/test.o -Iinclude
	bin/test
