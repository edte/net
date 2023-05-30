CPPFLAGS = -I ../include/ -I ../include/device -Wall  -pthread -Wno-address-of-packed-member

SRCS := $(wildcard src/**/*.c)
OBJS := $(patsubst %.c, ../build/%.o,$(notdir $(SRCS)))

all: server client 

server: 
	make -C ..
	$(CC) $(CFLAGS) $(CPPFLAGS) -c server.c -o ../build/server.o
	$(CC) $(OBJS) ../build/server.o -o server 
	@echo

client: 
	make -C ..
	$(CC) $(CFLAGS) $(CPPFLAGS) -c client.c -o ../build/client.o
	$(CC) $(OBJS) ../build/client.o -o client 
	@echo

.PHONY: clean server client

clean:
	cd .. && make clean
	rm -rf server client
