OS = lin
DEBUG_FLAG = -g

LIB_DIR = -L ./lib
OBJ_DIR = ./object_files/

ifeq ($(OS), lin)
CC = gcc
LINKERS = $(LIB_DIR) -lraylib /usr/lib/x86_64-linux-gnu/libGL.so -lm -lpthread -ldl -lrt
else
CC = x86_64-w64-mingw32-gcc
LINKERS = $(LIB_DIR) -lraylibwin -lopengl32 -lgdi32 -lwinmm 
endif

C_FLAGS = -Wall -Wextra -Wconversion -std=c99 -fdiagnostics-color=always -pedantic

C_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)%.o, $(C_FILES))

build: main

main: $(OBJ_FILES)
	$(CC) $(DEBUG_FLAG) $(C_FLAGS) -o main $(OBJ_DIR)*.o $(LINKERS)

$(OBJ_FILES): $(OBJ_DIR)%.o: %.c
	$(CC) -c $(C_FLAGS) $(DEBUG_FLAG) $< -o $@

clean: 
	rm -f $(OBJ_DIR)*.o main main.exe

run: 
	./main
