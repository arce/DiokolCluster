#include "p5lib.h"

  // Reference Processing - arc()

void setup() {
  p5_size(640,480);
  p5_background(200);
}

void draw() {
    p5_noFill();
    p5_strokeRGB(255, 102, 0);
    p5_line(85, 20, 10, 10);
    p5_line(90, 90, 15, 80);
    p5_strokeRGB(0, 0, 0);
    p5_bezier(85, 20, 10, 10, 90, 90, 15, 80);
	p5_translate(200,0);
    p5_noFill();
    p5_strokeRGB(255, 102, 0);
    p5_line(30, 20, 80, 5);
    p5_line(80, 75, 30, 75);
    p5_strokeRGB(0, 0, 0);
    p5_bezier(30, 20,  80, 5,  80, 75,  30, 75);
}

int main(int argc, char** argv) {
    p5_init(argc,argv);
    p5_setupFunc(setup);
    p5_drawFunc(draw);
    p5_createWindow("Reference Processing - arc()");
    p5_mainLoop();
}