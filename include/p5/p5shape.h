#ifndef _P5SHAPE_H_
#define _P5SHAPE_H_ 1

#if _WIN32
#include <Windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

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

int p5_createShape(int kind, int shpId,Context *ctx) {
	if ((shpId<0)||(shpId>100))
		return -1;
	ctx->shapeTable[shpId] = shape_new(kind,NULL,0);
}

int p5_shape(int shpId) {
	if ((shpId<0)||(shpId>100))
		return -1;
	Shape *shp = ctx->shapeTable[shpId];
	float *params = shp->params;
	switch (shp->kind) {
		case (ARC):
		  p5_arc(params[0],params[1],params[2],
		       params[3],params[4],params[5],params[6]);
		  break;
		case (ELLIPSE):
		  p5_ellipse(params[0],params[1],params[2],params[3]);
		  break;
		case (QUAD):
		  p5_quad(params[0],params[1],params[2],params[3],
		        params[4],params[5],params[6],params[7]);
		  break;
		case (RECT):
		  p5_rect(params[0],params[1],params[2],params[3]);
		  break;
		case (LINE):
		  p5_line(params[0],params[1],params[2],params[3]);
		  break;
		case (POINT):
		  p5_point(params[0],params[1]);
		  break;
		case (BEZIER):
		  p5_bezier(params[0],params[1],params[2],params[3],
		            params[4],params[5],params[6],params[7]);
		  break;
		case (CURVE):
		  p5_curve(params[0],params[1],params[2],params[3],
		                params[4],params[5],params[6],params[7]);
		  break;
		case (TRIANGLE):
		  p5_triangle(params[0],params[1],params[2],
		              params[3],params[4],params[5]);
		  break;
	  }
}

#endif