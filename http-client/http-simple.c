#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501 /* Windows XP. */
#endif
#include <Ws2tcpip.h>
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#if defined _WIN32
#define close(x) closesocket(x)
#endif

void connection(int socket_desc, int c) {
  int client_sock, read_size;
  struct sockaddr_in client;
  char client_message[2000];

  // accept connection from an incoming client
  client_sock =
      accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
  if (client_sock < 0) {
    perror("accept failed");
    return;
  }
  puts("Connection accepted");

  // Receive a message from client
  while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
    // Send the message back to client
    puts(client_message);
    send(client_sock, client_message, strlen(client_message), 0);
  }
  if (read_size == 0) {
    puts("Client disconnected");
    fflush(stdout);
  } else if (read_size == -1) {
    perror("recv failed");
  }
}

int main(int argc, char *argv[]) {
  int socket_desc, c;
  struct sockaddr_in server;
  int portnumber = 8888;
  int queuelen = 3;

#if defined _WIN32
  WSADATA wsa_data;
  WSAStartup(MAKEWORD(1, 1), &wsa_data);
#endif

  // Create socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1) {
    printf("Could not create socket");
  }
  puts("Socket created");

  // Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(portnumber);

  // Bind
  if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
    // print the error message
    perror("bind failed. Error");
    return 1;
  }
  puts("bind done");

  // Listen
  listen(socket_desc, queuelen);

  // Accept and incoming connection
  puts("Waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);
  while (1)
    connection(socket_desc, c);

#if defined _WIN32
  WSACleanup();
#endif
  return 0;
}