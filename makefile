# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Isrc/scanner  # Include directories

# Automatically find all .c files in src/ and subdirectories
SRC = $(wildcard src/**/*.c src/*.c)
OBJ = $(SRC:.c=.o)  # Replace .c with .o for object files

# Output binary
OUT = mpy

# Build target
$(OUT): $(OBJ)
	$(CC) -o $(OUT) $(OBJ)

# Compile each .c file into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(OUT)