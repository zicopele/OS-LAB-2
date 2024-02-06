#Makefile for myshell
#Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

#Source files
SRC = myshell.c utility.c

#Object files
OBJ = $(SRC:.c=.o)

#Target binary
TARGET = myshell

#Rule to build the target binary
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

#Rule to compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

#Phony target to clean the project
clean:
	rm -f $(OBJ) $(TARGET)
