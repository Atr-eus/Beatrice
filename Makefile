CC := gcc
CFLAGS := -c -Wall -std=c2x -Iinclude
LDFLAGS :=
SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=obj/%.o)
TARGET := beatrice

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf obj $(TARGET)
