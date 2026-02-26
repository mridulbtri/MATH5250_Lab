CC = gcc
FFLAGS = -O3 -Wall
LFLAGS =
OBJECTS = main.o \
	Bisection.o \
	DisplayStack.o \
	DeleteStack.o \
	Function.o \
	Peek.o \
	Push.o \
	Pop.o \
	StackSize.o

.PHONY: clean help

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main.exe

help:
	@echo "make - build main.exe"
	@echo "make clean - remove object files and executable"
