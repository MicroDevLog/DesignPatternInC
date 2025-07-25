all: Composite.o 
	gcc -o Composite Composite.o 
	@echo "Build complete. Run 'Composite' to execute the program."

.PHONY: all clean

clean:
	rm -f Composite.o
	rm -f Composite


Composite.o: Composite.c
	gcc -c Composite.c -o Composite.o

