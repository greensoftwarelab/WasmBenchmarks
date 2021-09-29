#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/fcntl.h>
#include <iostream>
#include <vector>
#include <termios.h>
#include <arpa/inet.h>
#include "rapl.h"

using namespace std;
using std::vector;
#define BAUDRATE B115200
#define MAX 80
#define STRMAX 256
#define PORT 8080

/* Global server configurations */
int run = 1; /* Is it running */
float usecs = 1000000; /* Measurement intervals (microsseconds) */ 
char raplOutput[STRMAX] = "results/results.rapl"; /* Rapl output logfile name */
char arduinoOutput[STRMAX] = "results/results.ard"; /* Watts Up logfile name */
char wattsupOutput[STRMAX] = "results/results.watts"; /* Watts Up logfile name */
char usbserial[STRMAX] = "/dev/ttyUSB0"; /* Usb serial port name where Arduino is connected */
// char usbserialwatts[STRMAX] = "/dev/ttyUSB1"; /* Usb serial port name where watts is connected */

/* Resets server configurations */
void resetConfig() {
	run = 1;
	usecs = 1000000;
	strcpy(raplOutput, "results/results.rapl");
	strcpy(arduinoOutput, "results/results.ard");
	strcpy(wattsupOutput, "results/results.watts");
//	strcpy(usbserial, "/dev/ttyUSB1");
	strcpy(usbserial, "/dev/ttyUSB0");

}

/* 
 * Given a Watts Up log response 
 * Returns an array with each field value
 */
char ** getRecords (char * response) {
	char ** record = malloc(21 * sizeof(char *));
	char * recordraw = malloc(strlen(response) * sizeof(char));;

	int i = 0;
	strcpy(recordraw, response);

	char *field = strtok(recordraw, ",");

	while(field != NULL)
	{
		record[i] = malloc(strlen(field) * sizeof(char));
		strcpy(record[i++], field);
		field = strtok(NULL, ",");
	}

	return record;
}

/*
 * Gather configurations sent by client
 */
void gatherConfigs(char * string){
	char *found;
	found = strsep(&string," ");
	found = strsep(&string," ");
	usecs = atof(found);
	found = strsep(&string," ");
	strcpy(raplOutput, found);
	strcat(raplOutput, ".rapl");
	strcpy(arduinoOutput, found);
	strcat(arduinoOutput, ".ard");
}

/*
 * Thread 
 * 
 * Gathers energy information from RAPL
 * every <usecs> microsseconds
 * 
 * Adds records to logfile for later analysis
 */
void * runRAPL(){
    int core = 0;

    FILE * fp = fopen(raplOutput, "w+"); /* Open file */

	fprintf(fp, "Package,CPU,GPU,DRAM\n"); /* Write header line */

	rapl_init(core);

	while(run){
	    rapl_before(fp, core);
		usleep(usecs);
		if(run) rapl_after(fp, core);
	}

    fclose(fp);
	pthread_exit(0);
	return NULL;
}

/*
 * Thread 
 * 
 * Gathers power information from arduino
 * every <usecs> microsseconds
 * 
 * Adds records to logfile for later analysis
 */
void * gatherWattsUp(){
	int fd_serial = 0;
	FILE * f_serial, * fp;
	struct termios attribs;
	char wattsupResponse[300];
	char ** record;
	int n = 0;
	char c ;

	fp = fopen(wattsupOutput, "w+");

	printf("WATTS UP: Opening usb serial port: %s\n", usbserial);

	fd_serial = open(usbserial, O_RDWR | O_NOCTTY);

	if (fd_serial < 0) {
		printf("WATTS UP: Serial port failed while opening...\n");
		pthread_exit(0);
	} else {
		printf("WATTS UP: Opened serial port.");
	}

	tcgetattr(fd_serial,&attribs); /* Get current serial attributes */
	cfsetospeed(&attribs, BAUDRATE); /* change outut baudrate */
	cfsetispeed(&attribs, BAUDRATE); /* change input baudrate */

	tcflush(fd_serial, TCIFLUSH);  
	tcsetattr(fd_serial,TCSANOW,&attribs); /* Apply changes */

	f_serial = fdopen(fd_serial, "r+");

	fprintf(f_serial, "#L,W,3,E,,%f;", usecs / 1000000); /* Start logging (Note - if %f doesn't work use %d) */
	fprintf(fp, "Watts,Joules\n"); /* Write header line */

	while(run) {
		while((c = getc(f_serial)) != '\n') {
			if(c != '\n') wattsupResponse[n++] = c;
		}

		if(run) {
			record = getRecords(wattsupResponse);

			if (record[3] != NULL) {
				fprintf(fp, "%f, %f\n", atof(record[3]) / 10, (atof(record[3]) / 10) * (usecs / 1000000));
			}
			else {
				fprintf(fp, "Skip\n");
			}

			bzero(wattsupResponse, 300);
			n = 0;
		}
	}

	close(fd_serial);
	fclose(f_serial);
	fclose(fp);

	pthread_exit(0);
	return NULL;
}

/*
 * Thread 
 * 
 * Gathers power information from arduino
 * every <usecs> microsseconds
 * 
 * Adds records to logfile for later analysis
 */
void * gatherArduino(){
	int fd_serial = 0;
	FILE * f_serial, * fp;
	struct termios attribs;
	char arduinoResponse[300];
	int n = 0;
	char c ;

	fp = fopen(arduinoOutput, "w+");

	printf("ARDUINO: Opening usb serial port: %s\n", usbserial);

	fd_serial = open(usbserial, O_RDWR | O_NOCTTY);

	if (fd_serial < 0) {
		printf("ARDUINO: Serial port failed while opening...\n");
		pthread_exit(0);
	} else {
		printf("ARDUINO: Opened serial port.");
	}
	tcgetattr(fd_serial,&attribs); /* Get current serial attributes */
	cfsetospeed(&attribs, BAUDRATE); /* change outut baudrate */
	cfsetispeed(&attribs, BAUDRATE); /* change input baudrate */
	tcflush(fd_serial, TCIFLUSH);  
	tcsetattr(fd_serial,TCSANOW,&attribs); /* Apply changes */
	std::vector<float> vecArduino = {}; /* Vector of Arduino values */
	f_serial = fdopen(fd_serial, "r+");
	//float* array = malloc(n * sizeof(float)); /* Array version not working */
	int nelems = 0;
	fprintf(f_serial, "%f\n", usecs / 1000000); /* Start logging */
	while(run) {
		while((c = getc(f_serial)) != '\n') {
			if(c != '\n') arduinoResponse[n++] = c;
		}
		if(run) {			
			float valor = atof(arduinoResponse);
			vecArduino.push_back(valor);
	//		array[nelems] = valor;
			bzero(arduinoResponse, 300);
			n = 0;
			nelems++;
		}
	}
	fprintf(fp, "Joules\n"); /* Write header line */
	/*Writing values in file*/
	for(float n : vecArduino) {
		fprintf(fp,"%f\n", n);
    }
//	for(int j = 0 ; j < nelems ; j++) {
//		fprintf(fp,"%f\n", array[j] );
    //}
	close(fd_serial);
	fclose(f_serial);
	fclose(fp);

	pthread_exit(0);
	return NULL;
}

/*
 * Waits for a client message
 */
void waitMessage(int sockfd)
{
	char buff[STRMAX], message[STRMAX];
	pthread_t raplThread;
	pthread_t arduinoThread;
	//pthread_t wattsupThread;

	/* infinite loop for chat */ 
	for (;;) {
		/* clear buffer and message */
		bzero(buff, STRMAX);
		bzero(message, STRMAX);

		/* Reads message into buffer */ 
		read(sockfd, buff, sizeof(buff));
        printf("%s\n", buff);

		/* Copies buffer */
		strcpy(message ,buff );

		/* If "start" was received, starts RAPL and Watts Up readings */
	    /* If "end" was received, end RAPL and Watts Up readings */
		if (strncmp("start", message, 5) == 0) {
			gatherConfigs(message);

			printf("STARTING RAPL and Watts Up\n"
					"INTERVAL: %f\n"
					"RAPL OUTPUT: %s\n"
					"ARDUINO OUTPUT: %s\n",
					usecs, raplOutput, arduinoOutput);

    		pthread_create(&raplThread, NULL, runRAPL, NULL);
    		//pthread_create(&arduinoThread, NULL, gatherArduino, NULL);
		} else if (strncmp("end", message, 3) == 0) {
			/* Stops thread execution */
			run = 0;

			printf("STOPING RAPL and Watts Up.\n");
			pthread_join(raplThread, 0);
			//pthread_join(arduinoThread, 0);
			printf("SUCESSFULY STOPPED.\n");

			break;
		}
	}
}

void sighandler(){
	exit(0);
}

/* Server Main */ 
int main()
{
	int sockfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr;

	/* Signal for killing the server */ 
	signal(SIGTERM, sighandler);

	/* Socket creation */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else {
		printf("Socket successfully created.\n");
	}

	/* Server configs (Family, address, port) */
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	/* Binding newly created socket to given IP and verification */
	if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else {
		printf("Socket successfully binded.\n");
	}

	/* Server is listening */
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else {
		printf("Server listening..\n");
	}

	// Run forever
	while(1) {

		// Resets server configs
		resetConfig();

		len = sizeof(servaddr);
		
		// Accept the data packet from client and verification
		connfd = accept(sockfd, (struct sockaddr *)&servaddr, &len);
		
		if (connfd < 0) {
			printf("server acccept failed...\n");
			exit(0);
		}
		else {
			printf("server acccept the client...\n");
		}

		// Communication between server and client
		waitMessage(connfd);

		// Close connection
		close(connfd);
	}

	// Close the socket
	close(sockfd);
}
