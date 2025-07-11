all: adapter.o 
	gcc -o adapter adapter.o 
	@echo "Build complete. Run 'adapter' to execute the program."

.PHONY: all clean

clean:
	rm -f adapter.o
	rm -f adapter


adapter.o: adapter.c
	gcc -c adapter.c -o adapter.o

