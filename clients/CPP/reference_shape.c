#include "p5lib.h"

  // Reference Processing - shape()

void setup() {
  p5_size(640,480);
  p5_background(200);
}

void draw() {
	p5_pushMatrix();
	
	p5_fill(255);
	p5_beginShape(P5_POLYGON);
	p5_vertex(30, 20);
	p5_vertex(85, 20);
	p5_vertex(85, 75);
	p5_vertex(30, 75);
	p5_endShape(P5_CLOSE);
	
	p5_popMatrix();
	p5_pushMatrix();
	p5_translate(100,0);
	p5_fill(255);
	
	p5_beginShape(P5_POINTS);
	p5_vertex(30, 20);
	p5_vertex(85, 20);
	p5_vertex(85, 75);
	p5_vertex(30, 75);
	p5_endShape(P5_OPEN);
	
	p5_popMatrix();
	p5_pushMatrix();
	p5_translate(200,0);
	p5_fill(255);
	
	p5_beginShape(P5_LINES);
	p5_vertex(30, 20);
	p5_vertex(85, 20);
	p5_vertex(85, 75);
	p5_vertex(30, 75);
	p5_endShape(P5_OPEN);
	
	p5_popMatrix();
	p5_pushMatrix();
	p5_translate(300,0);
	
	p5_noFill();
	p5_beginShape(P5_POLYGON);
	p5_vertex(30, 20);
	p5_vertex(85, 20);
	p5_vertex(85, 75);
	p5_vertex(30, 75);
	p5_endShape(P5_OPEN);
	
	p5_popMatrix();
	p5_pushMatrix();
	p5_translate(0,100);
	
	p5_noFill();
	p5_beginShape(P5_POLYGON);
	p5_vertex(30, 20);
	p5_vertex(85, 20);
	p5_vertex(85, 75);
	p5_vertex(30, 75);
	p5_endShape(P5_CLOSE);
	
	p5_popMatrix();
	p5_pushMatrix();
	p5_translate(100,100);
	p5_fill(255);
	
	p5_beginShape(P5_TRIANGLES);
	p5_vertex(30, 75);
	p5_vertex(40, 20);
	p5_vertex(50, 75);
	p5_vertex(60, 20);
	p5_vertex(70, 75);
	p5_vertex(80, 20);
	p5_endShape(P5_OPEN);
	
	p5_popMatrix();
	p5_pushMatrix();
	p5_translate(200,100);
	p5_fill(255);
	
	p5_beginShape(P5_TRIANGLE_STRIP);
	p5_vertex(30, 75);
	p5_vertex(40, 20);
	p5_vertex(50, 75);
	p5_vertex(60, 20);
	p5_vertex(70, 75);
	p5_vertex(80, 20);
	p5_vertex(90, 75);
	p5_endShape(P5_OPEN);
	
	p5_popMatrix();
	p5_pushMatrix();
	p5_translate(0,200);
	p5_fill(255);
	
	p5_beginShape(P5_TRIANGLE_FAN);
	p5_vertex(57.5, 50);
	p5_vertex(57.5, 15); 
	p5_vertex(92, 50); 
	p5_vertex(57.5, 85); 
	p5_vertex(22, 50); 
	p5_vertex(57.5, 15); 
	p5_endShape(P5_OPEN);
	
	p5_popMatrix();
	p5_pushMatrix();
	p5_translate(100,200);
	p5_fill(255);
	
	p5_beginShape(P5_QUADS);
	p5_vertex(30, 20);
	p5_vertex(30, 75);
	p5_vertex(50, 75);
	p5_vertex(50, 20);
	p5_vertex(65, 20);
	p5_vertex(65, 75);
	p5_vertex(85, 75);
	p5_vertex(85, 20);
	p5_endShape(P5_OPEN);
	
	p5_popMatrix();
	p5_pushMatrix();
	p5_translate(200,200);
	p5_fill(255);
	
	p5_beginShape(P5_QUAD_STRIP); 
	p5_vertex(30, 20); 
	p5_vertex(30, 75); 
	p5_vertex(50, 20);
	p5_vertex(50, 75);
	p5_vertex(65, 20); 
	p5_vertex(65, 75); 
	p5_vertex(85, 20);
	p5_vertex(85, 75); 
	p5_endShape(P5_OPEN);
	
	p5_popMatrix();
	p5_pushMatrix();
	p5_translate(300,200);
	p5_fill(255);
	
	p5_beginShape(P5_POLYGON);
	p5_vertex(20, 20);
	p5_vertex(40, 20);
	p5_vertex(40, 40);
	p5_vertex(60, 40);
	p5_vertex(60, 60);
	p5_vertex(20, 60);
	p5_endShape(P5_CLOSE);
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}