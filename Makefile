all:
	gcc -o sem sem.c

run: all
	./sem -c 3
	./sem -v
	./sem -c 2
	./sem -v
	./sem -r

clean:
	rm sem
