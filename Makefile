generator: main.o baza.o generacja.o
	$(CC) -o generator main.c baza.c generacja.c

.PHONY: clean

clean:
	-rm *.o
