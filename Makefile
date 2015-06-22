generator: main.o baza.o generacja.o stat.o
	$(CC) -o generator main.c baza.c generacja.c stat.c

.PHONY: clean

clean:
	-rm *.o
