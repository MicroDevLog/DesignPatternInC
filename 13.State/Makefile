all: state.o 
	gcc -o State state.o 
	@echo "Build complete. Run 'state' to execute the program."

.PHONY: all clean

clean:
	rm -f state.o
	rm -f state


state.o: state.c
	gcc -c state.c -o state.o
