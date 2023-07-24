#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-10: Pyramid
float theta = 0.0;

p5d::PGraphics pg("localhost", "8888");

void setup() {
  pg.size(480, 240);
  pg.frameRate(10);
}

void drawPyramid(int t) {
  pg.stroke(0);

  // this pyramid has 4 sides, each drawn as a separate triangle
  // each side has 3 vertices, making up a triangle shape
  // the parameter " t " determines the size of the pyramid
  pg.beginShape(pg.TRIANGLES);

  pg.fillRGBA(150, 0, 0, 127);
  //pg.vertex3d(-t, -t, -t);
 // pg.vertex3d( t, -t, -t);
  //pg.vertex3d( 0, 0, t);

  pg.fillRGBA(0, 150, 0, 127);
  //pg.vertex3d( t, -t, -t);
  //pg._vertex3d( t, t, -t);
  //pg.vertex3d( 0, 0, t);

  pg.fillRGBA(0, 0, 150, 127);
  //pg.vertex3d( t, t, -t);
  //pg.vertex3d(-t, t, -t);
  //pg.vertex3d( 0, 0, t);

  pg.fillRGBA(150, 0, 150, 127);
  //pg.vertex3d(-t, t, -t);
  //pg.vertex3d(-t, -t, -t);
  //pg.vertex3d( 0, 0, t);

  pg.endShape();
}

void draw() {
  pg.background(255);
  theta += 0.01;

  //pg.translate3d(p5_width/2, p5_height/2, 0);
  //pg.rotateX(theta);
  //pg.rotateY(theta);
  drawPyramid(50);

  // translate the scene again
  // pg.translate3d(100, 100, 20);
  // call the pyramid drawing function
  drawPyramid(10);
}

int main(int argc, char** argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);

  pg.listen();
}
