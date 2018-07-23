#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <signal.h>

/*
 * Функция socket_function принимает из функции main
 * дескриптор и выполняет прием и отправку сообщений
 * с клиентом. Функция была сделана для того чтобы иметь 
 * соединение с несколькими клиентами.
 */
void socket_function(int sock_fd)
{
	int buf[10];
	for(int i = 0; i < 10; i++)
		buf[i] = 0;
	
	while(1){	
		recv(sock_fd, buf, sizeof(buf), 0);
		for(int i = 0; i < 10; i++){
			if(buf[i] % 2 == 0)
				buf[i] = 0;
			}
		send(sock_fd, buf, sizeof(buf), 0);	
	}
	shutdown(sock_fd, 0);
}

int main()
{
	struct sockaddr_in serv_addr;

	int sock_fd_listen = socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	if(setsockopt(sock_fd_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		perror("Setsockopt");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);
	serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	bind(sock_fd_listen, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	int pid;
	while(1){
		listen(sock_fd_listen, 5);	
		int sock_fd = accept(sock_fd_listen, NULL, NULL);
		pid = fork();
		if(pid == 0){
			socket_function(sock_fd);
		}
	}
	kill(pid, SIGTERM);
	
	shutdown(sock_fd_listen, 0);
	return 0;
}
