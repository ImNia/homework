CC = gcc -Wall
CDIR = ./c_file
OBJDIR = ./object_file
HFILE = ./c_file/include

all: dir dop_file

dir: ./object_file

./object_file:
	mkdir ./object_file

dop_file: object
	$(CC) -o test $(OBJDIR)/store.o $(OBJDIR)/loader.o $(OBJDIR)/buyer.o $(OBJDIR)/main.o

object: $(CDIR)/store.c
	$(CC) -c $(CDIR)/store.c -o $(OBJDIR)/store.o -I./
	$(CC) -c $(CDIR)/loader.c -o $(OBJDIR)/loader.o -I./
	$(CC) -c $(CDIR)/buyer.c -o $(OBJDIR)/buyer.o -I./
	$(CC) -c $(CDIR)/main.c -o $(OBJDIR)/main.o -I./
clean:
	rm -rf ./object_file
	rm test
