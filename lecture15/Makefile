CC = gcc
CFLAGS = -Wall -Wextra
LFLAGS = -lm

TARGET = main

SRCS = main.c \
       Matrix_utils.c \
       Matrix_Vector.c \
       Print_utils.c \
       Vector_utils.c \
       FindZero.c\
       GetShift.c \
       Hessenberg.c \
       Householder.c \
       QRdecomp.c \
       RecursiveQR.c \
       Triagonal_utils.c \
       Pentadiag_utils.c \

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

%.o: %.c header_eigen.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)