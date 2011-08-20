CC = g++ $(CCFLAGS) -ansi -Wall
TARGETS = test1

all: $(TARGETS)

test1: test1.o
	$(CC) -o test1 test1.o -L../core -lDash -lMyThread -lpthread

.cpp.o:
	$(CC) -c $<

clean:
	rm -f *.o
	rm -f *~

mrproper: clean
	rm -f $(TARGETS)

