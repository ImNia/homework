all: server client_tcp client_udp

server: server.c
	gcc -Wall -g -o server server.c

client_tcp: client_tcp.c
	gcc -Wall -g -o client_tcp client_tcp.c

client_udp: client_udp.c
	gcc -Wall -g -o client_udp client_udp.c

clean:
	rm server
	rm client_tcp
	rm client_udp
