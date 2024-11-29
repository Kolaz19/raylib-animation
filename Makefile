OS = lin
DEBUG_FLAG = -g

ifeq ($(MAKECMDGOALS), lib)
DEBUG_FLAG =
endif

ifeq ($(OS), lin)
CC = gcc
LIB_NAME = libanim.a
else
CC = x86_64-w64-mingw32-gcc
LIB_NAME = libanimwin.a
endif

OBJ_DIR = ./object_files/

C_FLAGS = -Wall -Wextra -Wconversion -std=c99 -fdiagnostics-color=always -pedantic

LIB_DIR = -L ./lib

LINKERS = $(LIB_DIR) -lraylib /usr/lib/x86_64-linux-gnu/libGL.so -lm -lpthread -ldl -lrt

C_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)%.o, $(C_FILES))

build: main

main: $(OBJ_FILES)
	$(CC) $(DEBUG_FLAG) $(C_FLAGS) -o main $(OBJ_DIR)*.o $(LINKERS)

$(OBJ_FILES): $(OBJ_DIR)%.o: %.c
	$(CC) -c $(DEBUG_FLAG) $< -o $@

lib: prelib
	ar -rc $(LIB_NAME) $(OBJ_DIR)animation.o

prelib: animation.c 
	$(CC) -c animation.c -o $(OBJ_DIR)animation.o

clean: 
	rm -f $(OBJ_DIR)*.o main *.a

run: 
	./main
