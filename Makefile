all:
	gcc -c crypt.c -o crypt.o
	gcc -c test.c -o test.o
	gcc test.o crypt.o -o test
	gcc -c b64.c -o b64.o
	gcc b64.o crypt.o -o b64