/*
 * diokol-cli.c - Diokol command line interface
 * usage: diokol-cli <session> <host> <port>
 */
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <readline/history.h>
#include <readline/readline.h>

#define MAX_BUFFER 65536
int sockfd = 0, portno = 6453, n, session = 0;
struct sockaddr_in serveraddr;
struct hostent *server;
char *hostname = "127.0.0.1";

int startsWith(const char *pre, const char *str) {
  size_t lenpre = strlen(pre), lenstr = strlen(str);
  return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}

int connectHost(char* hostname) {
	if (sockfd!=0) close(sockfd);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    fprintf(stderr,"ERROR: connecting server");
		return 0;
	}

  server = gethostbyname(hostname);
  if (server == NULL) {
    fprintf(stderr,"ERROR: no such host as %s\n", hostname);
    return 0;
  }

  bzero((char *)&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr,
        server->h_length);
  serveraddr.sin_port = htons(portno);

  if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
    fprintf(stderr,"ERROR: connecting server");
		return 0;
	}
	return 1;
}

int main(int argc, char **argv) {
  char request[MAX_BUFFER], *command;
  char response[MAX_BUFFER];
  long lnum;
  int sid = 0;
  char *end;
	char ID[6];

  if (argc > 1)
    sid = atoi(argv[1]);
  if (argc > 2)
    hostname = argv[2];
  if (argc > 3)
    portno = atoi(argv[3]);
  if (argc > 4) {
    fprintf(stderr, "usage: %s <session> <hostname> <port>\n", argv[0]);
    exit(0);
  }

  if (!connectHost(hostname)) {
  	fprintf(stderr, "Error: connecting server\n");
		exit(0);
  }

  using_history();
	
	char *prompt = (char *)malloc(128 * sizeof(char));
  while (1) {
	  sprintf(prompt, "\n%s:%d[%d]> ", hostname, portno, sid);
    command = readline(prompt);
    if (!strcmp(command, "QUIT"))
      break;
		if (startsWith("HOST", command)) {
			char *token = strtok(command, " ");
			token = strtok(NULL, "");
      if (token == NULL) {
        fprintf(stderr,"ERROR: server address invalid\n");
        continue;
      }
			strcpy(hostname, token);
			if (connectHost(hostname)) printf("OK");
      continue;
		}
    if (startsWith("SESSION", command)) {
      char *token = strtok(command, " ");
      token = strtok(NULL, "");
      if (token == NULL) {
        fprintf(stderr,"ERROR: session ID invalid\n");
        continue;
      }
      strcpy(ID, token);
      lnum = strtol(ID, &end, 10);
      if (end == token) {
        fprintf(stderr,"ERROR: invalid session ID\n");
        continue;
      }
      sid = (int)lnum;
      printf("OK");
      continue;
    }
    sprintf(request, "SESSION %d VGTP/0.1\n %s", sid, command);
    n = write(sockfd, request, strlen(request));
    if (n < 0)
      fprintf(stderr,"ERROR: writing to server");
    add_history(command);
    free(command);
    bzero(response, MAX_BUFFER);
    if (read(sockfd, response, MAX_BUFFER) < 0)
      fprintf(stderr,"ERROR: reading from server");
    printf("%s", response);
  }
  close(sockfd);
  return 0;
}