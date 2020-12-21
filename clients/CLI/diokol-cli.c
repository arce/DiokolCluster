
/*
 * diokol-cli.c - Diokol command line interface
 * compile: gcc diokol-cli.c -o diokol-cli -lreadline
 * usage: diokol-cli <session> <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <readline/readline.h>
#include <readline/history.h>

#define BUFSIZE 1024

void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char **argv) {
    int sockfd, portno=6453, n, session=0;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char* hostname = "127.0.0.1";
    char *buf;

    if (argc > 1) session = atoi(argv[1]);
		if (argc > 2) hostname = argv[2];
		if (argc > 3) portno = atoi(argv[3]);
    if (argc > 4) {
       fprintf(stderr,"usage: %s <session> <hostname> <port>\n", argv[0]);
       exit(0);
    }

    //sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0);
    }
			
    bzero((char *) &serveraddr, sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
	  (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
      error("ERROR connecting");
    
		char *prompt = (char*)malloc(25 * sizeof(char));
		sprintf(prompt,"\n%s:%d[%d]> ",hostname,portno,session);
    while (1) {
			  buf = readline(prompt);
				if (!strcmp(buf,"QUIT")) break;
        n = write(sockfd, buf, strlen(buf));
        if (n < 0)
          error("ERROR writing to socket");
				add_history(buf);
				free(buf);
				if (read(sockfd, buf, sizeof(buf)) < 0)
				    error("ERROR reading from socket");
				printf("%.*s\n", (int) strlen(buf), buf);
    }
    close(sockfd);
    return 0;
}