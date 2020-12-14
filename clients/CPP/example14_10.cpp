#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-10: Pyramid
float theta = 0.0;

void setup() {
  p5_size(480, 240);
  p5_frameRate(10);
}

void drawPyramid(int t) {
  p5_stroke(0);

  // this pyramid has 4 sides, each drawn as a separate triangle
  // each side has 3 vertices, making up a triangle shape
  // the parameter " t " determines the size of the pyramid
  p5_beginShape(P5_TRIANGLES);

  p5_fillRGBA(150, 0, 0, 127);
  //p5_vertex3d(-t, -t, -t);
 // p5_vertex3d( t, -t, -t);
  //p5_vertex3d( 0, 0, t);

  p5_fillRGBA(0, 150, 0, 127);
  //p5_vertex3d( t, -t, -t);
  //p5_vertex3d( t, t, -t);
  //p5_vertex3d( 0, 0, t);

  p5_fillRGBA(0, 0, 150, 127);
  //p5_vertex3d( t, t, -t);
  //p5_vertex3d(-t, t, -t);
  //p5_vertex3d( 0, 0, t);

  p5_fillRGBA(150, 0, 150, 127);
  //p5_vertex3d(-t, t, -t);
  //p5_vertex3d(-t, -t, -t);
  //p5_vertex3d( 0, 0, t);

  p5_endShape();
}

void draw() {
  p5_background(255);
  theta += 0.01;

  //p5_translate3d(p5_width/2, p5_height/2, 0);
  //p5_rotateX(theta);
  //p5_rotateY(theta);
  drawPyramid(50);

  // translate the scene again
  //p5_translate3d(100, 100, 20);
  // call the pyramid drawing function
  drawPyramid(10);
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
