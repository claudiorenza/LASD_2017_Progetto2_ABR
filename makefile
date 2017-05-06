# the compiler to use
CC      = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CCFLAGS = -g -Wall
RM      = rm -rf

SRC_IO = io/random.c \
	io/io.c

SRC_T = tree/treeABR.c \
	tree/treeABR_func.c

SRC = $(SRC_IO) $(SRC_T)


OBJ_IO = $(SRC_IO:.c=.o)

OBJ_T = $(SRC_T:.c=.o)

OBJ = $(SRC:.c=.o)

default: all

all: $(OBJ)
	$(CC) $(CCFLAGS) $(SRC) -o treeLib main.c
	@echo "Build complete"

clean:
	$(RM) *.dSYM tree/*.o io/*.o *.o treeLib
	@echo "Clean complete"