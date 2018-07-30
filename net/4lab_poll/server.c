#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <poll.h>
#include <unistd.h>
#include <stdlib.h>

#define TIMEOUT 100 

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

	/*Настройка poll и ожидание подключения клиента*/
	struct pollfd fds[2];
	fds[0].fd = fd_tcp;
	fds[0].events = POLLIN | POLLPRI;
	fds[0].revents = 0;

	fds[1].fd = fd_udp;
	fds[1].events = POLLIN | POLLPRI;
	fds[1].revents = 0;

	int ret;
	
	while(1){
		ret = poll(fds, 1, TIMEOUT * 100);
		if(ret == -1){
			perror("Poll:");
			return -1;
		}

		if(fds[0].revents &POLLIN){
			connection_tcp(fd_tcp);
		}

		if(fds[1].revents &POLLIN){
			connection_udp(fd_udp);
		}
	}

	shutdown(fd_tcp, 0);
	shutdown(fd_udp, 0);
	return 0;
}
