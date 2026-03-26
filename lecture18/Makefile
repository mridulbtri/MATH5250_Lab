CC      = clang
CFLAGS  = -O2 -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -Wall
LDFLAGS = -L/opt/homebrew/opt/libomp/lib -lomp -lm

option: main.o black_scholes_exact.o compute_integrand.o compute_simp_integration.o
	$(CC) $(CFLAGS) -o option main.o black_scholes_exact.o compute_integrand.o compute_simp_integration.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

black_scholes_exact.o: black_scholes_exact.c
	$(CC) $(CFLAGS) -c black_scholes_exact.c

compute_integrand.o: compute_integrand.c
	$(CC) $(CFLAGS) -c compute_integrand.c

compute_simp_integration.o: compute_simp_integration.c
	$(CC) $(CFLAGS) -c compute_simp_integration.c

clean:
	rm -f *.o option