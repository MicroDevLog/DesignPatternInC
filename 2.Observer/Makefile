all: Observer.o
	gcc -o Observer Observer.o
	@echo "Build complete. Run 'Observer' to execute the program."

.PHONY: all clean

clean:
	rm -f Observer.o
	rm -f Observer

Observer.o: Observer.c
	gcc -c Observer.c -o Observer.o