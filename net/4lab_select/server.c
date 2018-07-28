#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

/* Функция connection_tcp для соединения с tcp клиентом.*/
void connection_tcp(int fd_tcp)
{
	int buf[10];
	for(int i = 0; i < 10; i++)
		buf[i] = 0;

	int sock_fd = accept(fd_tcp, NULL, NULL);

	while(1){
		recv(sock_fd, buf, sizeof(buf), 0);
		for(int i = 0; i < 10; i++){
			printf("%d", buf[i]);
			if(buf[i] % 2 == 0)
				buf[i] = 1;
		}
		printf("\n");

		send(sock_fd, buf, sizeof(buf), 0);
	}
	shutdown(sock_fd, 0);
}

/* Функция connection_udp для соединения с udp клиентом.*/
void connection_udp(int fd_udp)
{
	struct sockaddr_in serv;
	int addrlen = sizeof(serv);

	int buf[10];
	for(int i = 0; i < 10; i++)
		buf[i] = 0;

	while(1){
		recvfrom(fd_udp, buf, sizeof(buf), 0, (struct sockaddr*)&serv, &addrlen);
		for(int i = 0; i < 10; i++){
			printf("%d", buf[i]);
			if(buf[i] % 2 == 0)
				buf[i] = 1;
		}
		printf("\n");
		sendto(fd_udp, buf, sizeof(buf), 0, (struct sockaddr*)&serv, addrlen);
	}
}

int main()
{
	struct sockaddr_in serv_addr;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);
	serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);


	/*Создание socket tcp*/
	int fd_tcp = socket(AF_INET, SOCK_STREAM, 0);
	perror("fd_tcp socket: ");
	bind(fd_tcp, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	perror("Bind tcp: ");
	listen(fd_tcp, 5);	
	perror("Listen tcp: ");

	/*Создание socket udp*/
	int fd_udp = socket(AF_INET, SOCK_DGRAM, 0);
	perror("fd_udp socket: ");
	bind(fd_udp, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	perror("udp bind: ");

	/*Настройка select и ожидание подключения клиента*/
	fd_set set;
	FD_ZERO(&set);
	int max_fd;
	if(fd_tcp <= fd_udp)
		max_fd = fd_udp + 1;
	else
		max_fd = fd_tcp + 1;

	while(1){
		FD_SET(fd_tcp, &set);
		FD_SET(fd_udp, &set);
		
		if(select(max_fd, &set, NULL, NULL, NULL) < 0){
			perror("Select:");
		}

		if(FD_ISSET(fd_tcp, &set)){
			connection_tcp(fd_tcp);
		}

		if(FD_ISSET(fd_udp, &set)){
			connection_udp(fd_udp);
		}
	}

	shutdown(fd_tcp, 0);
	shutdown(fd_udp, 0);
	return 0;
}
