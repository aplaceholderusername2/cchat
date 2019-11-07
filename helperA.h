#include <stdio.h>
#include <unistd.h>

void TKDM(int port);

void TKDM(int port){


	
	fprintf(stderr, "\033[1;36m");

	fprintf(stderr, "[+]Initialzing... \t| [STARTUP]\n");
	usleep(100000);
	fprintf(stderr, "[+]Binding port   \t| [STARTUP]\n");
	usleep(400000);
	fprintf(stderr, "[ ]Port: %d	   \t| [STARTUP]\n", port);
	usleep(300000);
	fprintf(stderr, "[+]Success	   \t| [STARTUP]\n");
	usleep(700000);
	fprintf(stderr, "[+]Starting thread\t| [STARTUP]\n");
	usleep(1000000);

	for(int i = 1; i <= 65; i++){	
		fprintf(stderr, "█");
		usleep(10000);
		}
	usleep(200000);
	fprintf(stderr, "\nDone.\n");
	usleep(1000000);
}
