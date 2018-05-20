HEADERS = genes.h

default: genetic-algo

main.o: main.c $(HEADERS)
	gcc -c main.c -o main.o

genes.o: genes.c $(HEADERS)
	gcc -c genes.c -o genes.o

genetic-algo: main.o genes.o
	gcc -o genetic-algo main.o genes.o

clean:
	-rm -f *.o
	-rm -f genetic-algo
