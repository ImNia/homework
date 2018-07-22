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
	int addrlen = sizeof(serv_addr);
	
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	perror("Setsockopt");
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);
	serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	perror("Bind");
	recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&serv_addr, &addrlen);
//	recvfrom(sock_fd, buf, sizeof(buf), 0, NULL, NULL);
	perror("Recvfrom");
	for(int i = 0; i < 10; i++){
		if(buf[i] % 2 == 0)
			buf[i] = 0;
		printf("%d", buf[i]);
	}
	printf("\n");
	sendto(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&serv_addr, addrlen);

	perror("Sendto");

	shutdown(sock_fd, 0);
	return 0;
}
