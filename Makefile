all:
	gcc -c crypt.c -o crypt.o
	gcc -c test.c -o test.o
	gcc test.o crypt.o -o test