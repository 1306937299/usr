CC=gcc
CFLAGS+=-Wall
CFLAGS+=-g
CFLAGS+=-D SIP=\"192.168.2.252\"
LDFLAGS+=-lpthread

all:ser cli

ser:server.c
	${CC} ${CFLAGS} $^ ${LDFLAGS} -o $@ 
	
cli:client.c
	${CC} ${CFLAGS} $^ -o $@ 

clean:
	@-rm ser cli -f
