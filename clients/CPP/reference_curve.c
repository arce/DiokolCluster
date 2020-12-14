#include "p5lib.h"

  // Reference Processing - arc()

void setup() {
  p5_size(640,480);
  p5_background(200);
}

void draw() {
    p5_noFill();
    p5_strokeRGB(255, 102, 0);
    p5_curve(5, 26, 5, 26, 73, 24, 73, 61);
    p5_stroke(0);
    p5_curve(5, 26, 73, 24, 73, 61, 15, 65);
    p5_strokeRGB(255, 102, 0);
    p5_curve(73, 24, 73, 61, 15, 65, 15, 65);
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}