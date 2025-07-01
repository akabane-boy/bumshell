# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Source and object files
SRC = src/main.c src/input.c src/parser.c src/executor.c src/builtins.c
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = bumshell

# Default build target
all: $(TARGET)

# Linking object files
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile .c to .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f src/*.o $(TARGET)

# run the shell
run: $(TARGET)
	./$(TARGET)
