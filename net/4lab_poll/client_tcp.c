#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	struct sockaddr_in client_addr;
	int buf[10];
	for(int i = 0; i < 10; i++)
		buf[i] = i;

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(5000);
	client_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	connect(sock_fd, (struct sockaddr*)&client_addr, sizeof(client_addr));
	printf("%d\n", sock_fd);
	for(int i = 0; i < 10; i++)
		printf("%d", buf[i]);
	printf("\n");
	send(sock_fd, buf, sizeof(buf), 0);
	recv(sock_fd, buf, sizeof(buf), 0);
	for(int i = 0; i < 10; i++)
		printf("%d", buf[i]);
	printf("\n");
	shutdown(sock_fd, 0);

	return 0;
}
