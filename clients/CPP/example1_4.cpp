#include "p5d.h"

	// Learning Processing
	// Daniel Shiffman
	// http://www.learningprocessing.com

	// Example 1-4: Alpha Transparency

int main(int argc, char** argv) {
	p5d::p5DGraphics pg;
	
	pg.size(480, 270);
	pg.background(0);
	pg.noStroke();

	// No fourth argument means 100% opacity.
	pg.fill(0,0,255);
	pg.rect(0, 0, 240, 200);

	// 255 means 100% opacity.
	pg.fill(255,0,0,255);
	pg.rect(0, 0, 480, 40);

	// 75% opacity.
	pg.fill(255,0,0,191);
	pg.rect(0, 50, 480, 40);

	// 55% opacity.
	pg.fill(255,0,0,127);
	pg.rect(0, 100, 480, 40);

	// 25% opacity.
	pg.fill(255,0,0,63);
	pg.rect(0, 150, 480, 40);
	
	pg.listen();
}