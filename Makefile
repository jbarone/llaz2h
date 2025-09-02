TARGET = bin/dbview
SRC = $(wildcard src/*.c)
SRCT = $(wildcard test/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
TST = $(pathsubst test/%.c, %, $(SRCT))

default: $(TARGET)

run: clean default
	./$(TARGET) -f ./mynewdb.db -n
	./$(TARGET) -f ./mynewdb.db -a "Timmy H.,123 Sheshire Ln.,120"

clean:
	rm -f obj/*.o
	rm -rf bin/*
	rm -f *.db

$(TARGET): $(OBJ)
	gcc -Wall -o $@ $?

obj/%.o : src/%.c
	gcc -Wall -c $< -o $@ -Iinclude -g

obj/%.o : test/%.c
	gcc -Wall -c $< -o $@ -Iinclude -g

test: $(filter-out obj/main.o,$(OBJ))
	@echo "Running tests..."
	@for testfile in $(SRCT); do \
		gcc -Wall -o bin/`basename $$testfile .c` $$testfile $(filter-out obj/main.o,$(OBJ)) -Iinclude -g -lunity; \
		./bin/`basename $$testfile .c`; \
	done
	@echo "All tests completed."
