#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
	struct sockaddr serv_addr;
	char buf[10];
	int sock_fd = socket(AF_LOCAL, SOCK_STREAM | SOCK_DGRAM, 0);
	bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	listen(sock_fd, 5);	
	accept(sock_fd, NULL, NULL);
	recv(sock_fd, buf, sizeof(buf), MSG_WAITALL);
	buf[1] = 'e';
	send(sock_fd, buf, sizeof(buf), MSG_WAITALL);
	close(sock_fd);

	return 0;
}
