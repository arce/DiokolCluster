/*
 * diokol-cli.c - Diokol command line interface
 * usage: diokol-cli <session> <host> <port>
 */
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <readline/history.h>
#include <readline/readline.h>

#include <rmcast/rmcast.h>

#define MAX_BUFFER 65536
int sockfd = 0, portno = 6453, n, session = 0;
struct sockaddr_in serveraddr;
struct hostent *server;
char *hostname = "127.0.0.1";
bool multicast = false;
pthread_t tid;

int cliSock;

int startsWith(const char *pre, const char *str) {
  size_t lenpre = strlen(pre), lenstr = strlen(str);
  return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}

void callback_term(void) {
  fprintf(stderr, "rmchat exiting ...\n");
  exit(EXIT_SUCCESS);
}

int connectMultiHost() {

  if (!RM_readConfigFile("diokol.config", false)) {
    fprintf(stderr, "Error: Couldn't read config file diokol.config\n");
    exit(EXIT_FAILURE);
  }

  RM_initialize((void *)callback_term);

  sockfd = RM_joinGroup((char *)RM_USE_CURRENT_CONFIG, RM_USE_CURRENT_CONFIG);

  return 1;
}

#define BUFFSIZE 200
int end = 0;

void *ReceivePacket(void *arg) {
	
  char receive_buffer[BUFFSIZE];
  int bytes_read;

  while (!end) {
		if (!multicast||sockfd==0) continue;
    if ((bytes_read = RM_recv(sockfd, receive_buffer, BUFFSIZE)) > 0) {
      /* We have received data from the network, show it to the user */
      fprintf(stdout, "\n%s>", receive_buffer);
      fflush(stdout);
    } else {
      fprintf(stderr, "[ReceivePacket Error]: receiving data.\n");
      break;
    }
  }

  return 0;
}

int connectHost(char *hostname) {
  if (sockfd != 0) {
    if (multicast)
      RM_leaveGroup(sockfd, (char *)RM_USE_CURRENT_CONFIG);
    else
      close(sockfd);
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    fprintf(stderr, "ERROR: connecting server");
    return 0;
  }

  server = gethostbyname(hostname);
  if (server == NULL) {
    fprintf(stderr, "ERROR: no such host as %s\n", hostname);
    return 0;
  }

  bzero((char *)&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr,
        server->h_length);
  serveraddr.sin_port = htons(portno);

  if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
    fprintf(stderr, "ERROR: connecting server");
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
  tid = 0;

  if (pthread_create(&tid, NULL, ReceivePacket, NULL) != 0) {
    /* Error, terminate the application */
    fprintf(stderr, "[rmchat Error]: Could not create Receive Thread\n");
    RM_leaveGroup(sockfd, (char *)RM_USE_CURRENT_CONFIG);
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
        fprintf(stderr, "ERROR: server address invalid\n");
        continue;
      }
      strcpy(hostname, token);
      if (connectHost(hostname))
        printf("OK");
      multicast = false;
      continue;
    }
    if (strcpy("MULTIHOST", command) == 0) {
      if (connectMultiHost())
        printf("OK");
      multicast = true;
      continue;
    }
    if (startsWith("SESSION", command)) {
      char *token = strtok(command, " ");
      token = strtok(NULL, "");
      if (token == NULL) {
        fprintf(stderr, "ERROR: session ID invalid\n");
        continue;
      }
      strcpy(ID, token);
      lnum = strtol(ID, &end, 10);
      if (end == token) {
        fprintf(stderr, "ERROR: invalid session ID\n");
        continue;
      }
      sid = (int)lnum;
      printf("OK");
      continue;
    }
    sprintf(request, "SESSION %d VGTP/0.1\n %s", sid, command);
    if (sockfd != 0) {
      if (multicast)
        RM_sendto(sockfd, request, strlen(request));
      else {
        n = write(sockfd, request, strlen(request));
        if (n < 0)
          fprintf(stderr, "ERROR: writing to server");
      }
      bzero(response, MAX_BUFFER);
      if (!multicast) {
        if (read(sockfd, response, MAX_BUFFER) < 0)
          fprintf(stderr, "ERROR: reading from server");
        printf("%s", response);
      } else
        printf("OK");
      add_history(command);
      free(command);
    }
  }
  close(sockfd);
  return 0;
}