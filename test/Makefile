
Mazenew: Mazenew.o stack.o mylib.o 
	gcc -o Mazenew -g Mazenew.o stack.o mylib.o

Mazenew.o: Mazenew.c stack.c mylib.c
	gcc -Wall -pedantic -c -g Mazenew.c

stack.o: stack.c stack.h
	gcc -Wall -pedantic -c -g stack.c

mylib.o: mylib.c mylib.h
	gcc -Wall -pedantic -c -g mylib.c

