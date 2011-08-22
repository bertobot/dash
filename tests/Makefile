CC = g++ $(CCFLAGS) -ansi -Wall
TARGETS = test1 test2

all: $(TARGETS)

test1: test1.o
	$(CC) -o test1 test1.o -L../core -lDash -lMyThread -lpthread

test2: test2.o
	$(CC) -o test2 test2.o -L../core -lDash -lSocket

.cpp.o:
	$(CC) -c $<

clean:
	rm -f *.o
	rm -f *~

mrproper: clean
	rm -f $(TARGETS)

