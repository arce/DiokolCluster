/* -*- mode: c; tab-width: 4; indent-tabs-mode: nil; -*- */

/*
 * This file is part of p5Display.
 *
 * Copyright (c) 2014-2022 Armando Arce
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

#include <cstdlib>
#include <cstring>
#include <sstream>

#include <stdarg.h>
#include <stdbool.h>
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

int sockInit(void) {
#ifdef _WIN32
  WSADATA wsa_data;
  return WSAStartup(MAKEWORD(1, 1), &wsa_data);
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
  if (status == 0) {
    status = closesocket(sock);
  }
#else
  status = shutdown(sock, SHUT_RDWR);
  if (status == 0) {
    status = close(sock);
  }
#endif
  return status;
}

using namespace std;
namespace p5d {

#define PFont int
#define PImage int
#define PShape int

class PGraphics {

private:
  std::string DEFAULT_PORT;
  std::string DEFAULT_HOST;

  typedef void (*functiontype)();

  functiontype mousePressed__;
  functiontype mouseMoved__;
  functiontype keyPressed__;
  functiontype draw__;
  functiontype setup__;

  int mousePressedDef;
  int keyPressedDef;
  int mouseMovedDef;
  int drawDef;
  int setupDef;
  int loopFlag;
  int debug;

  stringstream ss;
  int session_id;

  static int imgCounter;
  static int fntCounter;
  static int shpCounter;

  SOCKET ConnectSocket;

  void error(std::string msg) {
    printf("%s\n", msg.c_str());
    exit(-1);
  }

  void processResponse(char *buffer, int size) {
    int event, x, y, c;
    sscanf(buffer, "data: dispatchEvent(%d,%d,%d,%d)", &event, &x, &y, &c);
    pmouseX = mouseX;
    pmouseY = mouseY;
    mouseX = x;
    mouseY = y;
    key = c;
    mousePressed = 0;
    if (event == 2 && mousePressedDef) {
      mousePressed__();
      mousePressed = 1;
    } else if (event == 1 && mouseMovedDef)
      mouseMoved__();
    else if (event == 5 && keyPressedDef)
      keyPressed__();
    if (drawDef) {
      ss << "function draw() ";
      draw__();
      ss << "end ";
      sendCommand();
    }
  }

  void sendCommand() {
    int iResult;
    ss << "GET /" << session_id << endl;
    ss << "Accept: text/event-stream" << endl;
    ss << "Cache-Control: no-cache" << endl;
    ss << "Connection: keep-alive" << endl;
    // ss << "Last-Event-ID: " << last_id << endl;
    iResult = send(ConnectSocket, ss.str().c_str(), ss.tellp(), 0);
    if (iResult == SOCKET_ERROR) {
      sockClose(ConnectSocket);
      sockQuit();
      error("Connection error");
    }
    stringstream().swap(ss);
  }

  void listen__() {
    int iResult;
    char recvbuf[1024];
    while (true) {
      iResult = recv(ConnectSocket, recvbuf, 1024, 0);
      if (iResult > 0) {
        processResponse(recvbuf, iResult);
      } else if (iResult == 0)
        error("Connection closed");
      else
        error("Connection error");
    }
  }

  int nextShpId() { return shpCounter++; }
  int nextFntId() { return fntCounter++; }
  int nextImgId() { return imgCounter++; }

public:
  static const double HALF_PI;
  static const double PI;
  static const double QUARTER_PI;
  static const double TAU;
  static const double TWO_PI;
  static const string PIE;
  static const string OPEN;
  static const string CHORD;
  static const string CENTER;
  static const string RADIUS;
  static const string CORNER;
  static const string CORNERS;
  static const string POINTS;
  static const string LINES;
  static const string TRIANGLES;
  static const string TRIANGLE_FAN;
  static const string TRIANGLE_STRIP;
  static const string QUADS;
  static const string QUAD_STRIP;
  static const string POLYGON;
  static const string CLOSE;
  static const string LEFT;
  static const string RIGHT;
  static const string TOP;
  static const string BOTTOM;
  static const string BASELINE;
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

  PGraphics(const int session = 0, const char host[] = "localhost",
            const char port[] = "8888") {
    int iResult;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    mousePressedDef = 0;
    keyPressedDef = 0;
    mouseMovedDef = 0;
    drawDef = 0;
    setupDef = 0;
    loopFlag = 0;
    debug = 2;
    ConnectSocket = INVALID_SOCKET;
    session_id = session;
    sockInit();

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(host, port, &hints, &result);
    if (iResult != 0) {
      sockQuit();
      error("Connection failed");
    }

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

      ConnectSocket = socket(PF_INET, SOCK_STREAM, 0);
      if (ConnectSocket == INVALID_SOCKET) {
        sockQuit();
        error("Connection failed\n");
      }
      iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
      if (iResult == SOCKET_ERROR) {
        sockClose(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        // error("Connection failed\n");
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

  void setupFunc(functiontype param) {
    setup__ = param;
    setupDef = 1;
  }

  // Structure

  void listen() {
    if (setupDef) {
      ss << "function setup() ";
      setup__();
      ss << "end ";
    }
    if (drawDef) {
      ss << "function draw() ";
      draw__();
      ss << "end ";
    }
    sendCommand();
    listen__();
  }

  void loop() { ss << "loop() "; }

  void noLoop() { ss << "noLoop() "; }

  void popStyle() { ss << "popStyle() "; }

  void pushStyle() { ss << "pushStyle() "; }

  // Environment

  void debugLevel(int level) { debug = level; }

  void frameRate(int fps) {
    frameCount = fps;
    ss << "frameRate(" << fps << ") ";
  }

  void noSmooth() { ss << "noSmooth() "; }

  void size(int a, int b) {
    width = a;
    height = b;
    ss << "size(" << a << "," << b << ") ";
  }

  void smooth() { ss << "smooth() "; }

  // Shape

  int createShape(int kind, ...) {
    int shpId = nextShpId();
    ss << "createShape(" << kind << "," << shpId << ") ";
    return shpId;
  }

  void shape(int shpId, double x = 0, double y = 0, double w = 0,
             double h = 0) {
    ss << "shape(" << shpId << "," << x << "," << y << "," << w << "," << h
       << ") ";
  }

  // Shape - 2D primitives

  void arc(double a, double b, double c, double d, double start, double stop) {
    ss << "arc(" << a << "," << b << "," << c << "," << d << "," << start << ","
       << stop << ") ";
  }

  void arcM(double a, double b, double c, double d, double start, double stop,
            string mode) {
    ss << "arc(" << a << "," << b << "," << c << "," << d << "," << start << ","
       << stop << "," << mode << ") ";
  }

  void ellipse(double a, double b, double c, double d) {
    ss << "ellipse(" << a << "," << b << "," << c << "," << d << ") ";
  }

  void line(double x1, double y1, double x2, double y2) {
    ss << "line(" << x1 << "," << y1 << "," << x2 << "," << y2 << ") ";
  }

  void point(double x, double y) { ss << "point(" << x << "," << y << ") "; }

  void quad(double x1, double y1, double x2, double y2, double x3, double y3,
            double x4, double y4) {
    ss << "quad(" << x1 << "," << y2 << "," << x2 << "," << y2 << "," << x3
       << "," << y3 << "," << x4 << "," << y4 << ") ";
  }

  void rect(double a, double b, double c, double d) {
    ss << "rect(" << a << "," << b << "," << c << "," << d << ") ";
  }

  void triangle(double x1, double y1, double x2, double y2, double x3,
                double y3) {
    ss << "triangle(" << x1 << "," << y1 << "," << x2 << "," << y2 << "," << x3
       << "," << y3 << ") ";
  }

  // Shape - Curves

  void bezier(double x1, double y1, double x2, double y2, double x3, double y3,
              double x4, double y4) {
    ss << "bezier(" << x1 << "," << y1 << "," << x2 << "," << y2 << "," << x3
       << "," << y3 << "," << x4 << "," << y4 << ") ";
  }

  void bezierDetail(int detail) { ss << "bezierDetail(" << detail << ") "; }

  void curve(double x1, double y1, double x2, double y2, double x3, double y3,
             double x4, double y4) {
    ss << "curve(" << x1 << "," << y1 << "," << x2 << "," << y2 << "," << x3
       << "," << y3 << "," << x4 << "," << y4 << ") ";
  }

  // Shape - Attributes

  void ellipseMode(string mode) { ss << "ellipseMode(" << mode << ") "; }

  void rectMode(string mode) { ss << "rectMode(" << mode << ") "; }

  void strokeWeight(double weight) { ss << "strokeWeight(" << weight << ") "; }

  // Shape - Vertex

  void beginShape(string mode = "POLYGON") {
    ss << "beginShape(" << mode << ") ";
  }

  void endShape(string mode = "OPEN") { ss << "endShape(" << mode << ") "; }

  void vertex(double x, double y) { ss << "vertex(" << x << "," << y << ") "; }

  // Transform

  void popMatrix() { ss << "popMatrix() "; }

  void pushMatrix() { ss << "pushMatrix() "; }

  void rotate(double a) { ss << "rotate(" << a << ") "; }

  void scale(double s) { ss << "scale" << s << ") "; }

  void scale(double x, double y) { ss << "scale(" << x << "," << y << ") "; }

  void translate(double x, double y) {
    ss << "translate(" << x << "," << y << ") ";
  }

  // Color - Setting

  void backgroundHex(unsigned int rgb, double alpha = 255) {
    ss << "background(" << rgb << "," << alpha << ") ";
  }

  void background(double gray, double alpha = 255) {
    ss << "background(" << gray << "," << alpha << ") ";
  }

  void background(double v1, double v2, double v3, double alpha = 255) {
    ss << "background(" << v1 << "," << v2 << "," << v2 << "," << alpha << ") ";
  }

  void fillHex(unsigned int rgb, double alpha = 255) {
    ss << "fill(" << rgb << "," << alpha << ") ";
  }

  void fill(double gray, double alpha = 255) {
    ss << "fill(" << gray << "," << alpha << ") ";
  }

  void fill(double v1, double v2, double v3, double alpha = 255) {
    ss << "fill(" << v1 << "," << v2 << "," << v3 << "," << alpha << ") ";
  }

  void noFill() { ss << "noFill() "; }

  void noStroke() { ss << "noStroke() "; }

  void strokeHex(unsigned int rgb, double alpha = 255) {
    ss << "stroke(" << rgb << "," << alpha << ") ";
  }

  void stroke(double gray, double alpha = 255) {
    ss << "stroke(" << gray << "," << alpha << ") ";
  }

  void stroke(double v1, double v2, double v3, double alpha = 255) {
    ss << "stroke(" << v1 << "," << v2 << "," << v3 << "," << alpha << ") ";
  }

  // Image - Loading & Displaying

  void image(int imgId, double x = 0, double y = 0, double w = -1,
             double h = -1) {
    ss << "image(" << imgId << "," << x << "," << y << "," << w << "," << h
       << ") ";
  }

  int loadImage(string image) {
    int imgId = nextImgId();
    ss << "loadImage(" << image << "," << imgId << ") ";
    return imgId;
  }

  // Typography - Loading & Displaying

  void text(string chars, double x, double y) {
    ss << "text(" << chars << x << "," << y << ") ";
  }

  void textSize(double size) { ss << "textSize(" << size << ") "; }

  void textAlign(int mode1, int mode2) {
    ss << "textAlign(" << mode1 << "," << mode2 << ") ";
  }

  int loadFont(string font) {
    int fntId = nextFntId();
    ss << "loadFont(" << font << "," << fntId << ") ";
    return fntId;
  }

  void textFont(int fntId) { ss << "textFont(" << fntId << ") "; }

  // Math - Random

  int random(int max) { return rand() % max; }

  // Math - Calculation

  int constrain(int value, int min, int max) {
    if (value < min)
      return min;
    if (value > max)
      return max;
    return value;
  }
};

const double PGraphics::HALF_PI = 1.57079632679489661923;
const double PGraphics::PI = 3.14159265358979323846;
const double PGraphics::QUARTER_PI = 0.7853982;
const double PGraphics::TAU = 6.28318530717958647693;
const double PGraphics::TWO_PI = 6.28318530717958647693;
int PGraphics::imgCounter = 1;
int PGraphics::fntCounter = 1;
int PGraphics::shpCounter = 1;
const string PGraphics::PIE = "PIE";
const string PGraphics::OPEN = "OPEN";
const string PGraphics::CHORD = "CHORD";
const string PGraphics::CENTER = "CENTER";
const string PGraphics::RADIUS = "RADIUS";
const string PGraphics::CORNER = "CORNER";
const string PGraphics::CORNERS = "CORNERS";
const string PGraphics::POINTS = "POINTS";
const string PGraphics::LINES = "LINES";
const string PGraphics::TRIANGLES = "TRIANGLES";
const string PGraphics::TRIANGLE_FAN = "TRIANGLE_FAN";
const string PGraphics::TRIANGLE_STRIP = "TRIANGLE_STRIP";
const string PGraphics::QUADS = "QUADS";
const string PGraphics::QUAD_STRIP = "QUAD_STRIP";
const string PGraphics::POLYGON = "POLYGON";
const string PGraphics::CLOSE = "CLOSE";
const string PGraphics::LEFT = "LEFT";
const string PGraphics::RIGHT = "RIGHT";
const string PGraphics::TOP = "TOP";
const string PGraphics::BOTTOM = "BOTTOM";
const string PGraphics::BASELINE = "BASELINE";

} // namespace p5d

#endif