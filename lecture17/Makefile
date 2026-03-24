CC = clang
CFLAGS = -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp

all:
	$(CC) $(CFLAGS) main.c gen_random_image.c apply_filter.c -o main

clean:
	rm -f main