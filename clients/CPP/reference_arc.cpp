#include "p5d.h"

  // Reference Processing - arc()

p5d::PGraphics pg("localhost","8888");

void setup() {
  pg.size(400,400);
}

void draw() {
	
	pg.background(200);
	
	pg.fill(255);
	pg.stroke(0);
	
	pg.arc(50, 55, 50, 50, 0, pg.HALF_PI);
	
	pg.noFill();
	pg.arc(50, 55, 60, 60, pg.HALF_PI, pg.PI);
	pg.arc(50, 55, 70, 70, pg.PI, pg.PI+pg.QUARTER_PI);
	pg.arc(50, 55, 80, 80, pg.PI+pg.QUARTER_PI, pg.TWO_PI);
}

int main(int argc, char **argv) {
	pg.setupFunc(setup);
	pg.drawFunc(draw);
	pg.listen();
}