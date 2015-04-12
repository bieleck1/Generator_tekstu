generator: main.c
	$(CC) -o generator main.c

.PHONY: clean

clean:
	-rm *.o
