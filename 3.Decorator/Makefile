all: Decorator.o
	gcc -o Decorator Decorator.o
	@echo "Build complete. Run 'Decorator' to execute the program."

.PHONY: all clean

clean:
	rm -f Decorator.o
	rm -f Decorator

Decorator.o: Decorator.c
	gcc -c Decorator.c -o Decorator.o