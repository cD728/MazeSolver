##
# Astar
#
# @file
# @version 0.1
main: *.c *.h 
	gcc *.c -lraylib -lm -g -DDEBUG -Wall -Wextra -Wswitch-enum -o main


