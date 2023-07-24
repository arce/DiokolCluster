#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 6-1: Many lines 

p5d::PGraphics pg("localhost", "8888");

void setup() {
  p5_size(480,270);
}

void draw() {
	pg.background(255);  
	// Legs  
	pg.stroke(0);  
	pg.line(50,60,50,80);  
	pg.line(60,60,60,80);  
	pg.line(70,60,70,80);  
	pg.line(80,60,80,80);  
	pg.line(90,60,90,80);  
	pg.line(100,60,100,80);  
	pg.line(110,60,110,80);  
	pg.line(120,60,120,80);  
	pg.line(130,60,130,80);  
	pg.line(140,60,140,80);  
	pg.line(150,60,150,80);
}

int main(int argc, char** argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);
  pg.listen();
}
