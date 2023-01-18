CC=gcc
DEPS = src/utilsFiles.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< 

preprocesor: preprocesor.o preprocesor.o 
	$(CC) -o preprocesor preprocesor.o preprocesor.o 
