CC = g++ $(CCFLAGS) -ansi -Wall
OBJ=\
Dash.o \
DashClient.o

lib: $(OBJ)
	ar rs libDash.a $(OBJ)

server: $(OBJ) main.o
	$(CC) -o dash $(OBJ)

.cpp.o:
	$(CC) -c $<

clean:
	rm -f *.o
	rm -f *~

mrproper: clean
	rm -f dash
	rm -f libDash.a

