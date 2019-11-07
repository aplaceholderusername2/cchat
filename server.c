#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "helperA.h"

void s_init();
void *send_message(void *arg);
void *keepAlive(int socket);
void *getMessage(void* arg);
int define_port();
int PORT;
char buffer[1024];
int status;

int main(){
	s_init();
	
	return 0;
}

void s_init(){

	char serv_msg[1024] = "\n\n\nWelcome to 6xfcastle!\n\n\n";
	int serv_sock;
	int users = 50;
	int client_sock;
	struct sockaddr_in serv_addr;

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	PORT = define_port();
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	listen(serv_sock, users);
	
	TKDM(PORT);

	while(1){

		client_sock = accept(serv_sock, NULL, NULL); // struct-where, struct-size?
		pthread_t t1;
		pthread_create(&t1, NULL, keepAlive, client_sock);
		// pthread_join(t1, NULL);	
		status = (int)recv(client_sock, buffer, sizeof(buffer), 0);

		printf("%s", buffer);
		printf("sending the message..");
		send(client_sock, serv_msg, sizeof(serv_msg), 0);
		// printf("server MOTD sent!\t%d\n", client_sock/*(struct sockaddr_in*)&client_addr*/);

	}
	close(serv_sock);



}

int define_port(){

	int port = 5601;
	fprintf(stderr, "please choose the server port:");
	scanf("%d", &port);

	return port;
}

void *keepAlive(int socket){
	while(1){
		send(socket, buffer, sizeof(buffer), 0);
		fprintf(stderr, "[CONN] %i", socket);
		usleep(5000000);

	}
void *getMessage(void* arg){
	return;
	}
}
