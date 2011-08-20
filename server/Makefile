CC=g++ -g3 -ansi -Wall 
OBJ=\
MetricHash.o \
ThreadWriter.o \
Worker.o

all: $(OBJ)
	ar rs libmetroserver.a $(OBJ)

test: server.o all
	$(CC) -o server server.o $(OBJ) -L../common -L../fs -lMyThread -lpthread -lSocket -lmetroutils

.cpp.o:
	$(CC) -c $<

clean:
	rm -f *.o

mrproper: clean
	rm -f *~
	rm -f libmetroserver.a
	rm -f server

