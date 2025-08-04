all: mvc.o 
	gcc -o mvc mvc.o 
	@echo "Build complete. Run 'mvc' to execute the program."

.PHONY: all clean

clean:
	rm -f mvc.o
	rm -f mvc


mvc.o: mvc.c
	gcc -c mvc.c -o mvc.o
