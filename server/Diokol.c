#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <lua/lauxlib.h>
#include <lua/lua.h>
#include <lua/lualib.h>

#define MAX_BUFFER 65536
#define MAX_STATES 10

int status, result;
lua_State *L[MAX_STATES];

void *connection_handler(void *);

int main(int argc, char *argv[]) {
  int socket_desc, client_sock, c;
  struct sockaddr_in server, client;

  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1) {
    printf("Could not create socket");
  }
  puts("Socket created");

  bzero(L, MAX_STATES * sizeof(void *));

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(6453);

  if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("bind failed. Error");
    return 1;
  }
  puts("bind done");

  listen(socket_desc, 3);

  puts("Waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);
  pthread_t thread_id;

  while ((client_sock = accept(socket_desc, (struct sockaddr *)&client,
                               (socklen_t *)&c))) {
    puts("Connection accepted");
    if (pthread_create(&thread_id, NULL, connection_handler,
                       (void *)&client_sock) < 0) {
      perror("could not create thread");
      return 1;
    }

    puts("Handler assigned");
  }

  if (client_sock < 0) {
    perror("accept failed");
    return 1;
  }

  return 0;
}

void *connection_handler(void *socket_desc) {
  int sock = *(int *)socket_desc;
  int read_size;
  char message[MAX_BUFFER], request[MAX_BUFFER];
  char *token;
  char session[10];
  long lnum;
  int sid;
  char *end;

  while ((read_size = recv(sock, request, MAX_BUFFER, 0)) > 0) {
    request[read_size] = '\0';
    token = strtok(request, " ");
    if (strcmp(token, "SESSION") != 0 || token == NULL) {
      write(sock, "ERROR: invalid header", 12);
      return NULL;
    }

    token = strtok(NULL, " ");
    if (token == NULL) {
      write(sock, "ERROR: session ID not found", 16);
      return NULL;
    }

    strcpy(session, token);
    lnum = strtol(session, &end, 10);

    if (end == token) {
      write(sock, "ERROR: invalid session ID", 25);
      return NULL;
    }
    sid = (int)lnum;

    if (L[sid] == NULL) {
      L[sid] = luaL_newstate();
      luaL_openlibs(L[sid]);
    }

    token = strtok(NULL, "\n");
    if (strcmp(token, "VGTP/0.1") != 0 || token == NULL) {
      write(sock, "ERROR: invalid protocol", 16);
      return NULL;
    }

    token = strtok(NULL, "");
    strcpy(request, token);

    status = luaL_loadstring(L[sid], request);

    if (status) {
      int n = strlen(lua_tostring(L[sid], -1));
      strcpy(message, lua_tostring(L[sid], -1));
      write(sock, message, n);
      bzero(request, MAX_BUFFER);
      return NULL;
    }

    result = lua_pcall(L[sid], 0, LUA_MULTRET, 0);
    if (result)
      write(sock, lua_tostring(L[sid], -1), strlen(lua_tostring(L[sid], -1)));
    else
      write(sock, "OK", 2);

    bzero(request, MAX_BUFFER);
  }

  if (read_size == 0) {
    puts("Client disconnected");
    fflush(stdout);
  } else if (read_size == -1) {
    perror("recv failed");
  }

  return 0;
}