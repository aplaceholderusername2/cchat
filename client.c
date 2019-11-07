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
void trmsend();
void *get_message(void *arg);
void *send_message(void *arg);
int define_port();
int sock;
struct sockaddr_in serverAddr;
char buffer[1024];
char message[1024];


int main(){

	atexit(trmsend);
	connect_to_server();
	pthread_t t1, t2;
	pthread_create(&t1, NULL, get_message, NULL);
	pthread_create(&t2, NULL, send_message, NULL);
	pthread_join(t1, NULL);

	return 0;
}


void connect_to_server(){
	int status = -1;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(define_port());	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	while(status == -1){
		status = connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
		usleep(FREQ);
	}
	

}


void *get_message(void *arg){
	int status = -1;
	while(1){

		status = (int)recv(sock, buffer, sizeof(buffer), 0);
		if(status == 0)
			break;
		fprintf(stderr, "\033[1;33m\%s\n", buffer);
		fprintf(stderr, "\033[34m\%s", "");
		usleep(FREQ);
		for(int i = 0; i < strlen(buffer); i++){
			buffer[i] = ' ';
			}
		}
	
	return NULL;
}


void *send_message(void *arg){
	
	while(1){

		fgets(message, sizeof(message), stdin);
		fprintf(stderr, "\033[1A\033[2K");
		send(sock, message, sizeof(message), 0);
		for(int i = 0; i < strlen(message); i++){
			message[i] = ' ';
		}
	}

	return NULL;
}


int define_port(){

	int port = 5601;
	fprintf(stderr, "[i]Server port:");
	scanf("%d", &port);

	return port;
}


void trmsend(){
	
	fprintf(stderr, "[-]Lost connection to remote socket.\n");

}