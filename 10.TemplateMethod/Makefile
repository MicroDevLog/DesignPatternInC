all: TemplateMethod.o 
	gcc -o TemplateMethod TemplateMethod.o 
	@echo "Build complete. Run 'TemplateMethod' to execute the program."

.PHONY: all clean

clean:
	rm -f TemplateMethod.o
	rm -f TemplateMethod


TemplateMethod.o: TemplateMethod.c
	gcc -c TemplateMethod.c -o TemplateMethod.o

