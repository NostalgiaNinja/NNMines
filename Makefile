#OBJS specifies which files to compile as part of the project
OBJS = Main.cpp LoadTex.cpp LoadTimer.cpp Game.cpp Options.cpp

#CC specifies the compiler
# -w ignores warnings
CC = g++

COMPILER-FLAGS = -w

LINKER-FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = NNMines

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER-FLAGS) $(LINKER-FLAGS) -o $(OBJ_NAME)
