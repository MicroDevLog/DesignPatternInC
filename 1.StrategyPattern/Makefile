all: strategy_pattern_static.o
	gcc -o strategy strategy_pattern_static.o
	@echo "Build complete. Run 'strategy' to execute the program."

.PHONY: all clean

clean:
	rm -f strategy_pattern_static.o
	rm -f strategy_pattern_static

strategy_pattern_static.o: strategy_pattern_static.c
	gcc -c strategy_pattern_static.c -o strategy_pattern_static.o