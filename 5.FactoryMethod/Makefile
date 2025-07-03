all: FactoryMethod.o
	gcc -o FactoryMethod FactoryMethod.o
	@echo "Build complete. Run 'FactoryMethod' to execute the program."

.PHONY: all clean

clean:
	rm -f FactoryMethod.o
	rm -f FactoryMethod

FactoryMethod.o: FactoryMethod.c
	gcc -c FactoryMethod.c -o FactoryMethod.o