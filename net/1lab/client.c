#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
	struct sockaddr client_addr;
	char buf[10];

	int sock_fd = socket(AF_LOCAL, SOCK_STREAM | SOCK_DGRAM, 0);
	connect(sock_fd, (struct sockaddr*)&client_addr, sizeof(client_addr));
//	recv(sock_fd, buf, sizeof(buf), NULL);
	buf[0] = 'H';	
	for(int i = 0; i < 10; i++)
		printf("%c", buf[i]);
		printf("\n");
	send(sock_fd, buf, sizeof(buf), MSG_PEEK);
	recv(sock_fd, buf, sizeof(buf), MSG_PEEK);
	for(int i = 0; i < 10; i++)
		printf("%c", buf[i]);
		printf("\n");
	close(sock_fd);

	return 0;
}
