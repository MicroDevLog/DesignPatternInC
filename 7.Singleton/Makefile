all: Singleton.o chocolate_boiler.o
	gcc -o Singleton Singleton.o chocolate_boiler.o
	@echo "Build complete. Run 'Singleton' to execute the program."

.PHONY: all clean

clean:
	rm -f Singleton.o
	rm -f Singleton
	rm -f chocolate_boiler.o

Singleton.o: Singleton.c
	gcc -c Singleton.c -o Singleton.o

chocolate_boiler.o: chocolate_boiler.c
	gcc -c chocolate_boiler.c -o chocolate_boiler.o