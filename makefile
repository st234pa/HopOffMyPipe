GCC = gcc -g

all: client.c server.c pipe_networking.o unnamed.c
	$(GCC) client.c server.c pipe_networking.o unnamed.c handshaketest

pipe_networking.o: pipe_networking.c pipe_networking.h
	$(GCC) -c pipe_networking.c

clean:
	rm *.o
	rm *~

run: all
	./handshaketest
