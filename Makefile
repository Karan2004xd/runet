CC = gcc

CFLAGS = -Wall -Wextra -O2 -Iinclude
PICFLAGS = -fPIC
LDFLAGS_SO = -shared

SRC = $(filter-out src/main.c, $(wildcard src/*.c))
OBJ = $(SRC:.c=.o)
	MAIN_OBJ = src/main.o

TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_MAIN_OBJ = tests/test_main.o

runet: $(OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

librunet.so: $(OBJ)
	$(CC) $(LDFLAGS_SO) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

test: $(TEST_OBJ) $(TEST_MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

clean:
	rm -f src/*.o runet librunet.so tests/*.o test

.PHONY: clean
