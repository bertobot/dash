CC=g++ -g3 -ansi -Wall 
OBJ=\
ThreadWriter.o \
Worker.o

all: $(OBJ)
	ar rs libmetroserver.a $(OBJ)

test: server.o all
	$(CC) -o server server.o $(OBJ) -L../core -lDash -lMyThread -lpthread -lSocket

.cpp.o:
	$(CC) -c $<

clean:
	rm -f *.o

mrproper: clean
	rm -f *~
	rm -f libmetroserver.a
	rm -f server

