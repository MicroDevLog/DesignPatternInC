all: command.o 
	gcc -o command command.o 
	@echo "Build complete. Run 'command' to execute the program."

.PHONY: all clean

clean:
	rm -f command.o
	rm -f command


command.o: command.c
	gcc -c command.c -o command.o

