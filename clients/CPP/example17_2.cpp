#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 17-2: Text align 

//PFont f; 

float r = 8;

p5d::PGraphics pg("localhost", "8888");

int main(int argc, char** argv) {

	int width = 480;
	int height = 270;
	
    pg.size(width, height);

    PFont fnt = pg.loadFont("fonts/lucida.txf");
	
	PImage img = pg.loadImage("icons/laptop130.png");
	
	PShape shp = pg.createShape(pg.RECT, 0, 0, 80, 80);
	
	pg.textFont(fnt);

    pg.background(255.0f);
    pg.stroke(175.0f);
	
    pg.line(width/2, 0, width/2, height);
    pg.textSize(16);
    pg.fill(0.0f);
	
	pg.textAlign(pg.CENTER,0);
    pg.text("This text is centerepg.", width/2, 160);
    pg.textAlign (pg.LEFT,0) ;
    pg.text("This text is left alignepg.", width/2, 200);
    pg.textAlign(pg.RIGHT,0);
    pg.text("This text is right alignepg.", width/2, 240);
	
	pg.shape(shp,10,20);
	pg.image(img,30,40);
	
	pg.listen();
}
