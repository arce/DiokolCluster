#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 6-1: Many lines 

void setup() {
  p5_size(480,270);
}

void draw() {
	p5_background(255);  
	// Legs  
	p5_stroke(0);  
	p5_line(50,60,50,80);  
	p5_line(60,60,60,80);  
	p5_line(70,60,70,80);  
	p5_line(80,60,80,80);  
	p5_line(90,60,90,80);  
	p5_line(100,60,100,80);  
	p5_line(110,60,110,80);  
	p5_line(120,60,120,80);  
	p5_line(130,60,130,80);  
	p5_line(140,60,140,80);  
	p5_line(150,60,150,80);
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
