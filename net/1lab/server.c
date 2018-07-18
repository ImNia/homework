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

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);
	serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	perror(NULL);
	listen(sock_fd, 5);	
	accept(sock_fd, NULL, NULL);
	recv(sock_fd, buf, sizeof(buf), 0);
	for(int i = 0; i < 10; i++){
		if(buf[i] == 2)
			buf[i] = 1;
		printf("%d", buf[i]);
	}
	printf("\n");
	send(sock_fd, buf, sizeof(buf), 0);
	perror(NULL);
	close(sock_fd);
	perror(NULL);
	return 0;
}
