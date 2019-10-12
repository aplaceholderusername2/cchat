#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
	int sock;
	int PORT = 5601;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	printf("connecting...");
	connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("connected.");
	while(1){
		recv(sock, buffer, sizeof(buffer), 0);
		printf("%s\n", buffer);
		for(int i = 0; i < strlen(buffer); i++){
			buffer[i] = ' ';
		}
	}
	return 0;
}
