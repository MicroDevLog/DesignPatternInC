all: AbstractFactory.o
	gcc -o AbstractFactory AbstractFactory.o
	@echo "Build complete. Run 'AbstractFactory' to execute the program."

.PHONY: all clean

clean:
	rm -f AbstractFactory.o
	rm -f AbstractFactory

AbstractFactory.o: AbstractFactory.c
	gcc -c AbstractFactory.c -o AbstractFactory.o