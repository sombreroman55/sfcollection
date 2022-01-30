CC=gcc
CFLAGS=-I. -I./frontend/ -I./ds/ -I./preproccessor/ -I./optimizer/ -I./backend/
DEPS = helpers.h ./ds/token.h ./frontend/lexer.h
OBJ = helpers.o ./ds/token.o ./frontend/lexer.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sfcc: $(OBJ)
	$(CC) -o sfcc sfcc.c $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o
