#include "p5lib.h"

  // Reference Processing - arc()

void setup() {
  p5_size(640,480);
  p5_background(200);
}

void draw() {
  p5_arc(50, 55, 50, 50, 0, P5_HALF_PI, P5_OPEN);
  p5_noFill();
  p5_arc(50, 55, 60, 60, P5_HALF_PI, P5_PI, P5_OPEN);
  p5_arc(50, 55, 70, 70, P5_PI, P5_PI+P5_QUARTER_PI, P5_OPEN);
  p5_arc(50, 55, 80, 80, P5_PI+P5_QUARTER_PI, P5_TWO_PI, P5_OPEN);
  
  p5_fill(255);
  p5_arc(50, 150, 80, 80, 0, P5_PI+P5_QUARTER_PI, P5_OPEN);
  
  p5_arc(150, 50, 80, 80, 0, P5_PI+P5_QUARTER_PI, P5_CHORD);

  p5_arc(150, 150, 80, 80, 0, P5_PI+P5_QUARTER_PI, P5_PIE);
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}