CC=g++ -g3 -ansi -Wall 
OBJ=\
DashChannelHandler.o \
ProxyCommand.o \
KeysCommand.o \
StatsCommand.o \
LimitCommand.o

all: $(OBJ)
	ar rs libmetroserver.a $(OBJ)

server: server.o all
	$(CC) -o server server.o $(OBJ) -L../core -lDash -lMyThread -lpthread -lstrmanip++ -lControlPort -lnetty++ -lSocket -lMyThread

.cpp.o:
	$(CC) -c $<

clean:
	rm -f *.o

mrproper: clean
	rm -f *~
	rm -f libmetroserver.a
	rm -f server

