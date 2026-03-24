CC = gcc
CFLAGS = -Wall -Wextra
LFLAGS = -lm

TARGET = main

SRCS = main.c \
       Compute_Error.c \
       Generate_Noise.c \
       Matrix_utils.c \
       Matrix_Vector.c \
       Print_utils.c \
       Solve_System.c \
       Vector_utils.c \
       Rayleigh_Quotient_Iteration.c \
       Power_Iteration.c \
       Shifted_Inverse_Iteration.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

%.o: %.c header_eigen.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)