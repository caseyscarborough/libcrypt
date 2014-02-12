CC=gcc
CFLAGS=-Wall -Wno-unused-variable
SRC=src
BIN=bin
TESTS=test
UTILS=utils

all: mkdir test b64 md5

test: $(TESTS)/crypt-test.c
	$(CC) $(CFLAGS) $(SRC)/crypt.c $(TESTS)/crypt-test.c -o $(TESTS)/crypt-$@ -lcheck

b64: $(UTILS)/b64.c
	$(CC) $(CFLAGS) $(SRC)/crypt.c $< -o $(BIN)/$@

md5: $(UTILS)/md5.c
	$(CC) $(CFLAGS) $(SRC)/crypt.c $< -o $(BIN)/$@

mkdir:
	mkdir -p $(BIN)

clean:
	rm -f $(BIN)/*

.PHONY: all test clean