#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()

	struct sockaddr_in client_addr;
    struct sockaddr_in server

	int buf[10];
	for(int i = 0; i < 10; i++)
		buf[i] = i;
	socklen_t addrlen = sizeof(server);

	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	perror("Setsockopt: ");
	
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(5000);
	client_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	sendto(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&server, addrlen);

	perror("Sendto: ");
	for(int i = 0; i < 10; i++)
		printf("%d", buf[i]);
	printf("\n");
	recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&server, &addrlen);
//	recvfrom(sock_fd, buf, sizeof(buf), 0, NULL, NULL);
	perror("Recvfrom");
	for(int i = 0; i < 10; i++)
		printf("%d", buf[i]);
	printf("\n");

	shutdown(sock_fd, 0);
	return 0;
}
