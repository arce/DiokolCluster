#include "p5lib.h"

  // Reference Processing - ellipseMode()

void setup() {
  p5_size(640,480);
  p5_background(200);
}

void draw() {
	p5_ellipseMode(P5_RADIUS);  // Set ellipseMode to RADIUS
	p5_fill(255);  // Set fill to white
	p5_ellipse(50, 50, 30, 30);  // Draw white ellipse using RADIUS mode

	p5_ellipseMode(P5_CENTER);  // Set ellipseMode to CENTER
	p5_fill(100);  // Set fill to gray
	p5_ellipse(50, 50, 30, 30);  // Draw gray ellipse using CENTER mode
	
	p5_translate(100,0);
	p5_ellipseMode(P5_CORNER);  // Set ellipseMode is CORNER
	p5_fill(255);  // Set fill to white
	p5_ellipse(25, 25, 50, 50);  // Draw white ellipse using CORNER mode

	p5_ellipseMode(P5_CORNERS);  // Set ellipseMode to CORNERS
	p5_fill(100);  // Set fill to gray
	p5_ellipse(25, 25, 50, 50);  // Draw gray ellipse using CORNERS mode
}

int main(int argc, char** argv) {
    p5_init(argc,argv);
    p5_setupFunc(setup);
    p5_drawFunc(draw);
    p5_createWindow("Reference Processing - ellipseMode()");
    p5_mainLoop();
}