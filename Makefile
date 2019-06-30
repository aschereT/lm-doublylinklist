all: main.c doublelinklist.c
	gcc -w -g -o lmlist main.c doublelinklist.c
testleak: all
	valgrind --track-origins=yes --leak-check=full ./lmlist
clean:
	rm lmlist
	rm doublelinklist.h.gch