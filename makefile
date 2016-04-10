#Sample Makefile. You can make changes to this file according to your need
# The executable must be named proxy

CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -lpthread

OBJS = tftp-server.o csapp.o

all: tftp-server

tftp-server: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o tftp-server

csapp.o: csapp.c
	$(CC) $(CFLAGS) -c csapp.c

tftp-server2.o: tftp-server.c
	$(CC) $(CFLAGS) -c tftp-server.c

clean:
	rm -f *~ *.o tftp-server 

