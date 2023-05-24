all: cyconnect clean

main.o: main.c header.h
	gcc -c $< -o $@

endofgame.o: endofgame.c header.h
	gcc -c endofgame.c -o endofgame.o

display.o: display.c header.h
	gcc -c display.c -o display.o

gameplay.o: gameplay.c header.h
	gcc -c gameplay.c -o gameplay.o

antibug.o: antibug.c header.h
	gcc -c antibug.c -o antibug.o

save.o: save.c header.h
	gcc -c save.c -o save.o

cyconnect: main.o gameplay.o display.o endofgame.o antibug.o save.o
	gcc main.o gameplay.o display.o endofgame.o antibug.o save.o -o cyconnect

clean: 
	rm -f *.o
	rm -rf *.dSYM
