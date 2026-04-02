# -----------------------------------------------------------------------
# Makefile for OpenMP adaptive quadrature project
# Works on: macOS (Apple Clang via Homebrew libomp) and Linux (GCC)
# -----------------------------------------------------------------------
TARGET  = main
SRCS    = main.c         \
          adaptive_int.c \
          function.c     \
          simp.c         \
          usage.c
OBJS    = $(SRCS:.c=.o)
# -----------------------------------------------------------------------
# Detect OS: macOS needs Homebrew libomp; Linux uses GCC's built-in OpenMP
# -----------------------------------------------------------------------
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    # macOS: use clang + Homebrew libomp
    # Install with: brew install libomp
    CC      = clang
    OMP_INC = $(shell brew --prefix libomp)/include
    OMP_LIB = $(shell brew --prefix libomp)/lib
    CFLAGS  = -O2 -Wall -Xpreprocessor -fopenmp -I$(OMP_INC)
    LDFLAGS = -L$(OMP_LIB) -lomp -lm
else
    # Linux: use gcc with built-in OpenMP support
    CC      = gcc
    CFLAGS  = -O2 -Wall -fopenmp
    LDFLAGS = -fopenmp -lm
endif
# -----------------------------------------------------------------------
# Rules
# -----------------------------------------------------------------------
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%.o: %.c header.h
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f $(OBJS) $(TARGET) *.data *.png
.PHONY: all clean