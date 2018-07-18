#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	struct sockaddr_in serv_addr;
	char buf[10];

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(100);
	serv_addr.sin_addr.s_addr = htons(INADDR_LOOPBACK);
	bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	listen(sock_fd, 5);	
	accept(sock_fd, NULL, NULL);
	recv(sock_fd, buf, sizeof(buf), MSG_WAITALL);
	buf[1] = 'e';
	for(int i = 0; i < 10; i++)
		printf("%c", buf[i]);
	printf("\n");
	send(sock_fd, buf, sizeof(buf), MSG_WAITALL);
	perror(NULL);
	close(sock_fd);

	return 0;
}
