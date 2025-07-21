all: iterator.o 
	gcc -o iterator iterator.o 
	@echo "Build complete. Run 'iterator' to execute the program."

.PHONY: all clean

clean:
	rm -f iterator.o
	rm -f iterator


iterator.o: iterator.c
	gcc -c iterator.c -o iterator.o

