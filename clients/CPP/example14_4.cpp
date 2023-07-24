#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-3: A rectangle moving along the z-axis

// A variable for the Z (depth) coordinate

float z = 0;

p5d::PGraphics pg("localhost", "8888");

// The function sets the vertices for the pyramid around the centerpoint at a
// flexible distance, depending on the number passed in as an argument.
void drawPyramid(int t) {

  pg.stroke(0);

  // this pyramid has 4 sides, each drawn as a separate triangle
  // each side has 3 vertices, making up a triangle shape
  // the parameter " t " determines the size of the pyramid
  pg.beginShape(pg.TRIANGLES);

  pg.fillA(255, 150); // Note that each polygon can have its own color.
  pg.vertex3d(-t, -t, -t);
  pg.vertex3d(t, -t, -t);
  pg.vertex3d(0, 0, t);

  pg.fillA(150, 150);
  pg.vertex3d(t, -t, -t);
  pg.vertex3d(t, t, -t);
  pg.vertex3d(0, 0, t);

  pg.fillA(255, 150);
  pg.vertex3d(t, t, -t);
  pg.vertex3d(-t, t, -t);
  pg.vertex3d(0, 0, t);

  pg.fill(150, 150);
  pg.vertex3d(-t, t, -t);
  pg.vertex3d(-t, -t, -t);
  pg.vertex3d(0, 0, t);

  pg.endShape();
}

void setup() {
  pg.size(200, 200);
  pg.frameRate(10);
}

void draw() {
  pg.background(255);

  // The pyramid's vertices are drawn relative to a centerpoint.
  // Therefore, we call translate() to place the pyramid properly in the window.
  // A slightly better option might be to include the translate in the
  // drawPyramid() function and pass in x,y,z as arguments
  // p5_translate3d(100, 100, 0);
  drawPyramid(150);
}

int main(int argc, char **argv) {

  pg.setupFunc(setup);
  pg.drawFunc(draw);

  pg.listen();
}
