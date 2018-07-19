#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	struct sockaddr_in serv_addr;
	int buf[10];
	for(int i = 0; i < 10; i++)
		buf[i] = 0;

	int sock_fd_listen = socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	if(setsockopt(sock_fd_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		perror("Setsockopt");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);
	serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	bind(sock_fd_listen, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	printf("%d\n", sock_fd_listen);
	listen(sock_fd_listen, 5);	
	perror(NULL);
	int sock_fd = accept(sock_fd_listen, NULL, NULL);
	recv(sock_fd, buf, sizeof(buf), 0);

	for(int i = 0; i < 10; i++){
		printf("%d", buf[i]);
		if(buf[i] % 2 == 0)
			buf[i] = 1;
	}
	printf("\n");
	send(sock_fd, buf, sizeof(buf), 0);
	shutdown(sock_fd, 0);
	shutdown(sock_fd_listen, 0);
	return 0;
}
