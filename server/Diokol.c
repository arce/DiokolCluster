#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <ifaddrs.h>

#include <lua/lauxlib.h>
#include <lua/lua.h>
#include <lua/lualib.h>

#include <rmcast/rmcast.h>

#define MAX_BUFFER 65536
#define MAX_STATES 10

int status, result;
lua_State *L[MAX_STATES];

int server_sock, group_sock;
bool multicast = false;

void lookup_host() {
  struct ifaddrs *ifAddrStruct = NULL;
  struct ifaddrs *ifa = NULL;
  void *tmpAddrPtr = NULL;

  getifaddrs(&ifAddrStruct);

  for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
    if (!ifa->ifa_addr) {
      continue;
    }
    if (ifa->ifa_addr->sa_family == AF_INET) {
      tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
      char addressBuffer[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
      printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
    }
  }
  if (ifAddrStruct != NULL)
    freeifaddrs(ifAddrStruct);
}

void execute_command(char *command, int sid, int sock) {

  char message[256];

  if (L[sid] == NULL) {
    L[sid] = luaL_newstate();
    luaL_openlibs(L[sid]);
  }

  int status = luaL_loadstring(L[sid], command);

  if (status) {
    if (!sock) {
      int n = strlen(lua_tostring(L[sid], -1));
      strcpy(message, lua_tostring(L[sid], -1));
      write(sock, message, n);
    }
    return;
  }

  int result = lua_pcall(L[sid], 0, LUA_MULTRET, 0);
  if (!sock) {
    if (result)
      write(sock, lua_tostring(L[sid], -1), strlen(lua_tostring(L[sid], -1)));
    else
      write(sock, "OK", 2);
  }
}

void process_request(char *request, int sock) {

  char *end;
  char command[MAX_BUFFER];
  char session[4];
  long lnum;
  int sid;

  char *token = strtok(request, " ");

  if (strcmp(token, "SESSION") != 0 || token == NULL) {
    if (sock)
      write(sock, "ERROR: invalid header", 12);
    return;
  }

  token = strtok(NULL, " ");
  if (token == NULL) {
    if (sock)
      write(sock, "ERROR: session ID not found", 16);
    return;
  }

  strcpy(session, token);
  lnum = strtol(session, &end, 10);

  if (end == token) {
    if (sock)
      write(sock, "ERROR: invalid session ID", 25);
    return;
  }

  sid = (int)lnum;
  token = strtok(NULL, "\n");

  if (strcmp(token, "VGTP/0.1") != 0 || token == NULL) {
    if (sock)
      write(sock, "ERROR: invalid protocol", 16);
    return;
  }

  token = strtok(NULL, "");
  strcpy(command, token);
  execute_command(command, sid, sock);
}

void resend_request(char *request) {
  RM_sendto(group_sock, request, strlen(request));
}

void *group_handler(void *arg) {

  char request[MAX_BUFFER];
  int n;

  while ((n = RM_recv(group_sock, request, MAX_BUFFER)) > 0) {
    request[n] = '\0';
    process_request(request, 0);
  }

  return 0;
}

void *client_handler(void *socket_desc) {

  int client_sock = *(int *)socket_desc;
  char request[MAX_BUFFER];
  int n;

  while ((n = recv(client_sock, request, MAX_BUFFER, 0)) > 0) {
    request[n] = '\0';
    process_request(request, client_sock);
    if (multicast)
      resend_request(request);
  }

  return 0;
}

void callback_term(void) {
  perror("Diokol exiting ...\n");
  exit(EXIT_SUCCESS);
}

void multicast_initialize() {
  if (!RM_readConfigFile("diokol.config", false)) {
    perror("Couldn't read config file diokol.config\n");
    exit(EXIT_FAILURE);
  }

  RM_initialize((void *)callback_term);

  group_sock =
      RM_joinGroup((char *)RM_USE_CURRENT_CONFIG, RM_USE_CURRENT_CONFIG);
}

void unicast_initialize() {
  struct sockaddr_in server;

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock == -1) {
    perror("Could not create socket");
  }

  bzero(L, MAX_STATES * sizeof(void *));

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(6453);

  if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("bind failed. Error");
    return;
  }

  listen(server_sock, 3);
}

int main(int argc, char *argv[]) {
  int client_sock;
	struct sockaddr_in client;

  unicast_initialize();
  multicast_initialize();
  lookup_host();

  int c = sizeof(struct sockaddr_in);
  pthread_t tid;

  if (pthread_create(&tid, NULL, group_handler, NULL) != 0) {
    perror("Error: group thread failed");
    RM_leaveGroup(group_sock, (char *)RM_USE_CURRENT_CONFIG);
  }

  while ((client_sock = accept(server_sock, (struct sockaddr *)&client,
                               (socklen_t *)&c))) {
    if (pthread_create(&tid, NULL, client_handler, (void *)&client_sock) < 0) {
      perror("Error: client thread failedd");
      return 1;
    }
  }

  if (client_sock < 0) {
    perror("Error: client accept failed");
    return 1;
  }

  return 0;
}