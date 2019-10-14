#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define FREQ 50

void connect_to_server();
void *get_message(void *arg);
void *send_message(void *arg);
int define_port();

int sock;
struct sockaddr_in serverAddr;
char buffer[1024];
char message[1024];



int main(){
	// printf("attempting connection...")
	connect_to_server();

	pthread_t t1, t2; //t1 - get ^ t2 - set
	pthread_create(&t1, NULL, get_message, NULL);
	pthread_create(&t2, NULL, send_message, NULL);
	pthread_join(t1, NULL);

	return 0;
}





void connect_to_server(){
	sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(define_port());	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	fprintf(stderr, "connecting...");
	connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	fprintf(stderr, "connected.");

}

void *get_message(void *arg){

	
	while(1){
	recv(sock, buffer, sizeof(buffer), 0);
	fprintf(stderr, "\033[1;33m\%s\n", buffer);
	fprintf(stderr, "\033[34m\%s", "");
	usleep(FREQ);
	// fprintf(stderr, "\033[A\033[A");
	for(int i = 0; i < strlen(buffer); i++){
		buffer[i] = ' ';
		}
	}
	
	return NULL;
}

void *send_message(void *arg){
	while(1){

		// fprintf(stderr, "\n");
		scanf("%s", &message);

		fprintf(stderr, "\033[1A\033[2K");
		send(sock, message, sizeof(message), 0);
		for(int i = 0; i < strlen(message); i++){
			message[i] = ' ';
		}
	}
		// fprintf(stderr, "\033[A\033[A");
		// fprintf(stderr, "\033[A\033[A");

		// fprintf(stderr, "%s", message);



	return NULL;
	}




int define_port(){
	int port = 5601;
	fprintf(stderr, "please choose the server port:");
	scanf("%d", &port);

	return port;
}