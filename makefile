all: cyconnect clean

main.o: main.c header.h
	gcc -c main.c -o main.o

endofgame.o: endofgame.c header.h
	gcc -c endofgame.c -o endofgame.o

display.o: display.c header.h
	gcc -c display.c -o display.o

gameplay.o: gameplay.c header.h
	gcc -c gameplay.c -o gameplay.o

cyconnect: main.o gameplay.o display.o endofgame.o
	gcc main.o gameplay.o display.o endofgame.o -o cyconnect

clean: 
	rm -f *.o
	rm -rf *.dSYM
