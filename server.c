#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

int define_port();

int main(){

	char serv_msg[1024] = "\n\n\nWelcome to 6xfcastle!\n\n\n";
	int serv_sock;
	int users = 50;
	// int PORT = 5602;
	int client_sock;
	struct sockaddr_in serv_addr;
	// struct sockaddr client_addr;
	// struct socklen_t client_addrlen[256];

	

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(define_port());
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

	listen(serv_sock, users);
	while(1){
	client_sock = accept(serv_sock, NULL, NULL); // struct-where, struct-size?
	printf("sending the message..\n");
	send(client_sock, serv_msg, sizeof(serv_msg), 0);
	// printf("server MOTD sent!\t%d\n", client_sock/*(struct sockaddr_in*)&client_addr*/);

}
	close(serv_sock);

	return 0;
}

int define_port(){
	int port = 5601;
	fprintf(stderr, "please choose the server port:");
	scanf("%d", &port);

	return port;
}