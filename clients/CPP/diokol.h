/* -*- mode: c; tab-width: 4; indent-tabs-mode: nil; -*- */

/*
* This file is part of p5Display.
*
* Copyright (c) 2014-2015 Armando Arce
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would
*    be appreciated but is not requirepg.
*
* 2. Altered source versions must be plainly marked as such, and must not
*    be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source
*    distribution.
*/

#ifndef _P5D_API_H_
#define _P5D_API_H_ 1

#include <stdio.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdarg.h>
#include <stdbool.h>

#ifdef _WIN32
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501  /* Windows XP. */
  #endif
  #include <winsock2.h>
  #include <Ws2tcpip.h>
  #pragma comment(lib,"ws2_32.lib");
#else
  /* Assume that any non-Windows platform uses POSIX-style sockets insteapg. */
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <sys/types.h>
  #include <netinet/in.h>
  #include <sys/wait.h>
  #include <resolv.h>
  #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
  #include <unistd.h> /* Needed for close() */
  typedef int SOCKET; /* Note: For POSIX, typedef SOCKET as an int. */
  #define INVALID_SOCKET  (SOCKET)(~0)
  #define SOCKET_ERROR            (-1)
#endif
  
namespace p5d {

#define B_CMD memset(buffer,0,DEFAULT_BUFLEN);
#define E_CMD sendCommand(buffer);
#define PFont int
#define PImage int
#define PShape int

class PGraphics {
	
	private:
	
	static const int DEFAULT_BUFLEN = 512;
	std::string DEFAULT_PORT;
	std::string DEFAULT_HOST;
	
	typedef void (*functiontype)();

	functiontype mousePressed__;
	functiontype mouseMoved__;
	functiontype keyPressed__;
	functiontype draw__;
	
	int mousePressedDef;
	int keyPressedDef;
	int mouseMovedDef;
	int drawDef;
	int loopFlag;
	int debug;
	
	static int imgCount;
	static int fntCount;
	static int shpCount;
	const static std::string modes[];
	
	SOCKET ConnectSocket;

	char buffer[DEFAULT_BUFLEN];
	
	void error(std::string msg) {
		printf("%s\n",msg.c_str());
		exit(-1);
	}
	
	int sockInit(void) {
	  #ifdef _WIN32
	    WSADATA wsa_data;
	    return WSAStartup(MAKEWORD(1,1), &wsa_data);
	  #else
	    return 0;
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

	void processResponse(char* buffer, int size) {
		char event [24];
	    int x,y,c;
		if (debug>0) printf("%s", buffer);
		sscanf(buffer, "%s %d %d %d", event, &x, &y, &c);
		if (debug>1) printf("cmd: %s x: %d y: %d c: %d\n",event, x, y, c);
		pmouseX = mouseX; pmouseY = mouseY;
		mouseX = x; mouseY = y; key = c;
		mousePressed = 0;
		if (strcmp(event,"mousePressed")==0&&mousePressedDef) {
			mousePressed__();
			mousePressed = 1;
		} else if (strcmp(event,"mouseMoved")==0&&mouseMovedDef)
			mouseMoved__();
		else if (strcmp(event,"keyPressed")==0&&keyPressedDef)
			keyPressed__();
		if (drawDef) draw__();
	}
	
	void sendCommand(char* sendbuf) {
		int iResult;
		char  recvbuf[128];
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf),0);
	    if (iResult == SOCKET_ERROR) {
	        sockClose(ConnectSocket);
	        sockQuit();
			error("Connection error");
	    }
		iResult = recv(ConnectSocket, recvbuf, 128, 0);
		if ( iResult > 0) {
			if ( debug > 0) printf("%s", recvbuf);
        } else if (iResult == 0)
            error("Connection closed");
        else
            error("Connection error");
	}
	
	void listen__() {
		int iResult;
		char  recvbuf[512];
		while (true) {
		  iResult = recv(ConnectSocket, recvbuf, 512, 0);
		  if ( iResult > 0 )
            processResponse(recvbuf,iResult);
          else if ( iResult == 0 )
           error("Connection closed");
          else
            error("Connection error");
	    }
	}
	
	int nextShpId() {
		return shapeCounter++;
	}
	int nextFntId() {
		return fontCounter++;	
	}
	int nextImgId() {
		return imageCounter++;	
	}
	
	public:
	
	static const float HALF_PI;
	static const float PI;
	static const float QUARTER_PI;
	static const float TAU;
	static const float TWO_PI;
	static const int PIE = 0;
	static const int OPEN = 1;
	static const int CHORD = 2;
	static const int CENTER = 3;
	static const int RADIUS = 4;
	static const int CORNER = 5;
	static const int CORNERS = 6;
	static const int POINTS = 7;
	static const int LINES = 8;
	static const int TRIANGLES = 9;
	static const int TRIANGLE_FAN = 10;
	static const int TRIANGLE_STRIP = 11;
	static const int QUADS = 12;
	static const int QUAD_STRIP = 13;
	static const int POLYGON = 14;
	static const int CLOSE = 15;
	static const int OPEN = 16;
	static const int LEFT = 17;
	static const int RIGHT = 18;
	static const int TOP = 19;
	static const int BOTTOM = 20;
	static const int BASELINE = 21;
	int pmouseX;
	int pmouseY;
	int mouseX;
	int mouseY;
	int posX;
	int posY;
	int key;
	int frameCount;
	int width;
	int height;
	int mousePressed;
	
	PGraphics(int argc=0, char **argv=NULL) {
	  int iResult;
	  struct addrinfo *result = NULL,
	                     *ptr = NULL,
	                     hints;
						 
	  DEFAULT_PORT = "9555";
	  DEFAULT_HOST = "localhost";
	  mousePressedDef=0;
	  keyPressedDef=0;
	  mouseMovedDef=0;
	  drawDef=0;
	  loopFlag=0;
	  debug=2;
	  ConnectSocket = INVALID_SOCKET;
	  sockInit();
	  
	  memset( &hints, 0, sizeof(hints) );
	  hints.ai_family = AF_UNSPEC;
	  hints.ai_socktype = SOCK_STREAM;
	  hints.ai_protocol = IPPROTO_TCP;
	  
	  iResult = getaddrinfo(DEFAULT_HOST.c_str(), DEFAULT_PORT.c_str(), &hints, &result);
      if ( iResult != 0 ) {
          sockQuit();
		  error("Connection failed");
      }
	  
	  for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
		  
		  ConnectSocket = socket(PF_INET, SOCK_STREAM, 0);
		  if (ConnectSocket == INVALID_SOCKET) {
		    sockQuit();
			error("Connection failed\n");
		  }
		  iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		  if (iResult == SOCKET_ERROR) {
		    sockClose(ConnectSocket);
		    ConnectSocket = INVALID_SOCKET;
			//error("Connection failed\n");
		  }
      }
	  
	  if (ConnectSocket == INVALID_SOCKET) {
	    sockQuit();
		error("Unable to connect to p5Display server!\n");
	  }
	  freeaddrinfo(result);
	}
	
	~PGraphics() {
		sockClose(ConnectSocket);
		sockQuit();
	}
	
	void mousePressedFunc(functiontype param) {
	  mousePressed__ = param;
	  mousePressedDef = 1;
	}

	void mouseMovedFunc(functiontype param) {
	  mouseMoved__ = param;
	  mouseMovedDef = 1;
	}

	void keyPressedFunc(functiontype param) {
	  keyPressed__ = param;
	  keyPressedDef = 1;
	}
	
	void drawFunc(functiontype param) {
	  draw__ = param;
	  drawDef = 1;
	}
	
	// Structure
	
	void listen() {
		if (drawDef) 
			draw__();
		listen__();
	}
	
	void loop() {
	  	B_CMD sprintf(buffer,".loop\n"); E_CMD	
    }
	
	void noLoop() {
		B_CMD sprintf(buffer,".noLoop\n"); E_CMD	
	}
	
	void popStyle() {
		B_CMD sprintf(buffer,"popStyle \n"); E_CMD
	}
	
	void pushStyle() {
		B_CMD sprintf(buffer,"pushStyle \n"); E_CMD
	}
	
	void redraw() {
		B_CMD sprintf(buffer,".redraw\n"); E_CMD
	}
	
	// Environment
	
	void debugLevel(int level) {
		debug = level;
	}
	
	void frameRate(int fps) {
		frameCount = fps;
		B_CMD sprintf(buffer,"frameRate %d\n",fps); E_CMD
	}
	
	void noSmooth() {
		B_CMD sprintf(buffer,"noSmooth \n"); E_CMD
	}
	
	void size(int a, int b) {
		width = a; height = b;
		B_CMD sprintf(buffer,"size %d %d\n",a,b); E_CMD
	}
	
	void position(int a, int b) {
		posX = a; posY = b;
		B_CMD sprintf(buffer,"position %d %d\n",a,b); E_CMD
	}
	
	void smooth() {
		B_CMD sprintf(buffer,"smooth\n"); E_CMD
	}
	
	// Shape
	
	int createShape(int kind, ...) {
		int shpId = nextShpId();
		B_CMD sprintf(buffer,"createShape %s %d\n",modes[kind].c_str(),shpId); E_CMD
		return shpId;
	}
	
	void shape(int shpId, float x=0, float y=0, float w=0, float h=0) {
		B_CMD sprintf(buffer,"shape %d %1.0f %1.0f %1.0f %1.0f\n",shpId,x,y,w,h); E_CMD
	}
	
	// Shape - 2D primitives
	
	void arc(float a, float b, float c, float d, float start, float stop) {
		B_CMD sprintf(buffer,"arc %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f\n",a,b,c,d,start,stop); E_CMD
	}
	
	void ellipse(float a, float b, float c, float d) {
		B_CMD sprintf(buffer,"ellipse %1.0f %1.0f %1.0f %1.0f\n",a,b,c,d); E_CMD
	}
	
	void line(float x1, float y1, float x2, float y2) {
		B_CMD sprintf(buffer,"line %1.0f %1.0f %1.0f %1.0f\n",x1,y1,x2,y2); E_CMD
	}
	
	void point(float x, float y) {
		B_CMD sprintf(buffer,"point %1.0f %1.0f\n",x,y); E_CMD
	}
	
	void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
		B_CMD sprintf(buffer,"quad %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f\n",x1,y2,x2,y2,x3,y3,x4,y4); E_CMD	
	}

	void rect(float a, float b, float c, float d) {
		B_CMD sprintf(buffer,"rect %1.0f %1.0f %1.0f %1.0f\n",a,b,c,d); E_CMD
	}
	
	void triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
		B_CMD sprintf(buffer,"triangle %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f\n",x1,y1,x2,y2,x3,y3); E_CMD
	}
	
	// Shape - Curves

	void bezier(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
		B_CMD sprintf(buffer,"bezier %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f\n",x1,y1,x2,y2,x3,y3,x4,y4); E_CMD
	}
	
	void bezierDetail(int detail) {
		B_CMD sprintf(buffer,"bezierDetail %d\n",detail); E_CMD
	}
	
	void curve(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
		B_CMD sprintf(buffer,"curve %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %1.0f %f\n",x1,y1,x2,y2,x3,y3,x4,y4); E_CMD	
	}
	
	// Shape - Attributes
	
	void ellipseMode(int mode) {
		B_CMD sprintf(buffer,"ellipseMode %s \n",modes[mode].c_str()); E_CMD
	}

	void rectMode(int mode) {
		B_CMD sprintf(buffer,"rectMode %s \n",modes[mode].c_str()); E_CMD
	}

	void strokeWeight(float weight) {
		B_CMD sprintf(buffer,"strokeWeight %1.0f\n",weight); E_CMD
	}
	
	// Shape - Vertex
	
	void beginShape(int mode=POLYGON) {
		B_CMD sprintf(buffer,"beginShape %s \n",modes[mode].c_str()); E_CMD
	}
	
	void endShape(int mode=OPEN) {
		B_CMD sprintf(buffer,"endShape %s \n",modes[mode].c_str()); E_CMD
	}
	
	void vertex(float x, float y) {
		B_CMD sprintf(buffer,"vertex %1.0f %1.0f\n",x,y); E_CMD	
	}

	// Transform
	
	void popMatrix() {
		B_CMD sprintf(buffer,"popMatrix \n"); E_CMD	
	}
	
	void pushMatrix() {
		B_CMD sprintf(buffer,"pushMatrix \n"); E_CMD	
	}
	
	void rotate(float a) {
		B_CMD sprintf(buffer,"rotate %1.0f\n",a); E_CMD		
	}
	
	void scale(float s) {
		B_CMD sprintf(buffer,"scale %1.0f\n",s); E_CMD		
	}

	void scale(float x,float y) {
		B_CMD sprintf(buffer,"scale %1.0f %1.0f\n",x,y); E_CMD		
	}
	
	void translate(float x,float y) {
		B_CMD sprintf(buffer,"translate %1.0f %1.0f\n",x,y); E_CMD		
	}
	
	// Color - Setting
	
	void backgroundHex(unsigned int rgb, float alpha=255) {
		B_CMD sprintf(buffer,".background %x %1.0f\n",rgb,alpha); E_CMD
	}

	void background(float gray, float alpha=255) {
		B_CMD sprintf(buffer,".background %1.0f %1.0f\n",gray,alpha); E_CMD
	}
	
	void background(float v1, float v2, float v3, float alpha=255) {
		B_CMD sprintf(buffer,".background %1.0f %1.0f %1.0f %1.0f\n",v1,v2,v3,alpha); E_CMD
	}
		
	void clear() {
		B_CMD sprintf(buffer,".clear \n"); E_CMD
	}
	
	void fillHex(unsigned int rgb, float alpha=255) {
		B_CMD sprintf(buffer,"fill %x %1.0f\n",rgb,alpha); E_CMD
	}
	
	void fill(float gray, float alpha=255) {
		B_CMD sprintf(buffer,"fill %1.0f %1.0f\n",gray,alpha); E_CMD
	}
	
	void fill(float v1, float v2, float v3, float alpha=255) {
		B_CMD sprintf(buffer,"fill %1.0f %1.0f %1.0f %1.0f\n",v1,v2,v3,alpha); E_CMD
	}
	
	void noFill() {
		B_CMD sprintf(buffer,"noFill \n"); E_CMD
	}
	
	void noStroke() {
		B_CMD sprintf(buffer,"noStroke \n"); E_CMD
	}
	
	void strokeHex(unsigned int rgb, float alpha=255) {
		B_CMD sprintf(buffer,"stroke %x %1.0f\n",rgb,alpha); E_CMD
	}
	
	void stroke(float gray, float alpha=255) {
		B_CMD sprintf(buffer,"stroke %1.0f %1.0f\n",gray,alpha); E_CMD
	}
	
	void stroke(float v1, float v2, float v3, float alpha=255) {
		B_CMD sprintf(buffer,"stroke %1.0f %1.0f %1.0f %1.0f\n",v1,v2,v3,alpha); E_CMD
	}
	
	// Image - Loading & Displaying
	
	void image(int imgId, float x=0, float y=0, float w=-1, float h=-1) {
		B_CMD sprintf(buffer,"image %d %1.0f %1.0f %1.0f %1.0f\n",imgId,x,y,w,h); E_CMD
	}
	
	int loadImage(std::string image) {
		int imgId = nextImgId();
		B_CMD sprintf(buffer,"loadImage \"%s\" %d\n",image.c_str(),imgId); E_CMD
		return imgId;
	}
	
	// Image - Rendering
	
	void beginDraw() {
	}
	
	void endDraw() {
	}
	
	// Typography - Loading & Displaying
	
	void text(std::string chars, float x, float y) {
		B_CMD sprintf(buffer,"text \"%s\" %1.0f %1.0f\n",chars.c_str(),x,y); E_CMD
	}
	
	void textSize(float size) {
		B_CMD sprintf(buffer,"textSize %1.0f\n",size); E_CMD
	}
	
	void textAlign(int mode1, int mode2) {
		B_CMD sprintf(buffer,"textAlign %s %s\n",modes[mode1].c_str(),modes[mode2].c_str()); E_CMD
	}
	
	int loadFont(std::string font) {
		int fntId = nextFntId();
		B_CMD sprintf(buffer,"loadFont \"%s\" %d\n",font.c_str(),fntId); E_CMD
		return fntId;
	}
	
	void textFont(int fntId) {
		B_CMD sprintf(buffer,"textFont %d\n",fntId); E_CMD
	}
	
	// Math - Random
	
	int random(int max) { return rand() % max; }
	
	// Math - Calculation
	
	int constrain(int value,int min, int max) {
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}
	
  };
  
  const float PGraphics::HALF_PI = 1.57079632679489661923;
  const float PGraphics::PI = 3.14159265358979323846;
  const float PGraphics::QUARTER_PI = 0.7853982;
  const float PGraphics::TAU = 6.28318530717958647693;
  const float PGraphics::TWO_PI = 6.28318530717958647693;
  int PGraphics::imgCount=1;
  int PGraphics::fntCount=1;
  int PGraphics::shpCount=1;

  const std::string PGraphics::modes[] = {"RADIUS","CENTER","CORNER","CORNERS","PIE","OPEN","CHORD",
"POINTS","LINES","TRIANGLES","TRIANGLE_STRIP","TRIANGLE_FAN","QUADS","QUAD_STRIP","RIGHT","LEFT",
"BASELINE","BOTTOM","TOP","POINT","LINE","TRIANGLE","QUAD","RECT","ELLIPSE","ARC","BOX","SPHERE"};

}

#endif