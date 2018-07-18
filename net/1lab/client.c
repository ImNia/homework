#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	struct sockaddr_in client_addr;
	char buf[10];

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(100);
	client_addr.sin_addr.s_addr = htons(INADDR_LOOPBACK);
	connect(sock_fd, (struct sockaddr*)&client_addr, sizeof(client_addr));
//	recv(sock_fd, buf, sizeof(buf), NULL);
	buf[0] = 'H';	
	for(int i = 0; i < 10; i++)
		printf("%c", buf[i]);
	printf("\n");
	send(sock_fd, buf, sizeof(buf), MSG_WAITALL);
	recv(sock_fd, buf, sizeof(buf), MSG_WAITALL);
	for(int i = 0; i < 10; i++)
		printf("%c", buf[i]);
	printf("\n");
	perror(NULL);
	close(sock_fd);

	return 0;
}
