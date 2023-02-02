default: main

main.o: main_submission.c
	gcc -c main_submission.c -o main.o

main: main.o
	gcc main.o -o main

clean:
	-rm -f main.o
	-rm -f main
