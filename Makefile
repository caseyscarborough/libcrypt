CC=gcc
CFLAGS=-Wall -Wno-unused-variable
SRC=src
BIN=bin
TESTS=test
UTILS=utils

all: mkdir crypt.o test.o test b64.o b64

crypt.o: $(SRC)/crypt.c
	$(CC) $(CFLAGS) -c $< -o $(BIN)/$@

test.o: $(TESTS)/test.c
	$(CC) $(CFLAGS) -c $< -o $(BIN)/$@

test: $(BIN)/test.o $(BIN)/crypt.o
	$(CC) $(CFLAGS) $(BIN)/test.o $(BIN)/crypt.o -o $(BIN)/$@

b64.o: $(UTILS)/b64.c
	$(CC) $(CFLAGS) -c $< -o $(BIN)/b64.o

b64: $(BIN)/b64.o $(BIN)/crypt.o
	$(CC) $(CFLAGS) $(BIN)/b64.o $(BIN)/crypt.o -o $(BIN)/$@

mkdir:
	mkdir -p $(BIN)

clean:
	rm -f $(BIN)/*