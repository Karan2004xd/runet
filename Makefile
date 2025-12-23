CC = gcc

CFLAGS = -Wall -Wextra -O2 -Iinclude -fno-omit-frame-pointer -g -O0

PICFLAGS = -fPIC
LDFLAGS = -lm

LDFLAGS_SO =

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LDFLAGS_SO = -dynamiclib
	CFLAGS += -arch arm64
else
	LDFLAGS_SO = -shared
endif

SRC = $(filter-out src/main.c, $(wildcard src/*.c))
OBJ = $(SRC:.c=.o)
MAIN_OBJ = src/main.o

TEST_SRC = $(filter-out tests/test_main.c, $(wildcard tests/*.c))
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_MAIN_OBJ = tests/test_main.o

runet: $(OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

librunet.so: $(OBJ)
	@mkdir -p libs
	$(CC) $(LDFLAGS_SO) -o libs/$@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

test: $(TEST_OBJ) $(TEST_MAIN_OBJ) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

clean:
	rm -f src/*.o runet tests/*.o test libs/*.so

.PHONY: clean
