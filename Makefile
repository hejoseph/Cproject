all: programme

programme: main.o labyrinthe.o
	gcc main.o labyrinthe.o -o programme

main.o: main.c
	gcc -c main.c

labyrinthe.o: labyrinthe.c
	gcc -c labyrinthe.c

clean: 
	rm -rf *.o
