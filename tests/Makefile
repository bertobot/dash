CC = g++ $(CCFLAGS) -ansi -Wall
TARGETS = test1 test2 test3

all: $(TARGETS)

test1: test1.o
	$(CC) -o test1 test1.o -L../core -lDash -lMyThread -lpthread

test2: test2.o
	$(CC) -o test2 test2.o -L../core -lDash -lSocket

test3: test3.o
	$(CC) -o test3 test3.o -L../core -lDash -lSocket -lMyThread -lpthread

.cpp.o:
	$(CC) -c $<

clean:
	rm -f *.o
	rm -f *~

mrproper: clean
	rm -f $(TARGETS)

