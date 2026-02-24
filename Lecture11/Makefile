CC     = gcc
FFLAGS = -O3
LFLAGS =
OBJECTS = main.o AddPolys.o Array2Poly.o EvaluatePoly.o \
	  FreeMemory.o GetCoeffs.o GetEvaluationPoint.o PrintPoly.o WriteToFile.o

.PHONY: clean help

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe -lm

%%.o: %%.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main.exe

help:
	@echo "Valid targets:"
	@echo "  main.exe"
	@echo "  clean"
