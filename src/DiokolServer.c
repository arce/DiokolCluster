#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "p5parser.h"
#include "p5lib.h"
#include "ini/ini.h"

#ifdef _WIN32
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501  /* Windows XP. */
  #endif
  #include <winsock2.h>
  #include <Ws2tcpip.h>
  #pragma comment(lib,"ws2_32.lib");
#else
  /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <sys/types.h>
  #include <netinet/in.h>
  #include <sys/wait.h>
  #include <sys/ioctl.h>
  #include <resolv.h>
  #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
  #include <unistd.h> /* Needed for close() */
  typedef int SOCKET; /* Note: For POSIX, typedef SOCKET as an int. */
#endif

typedef struct {
    int width;
  	int height;
  	int x;
  	int y;
    const char* title;
    int fullscreen;
	int framerate;
	int port;
} configuration;
  
int sockInit(void) {
  #ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1,1), &wsa_data);
  #else
    return 0;
  #endif
}

int sockIoctl(SOCKET sock, unsigned long mode, int flags) {
  long param = flags;
  #ifdef _WIN32
    return ioctlsocket(sock, mode, (char *)&param);
  #else
	return ioctl(sock, mode, (char *)&param);
  #endif
}

int sockQuit(void) {
  #ifdef _WIN32
    return WSACleanup();
  #else
    return 0;
  #endif
}

int sockClose(SOCKET sock) {
  int status = 0;
  #ifdef _WIN32
    status = shutdown(sock, SD_BOTH);
    if (status == 0) { status = closesocket(sock); }
  #else
    status = shutdown(sock, SHUT_RDWR);
    if (status == 0) { status = close(sock); }
  #endif
  return status;
}

void PANIC(char* msg);
#define PANIC(msg)  { perror(msg); exit(-1); }

struct sockaddr_in addr;
int server;
configuration config;
int _event;

typedef struct View {
  AList *displayList;
  Context *ctx;
  int sockId;
} View;

int viewFocus;

AList * views;
AQueue * events;

View *view_new() {
    View *v;
    v = malloc(sizeof(View));
	memset(v,0,sizeof(View));
	v->displayList = list_new(100);
	v->ctx = ctx_new();
    return v;
}

void view_free(View *v) {
	list_free(v->displayList);
	ctx_free(v->ctx);
	free(v);
}

void setView(int id) {
}

int getView() {
  return 0;
}

int viewCreate() {
  return -1;	
}

void viewDestroy() {
}

void viewSize(int w, int h) {
  ctx->w = w;
  ctx->h = h;
}

void viewPosition(int x, int y) {
  ctx->x = x;
  ctx->y = y;
}

void execCmmds(View *view) {
  AList *displayList = view->displayList;
  int length = list_length(displayList);
  for (int i=0;i<length;i++)
	execCmmd(displayList->listArray[i]);
}

void listenClient(View *view) {
  const size_t str_size = 10240;
  char str[10240];
  int bytes_read;
  char *line;
  char *token;
  char buf[256];
  
  while((bytes_read = recv(view->sockId,str,str_size,0))>0) {
    if (bytes_read<5) return;
    str[bytes_read]='\0';
    for (line = strtok (str, "\n"); line != NULL;
         line = strtok (line + strlen (line) + 1, "\n")) {
	  strncpy (buf, line, sizeof (buf));
	  appendCmmd(view->displayList,buf,view->ctx);
    }
  }
  if (bytes_read==0) {
	printf("Connection closed\n");
  	int pos = list_find(views,view);
  	list_moveToPos(views,pos);
  	list_remove(views);

  	sockClose(view->sockId);
  	view_free(view);
	p5_frameRate(config.framerate);
  }
}

void listenClients() {
  View *view;
  int length = list_length(views);
  for (int i=0;i<length;i++) {
  	view = views->listArray[i];
    listenClient(view);
  }
}

void acceptClient() {
  int addr_size = sizeof(addr);
  SOCKET client = accept(server, (struct sockaddr*)&addr, &addr_size);
  //if (client==EAGAIN||client==EWOULDBLOCK) return;
  if (client==-1) return;
  if (sockIoctl(client,FIONBIO,1)) {
      printf("ioctl FIONREAD call failed\n");
	  exit(-1);
  }
  printf("Connected: %s:%d\n",
	    inet_ntoa(addr.sin_addr),
	    ntohs(addr.sin_port));
  View *view = view_new();
  view->sockId = client;
  list_append(views,view);
}

void idleServer() {
  acceptClient();
  if (list_length(views)==0) return;
  listenClients();
  if (_event) return;
  char message[20];
  memset(message,0,20);
  View *view;
  sprintf(message, "idleEvent %d\n",p5_frameCount);
  int length = list_length(views);
  for (int i=0;i<length;i++) {
    view = views->listArray[i];
  	Context *ctx = view->ctx;
	send(view->sockId,message,strlen(message),0);
  }
}
	
void mousePressedServer() {
  if (list_length(views)==0) return;
  char message[40];
  memset(message,0,40);
  View *view;
  int length = list_length(views);
  for (int i=0;i<length;i++) {
    view = views->listArray[i];
  	Context *ctx = view->ctx;
    if ((ctx->x <= p5_mouseX && p5_mouseX <= ctx->x+ctx->w && 
  		 ctx->y <= p5_mouseY && p5_mouseY <= ctx->y+ctx->h )) {
  	  viewFocus = i;
	  sprintf(message, "mousePressed %d %d %d %d\n", p5_mouseX,
	          p5_mouseY,p5_mouseButton,p5_mouseState);
	  send(view->sockId,message,strlen(message),0);
  	}
  }
}

void mouseMovedServer() {
  if (list_length(views)==0) return;
  char message[30];
  memset(message,0,30);
  View *view = views->listArray[viewFocus];
  Context *ctx = view->ctx;
  if ((ctx->x <= p5_mouseX && p5_mouseX <= ctx->x+ctx->w && 
		 ctx->y <= p5_mouseY && p5_mouseY <= ctx->y+ctx->h )) {
	sprintf(message, "mouseMoved %d %d\n", p5_mouseX, p5_mouseY);
	send(view->sockId,message,strlen(message),0);
  }
}

void keyPressedServer() {
  if (list_length(views)==0) return;
  char message[20];
  memset(message,0,20);
  View *view = views->listArray[viewFocus];
  Context *ctx = view->ctx;
  sprintf(message, "keyPressed %d\n", p5_key);
  send(view->sockId,message,strlen(message),0);
}

void drawServer() {
  glEnable(GL_SCISSOR_TEST);
  View *view;
  int length = list_length(views);
  for (int i=0;i<length;i++) {
	view = views->listArray[i];
	ctx = view->ctx;
	p5_strokeWeight(1);
	p5_rectMode(P5_CORNER);
	p5_ellipseMode(P5_CENTER);
	p5_noSmooth();
	glLoadIdentity();
	glTranslated(ctx->x,ctx->y,0);
	glScissor(ctx->x,p5_height-ctx->h-ctx->y,ctx->w,ctx->h);
    execCmmds(view);
  }
  glDisable(GL_SCISSOR_TEST);
}

void setupServer() {
  if (config.fullscreen)
    glutFullScreen();
  p5_size(config.width,config.height);
  p5_position(config.x,config.y);
  p5_frameRate(config.framerate);
  p5_loop();
}

static int handler(void* user, const char* section, const char* name,
                   const char* value) {
    configuration* pconfig = (configuration*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("window", "width")) {
        pconfig->width = atoi(value);
    } else if (MATCH("window", "height")) {
        pconfig->height = atoi(value);
    } else if (MATCH("window", "x")) {
        pconfig->x = atoi(value);
    } else if (MATCH("window", "y")) {
        pconfig->y = atoi(value);
    } else if (MATCH("window", "title")) {
        pconfig->title = strdup(value);
    } else if (MATCH("window", "fullscreen")) {
        pconfig->fullscreen = atoi(value);
    } else if (MATCH("window", "framerate")) {
        pconfig->framerate = atoi(value);
    } else if (MATCH("window", "port")) {
        pconfig->port = atoi(value);
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

int main(int argc, char *argv[]) {

  if (ini_parse("p5DisplayServer.ini", handler, &config) < 0) {
    printf("Can't load 'p5DisplayServer.ini'\n");
    return 1;
  }
  
  _debug = 0;
  views = list_new(10);
  events = queue_new(100);

  sockInit();
  if ( (server = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
    PANIC("Socket");
  if (sockIoctl(server,FIONBIO,1)) {
      printf("ioctl FIONBIO call failed\n");
	  exit(-1);
  }
  addr.sin_family = AF_INET;
  addr.sin_port = htons(config.port);
  addr.sin_addr.s_addr = INADDR_ANY;
  if ( bind(server, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
    PANIC("Bind");
  if ( listen(server, 20) != 0 )
    PANIC("Listen");

  p5_init(argc,argv);

  p5_mousePressedFunc(mousePressedServer);
  p5_mouseMovedFunc(mouseMovedServer);
  p5_keyPressedFunc(keyPressedServer);
  p5_setupFunc(setupServer);
  p5_drawFunc(drawServer);
  p5_idleFunc(idleServer);

  p5_createWindow(config.title);
  
  p5_mainLoop();
  
  sockClose(server);
  sockQuit();
  return 0;
}
