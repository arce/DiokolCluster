
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

#define MAX_BUFFER 65536

void error(char *msg) {
    perror(msg);
    exit(0);
}

int startsWith(const char *pre, const char *str) {
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}

int main(int argc, char **argv) {
    int sockfd, portno=6453, n, session=0;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char* hostname = "127.0.0.1";
    char request[MAX_BUFFER], *command;
		char response[MAX_BUFFER];
		char ID[10];
	  long lnum;
	  int sid=0;
	  char *end;

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
    
		using_history();
		char *prompt = (char*)malloc(128 * sizeof(char));
		sprintf(prompt,"\n%s:%d[%d]> ",hostname,portno,session);
    while (1) {
			  command = readline(prompt);
				if (!strcmp(command,"QUIT")) break;
				if (startsWith("SESSION",command)) {
					char *token = strtok(command," ");
					token = strtok(NULL,"");
					if (token==NULL) {
						printf("ERROR: session ID not found\n");
						continue;
					}
					printf("%s\n",token);
					strcpy(ID,token);
					lnum = strtol(ID, &end, 10);
			    if (end == token) {
			      printf("ERROR: invalid session ID\n");
			      continue;
			    }
			    sid = (int)lnum;
					printf("OK");
					continue;
				}
				sprintf(request,"SESSION %d VGTP/0.1\n %s",sid,command);
        n = write(sockfd, request, strlen(request));
        if (n < 0)
          error("ERROR: writing to server");
				add_history(command);
				free(command);
				bzero(response,MAX_BUFFER);
				if (read(sockfd, response, MAX_BUFFER) < 0)
				    error("ERROR: reading from server");
				printf("%s", response);
    }
    close(sockfd);
    return 0;
}