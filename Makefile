all: bin2c

bin2c: bin2c.c
	cc -std=c99 bin2c.c -o bin2c

clean:
	rm bin2c