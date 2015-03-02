CC=g++
CFLAGS=-I.
DEPS = Image.hpp Kernel.hpp
OBJ = Image.o Kernel.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

imageProcessingDemo: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
