CC = gcc
FLAGS = -Wall -Wextra -Wswitch-enum -lm -lraylib
BUILD_PATH = build
SOURCES = $(wildcard src/*.c src/*/*.c)
PROG = maze_solver

.PHONY: all

all: $(addprefix $(BUILD_PATH)/,$(PROG))

$(BUILD_PATH):
	mkdir -p $@

$(BUILD_PATH)/$(PROG): $(SOURCES:.c=.o)
	$(CC) $(FLAGS) $(addprefix $(BUILD_PATH)/,$(notdir $^)) -o $@

%.o: %.c
	$(CC) $(FLAGS) -c -o $(BUILD_PATH)/$(notdir $@) $<

########

stack.c: src/stack/stack.h src/cell/cell.h
queue.c: src/queue/queue.h
board.c: src/board/board.h src/cell/cell.h
cell.c: src/cell/cell.h
maze.c: src/maze/maze.h src/board/board.h
pathfind.c: src/pathfind/pathfind.h src/board/board.h
main.c: src/stack/stack.h src/queue/queue.h src/board/board.h src/cell/cell.h src/maze/maze.h src/pathfind/pathfind.h
