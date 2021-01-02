#ifndef _P5PARSER_H_
#define _P5PARSER_H_ 1

#include "p5lib.h"
#include "datastruc/arraylist.h"
#include "datastruc/arrayqueue.h"

#define CMMD_MAX 41
#define SETUP_MAX 47
#define ARRAY_SIZE 60

#define NONE -401
#define ARC 0
#define ELLIPSE 1
#define ELLIPSE_MODE 2
#define QUAD 3
#define RECT 4
#define RECT_MODE 5
#define LINE 6
#define POINT 7
#define TRIANGLE 8
#define BEZIER 9
#define BEZIER_DETAIL 10
#define CURVE 11
#define BACKGROUND 12
#define NO_FILL 13
#define FILL 14
#define NO_STROKE 15
#define STROKE 16
#define PUSH_STYLE 17
#define POP_STYLE 18
#define RESET_MATRIX 19
#define PUSH_MATRIX 20
#define POP_MATRIX 21
#define TRANSLATE 22
#define ROTATE 23
#define SCALE_XY 24
#define SCALE 25
#define SMOOTH 26
#define NO_SMOOTH 27
#define STROKE_CAP 28
#define STROKE_JOIN 29
#define STROKE_WEIGHT 30
#define TEXT_ALIGN 31
#define TEXT_SIZE 32
#define TEXT_FONT 33
#define TEXT 34
#define BEGIN_SHAPE 35
#define VERTEX 36
#define END_SHAPE 37
#define IMAGE 38
#define SHAPE 39
#define IMAGE_MODE 40
#define REDRAW 41

#define LOOP 42
#define NO_LOOP 43
#define FRAME_RATE 44
#define LOAD_IMAGE 45
#define LOAD_FONT 46
#define CREATE_SHAPE 47
 
#define SIZE 48
#define POSITION 49
#define TITLE 50
#define CLEAR 51
#define ADD_MODE 52
#define REMOVE 53
#define MOVE_START 54
#define MOVE_END 55
#define PREV 56
#define NEXT 57
#define MOVE_TO 58
#define BACKGROUND_ 59

typedef struct Cmmd_s {
  int code;
  float *params;
  int size;
  char *text;
  bool intParams;
} Cmmd;

Cmmd *cmmd_make(int code,float *params,int size,char *text,bool intParams) {
  Cmmd *c;
  c = malloc(sizeof(Cmmd));
  c->code = code;
  c->text = text;
  c->size = size;
  c->params = malloc(sizeof(int)*size);
  for (int i=0;i<size;i++)
	  c->params[i] = params[i];
  c->intParams = intParams;
  return c;
}

char *cmmdArray[] = {"arc","ellipse","ellipseMode","quad","rect","rectMode","line","point",
 "triangle","bezier","bezierDetail","curve","background", "noFill","fill","noStroke","stroke",
 "pushStyle","popStyle","resetMatrix","pushMatrix","popMatrix","translate","rotate","scaleXY",
 "scale","smooth","noSmooth","strokeCap","strokeJoin","strokeWeight","textAlign","textSize",
 "textFont","text","beginShape","vertex","endShape","image","shape","imageMode","redraw","loop",
 "noLoop","frameRate","loadImage","loadFont","createShape",".size",".position",".title",
 ".clear",".addMode",".remove",".moveStart",".moveEnd",".prev",".next",".moveTo",".background"};

char *constArray[] = {"OPEN","CLOSE","CENTER","CORNER","CORNERS","RADIUS","LEFT","RIGHT",
 "TOP","BOTTOM","CHORD","PIE","SQUARE","PROJECT","ROUND","MITER","BEVEL"};

char *eventArray[] = {"mousePressed","mouseMoved","keyPressed","idleEvent"};

int arraySize(char* array) {
	return (sizeof array / sizeof array[0]);
} 

int commandLookup(char *command) {
  for (int i=0; i<ARRAY_SIZE; i++)
    if (strcmp(cmmdArray[i],command)==0)
	  return i;
  return NONE;
}

void constantLookup(char *constant) {
  for (int i=0; i<arraySize(constArray); i++)
    if (strcmp(constArray[i],constant)==0) {
		sprintf(constant,"%d",i);
    	break;
    }
}

int execMetaCmmd(AList *displayList,Cmmd *cmmd,Context *ctx) {
float *params = cmmd->params;
switch (cmmd->code) {
  	case (SIZE):
  	  ctx->w = params[0]; ctx->h = params[1];
  	  break;
    case (POSITION):
      ctx->x = params[0]; ctx->y = params[1];
      break;
	case (CLEAR):
	  return list_clear(displayList);
	case (ADD_MODE):
	  return list_setAddMode(displayList,params[0]);
	case (REMOVE):
	  return list_remove(displayList);
    case (MOVE_START):
	  return list_moveToStart(displayList);
    case (MOVE_END):
	  return list_moveToEnd(displayList);
  	case (PREV):
	  return list_prev(displayList);
	case (NEXT):
	  return list_next(displayList);
	case (MOVE_TO):
	  return list_moveToPos(displayList,params[0]);
  	case (BACKGROUND_):
	  list_clear(displayList);
	  cmmd->code = BACKGROUND;
  	  return list_add(displayList,cmmd);
	case (LOAD_IMAGE):
	  p5_loadImage(cmmd->text,params[0],ctx);
	  break;
	case (LOAD_FONT):
	  p5_loadFont(cmmd->text,params[0],ctx);
	  break;
	case (CREATE_SHAPE):
	  p5_createShape(cmmd->text,params,ctx);
	  break;
	case (LOOP):
	  p5_loop();
	  break;
	case (NO_LOOP):
	  p5_noLoop();
	  break;
	case (REDRAW):
	  p5_redraw();
	  break;
	case (FRAME_RATE):
	  p5_frameRate(params[0]);
	  break;
	default:
	  return -1;
  }
  return 0;
}

int execCmmd(Cmmd *cmmd) {
float *params = cmmd->params;
switch (cmmd->code) {
  case (ARC):
    p5_arc(params[0],params[1],params[2],
	       params[3],params[4],params[5],params[6]);
    break;
  case (ELLIPSE):
    p5_ellipse(params[0],params[1],params[2],params[3]);
    break;
  case (ELLIPSE_MODE):
    p5_ellipseMode(params[0]);
    break;
  case (QUAD):
    p5_quad(params[0],params[1],params[2],params[3],
	        params[4],params[5],params[6],params[7]);
  	break;
  case (RECT):
	p5_rect(params[0],params[1],params[2],params[3]);
	break;
  case (RECT_MODE):
    p5_rectMode(params[0]);
    break;
  case (LINE):
    p5_line(params[0],params[1],params[2],params[3]);
    break;
  case (POINT):
    p5_point(params[0],params[1]);
    break;
  case (TRIANGLE):
    p5_triangle(params[0],params[1],params[2],
                params[3],params[4],params[5]);
    break;
  case (BEZIER):
    p5_bezier(params[0],params[1],params[2],params[3],
              params[4],params[5],params[6],params[7]);
    break;
  case (BEZIER_DETAIL):
    p5_bezierDetail(params[0]);
    break;
  case (CURVE):
    p5_curve(params[0],params[1],params[2],params[3],
                  params[4],params[5],params[6],params[7]);
    break;
  case (BACKGROUND):
    if (cmmd->size==1)
      if (cmmd->intParams)
        p5_backgroundH(params[0]);
      else
        p5_background(params[0]);
    else if (cmmd->size==2)
      if (cmmd->intParams)
        p5_backgroundHA(params[0],params[1]);
      else
      p5_backgroundA(params[0],params[1]);
    else if (cmmd->size==3)
      p5_backgroundRGB(params[0],params[1],params[2]);
    else if (cmmd->size==4)
      p5_backgroundRGBA(params[0],params[1],params[2],params[3]);
    break;
  case (NO_FILL):
    p5_noFill();
    break;
  case (FILL):
    if (cmmd->size==1)
      if (cmmd->intParams)
        p5_fillH(params[0]);
      else
        p5_fill(params[0]);
    else if (cmmd->size==2)
      if (cmmd->intParams)
        p5_fillHA(params[0],params[1]);
      else
	    p5_fillA(params[0],params[1]);
	else if (cmmd->size==3)
	  p5_fillRGB(params[0],params[1],params[2]);
	else if (cmmd->size==4)
	  p5_fillRGBA(params[0],params[1],params[2],params[3]);
    break;
  case (NO_STROKE):
    p5_noStroke();
    break;
  case (STROKE):
    if (cmmd->size==1)
      if (cmmd->intParams)
        p5_strokeH(params[0]);
	  else
		p5_stroke(params[0]);
	else if (cmmd->size==2)
	  if (cmmd->intParams)
	    p5_strokeHA(params[0],params[1]);
	  else
		p5_strokeA(params[0],params[1]);
	else if (cmmd->size==3)
	  p5_strokeRGB(params[0],params[1],params[2]);
	else if (cmmd->size==4)
	  p5_strokeRGBA(params[0],params[1],params[2],params[3]);
    break;
  case (RESET_MATRIX):
    p5_resetMatrix();
    break;
  case (PUSH_MATRIX):
    p5_pushMatrix();
    break;
  case (POP_MATRIX):
    p5_popMatrix();
    break;
  case (TRANSLATE):
    p5_translate(params[0],params[1]);
    break;
  case (ROTATE):
    p5_rotate(params[0]);
    break;
  case (SCALE_XY):
    p5_scaleXY(params[0],params[1]);
    break;
  case (SCALE):
    p5_scale(params[0]);
    break;
  case (SMOOTH):
    p5_smooth();
    break;
  case (NO_SMOOTH):
    p5_smooth();
    break;
  case (STROKE_CAP):
    p5_strokeCap(params[0]);
    break;
  case (STROKE_JOIN):
    p5_strokeJoin(params[0]);
    break;
  case (STROKE_WEIGHT):
    p5_strokeWeight(params[0]);
    break;
  case (TEXT_ALIGN):
    p5_textAlign(params[0]);
  	break;
  case (TEXT_SIZE):
    p5_textSize(params[0]);
	break;
  case (TEXT_FONT):
    p5_textFont(params[0]);
  	break;
  case (TEXT):
    p5_text(cmmd->text,params[0],params[1]);
    break;
  case (BEGIN_SHAPE):
    p5BeginShape(params[0]);
    break;
  case (VERTEX):
    p5Vertex(params[0],params[1]);
    break;
  case (END_SHAPE):
    p5EndShape(params[0]);
    break;
  case (IMAGE):
    if (cmmd->size==3) 
      p5_image(params[0],params[1],params[2]);
	else if (cmmd->size==5) 
	  p5_imageResize(params[0],params[1],params[2],params[3],params[4]);
    break;
  case (SHAPE):
    p5_shape(params[0]);
    break;
  case (IMAGE_MODE):
    p5_imageMode(params[0]);
    break;
  default:
   return -1;
  }
  return 0;
}

int appendCmmd(AList *displayList,char *line, Context *ctx) {
  float d;
  int i=0;
  bool intParams = 0;
  float *params = malloc(sizeof(float)*8);
  char *text;
  char *err;
	  
  char *token = strtok(line, " ");
  
  int code = commandLookup(token);
  if (code==NONE) return code;
  
  token = strtok(NULL, "\"");
  if (token!=NULL) {
 	text = malloc(sizeof(char)*128);
	strncpy(text,token,128);
	token = strtok(NULL, " ,");
	
	if (token==NULL) {
	  token = strtok(text, " ,");
	  //text = NULL;
    }
	constantLookup(token);
	if (strncmp(token,"0x",2)==0) {
	  d = strtol(token,&err, 16);
	  intParams = 1;
	} else
	  d = strtod(token, &err);
	while (true) {
	  params[i++] = d;
  	  token = strtok(NULL, " ,");
	  if (token==NULL) break;
	  d = strtod(token, &err);
    }
  }

  int result;
  if (code<=CMMD_MAX)
	result = list_add(displayList,cmmd_make(code,params,i,text,intParams));
  else if (CMMD_MAX<code&&code<=SETUP_MAX)
	result = execMetaCmmd(displayList,cmmd_make(code,params,i,text,intParams),ctx);
  else
	result = execMetaCmmd(displayList,cmmd_make(code,params,i,text,intParams),ctx);
  
  if (result<0)
	return result;
  else
	return list_currPos(displayList);
}

#endif