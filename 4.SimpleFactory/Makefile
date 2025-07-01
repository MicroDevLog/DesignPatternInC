all: SimpleFactory.o
	gcc -o SimpleFactory SimpleFactory.o
	@echo "Build complete. Run 'SimpleFactory' to execute the program."

.PHONY: all clean

clean:
	rm -f SimpleFactory.o
	rm -f SimpleFactory

SimpleFactory.o: SimpleFactory.c
	gcc -c SimpleFactory.c -o SimpleFactory.o