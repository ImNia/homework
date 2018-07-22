#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	struct sockaddr_in client_addr;
	struct sockaddr_in serv_addr;

	int buf[10];
	for(int i = 0; i < 10; i++)
		buf[i] = i;
	int *addrlen;

	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	perror("Setsockopt: ");
/*	int opt = 1;
	if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	perror("Setsockopt");	
*/
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(5000);
	client_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	sendto(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));

	perror("Sendto: ");
	for(int i = 0; i < 10; i++)
		printf("%d", buf[i]);
	printf("\n");
//	recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, (socklen_t *)&addrlen);
	recvfrom(sock_fd, buf, sizeof(buf), 0, NULL, NULL);
	perror("Recvfrom");
	for(int i = 0; i < 10; i++)
		printf("%d", buf[i]);
	printf("\n");

	shutdown(sock_fd, 0);
	return 0;
}
