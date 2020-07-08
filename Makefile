CC=gcc
CFLAGS=-ansi -pedantic -Wall
LDFLAGS=-lMLV

OBJ=Main.o Labyrinthe.o UnionFind.o AffichageAscii.o MLV.o Option.o FileLaby.o

labyrinthe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

Main.o: Main.c Labyrinthe.h AffichageAscii.h MLV.h Option.h UnionFind.h

Labyrinthe.o: Labyrinthe.c Labyrinthe.h UnionFind.h

UnionFind.o: UnionFind.c UnionFind.h Labyrinthe.h

AffichageAscii.o: AffichageAscii.c AffichageAscii.h Labyrinthe.h

MLV.o: MLV.c MLV.h Labyrinthe.h

Option.o: Option.c Option.h

FileLaby.o: FileLaby.c FileLaby.h Labyrinthe.h

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f labyrinthe

install: labyrinthe
	mkdir ../bin
	mv labyrinthe ../bin/labyrinthe
	make mrproper

uninstall: mrproper
	rm -f ../bin/labyrinthe
	rm -rf ../bin

