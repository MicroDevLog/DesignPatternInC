all: remoteProxy.o 
	gcc -o remoteProxy remoteProxy.o 
	@echo "Build complete. Run 'remoteProxy' to execute the program."

.PHONY: all clean

clean:
	rm -f remoteProxy.o
	rm -f remoteProxy


remoteProxy.o: remoteProxy.c
	gcc -c remoteProxy.c -o remoteProxy.o
