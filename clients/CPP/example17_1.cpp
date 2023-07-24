#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 17-1: Simple displaying text

// Step 2: Declare PFont variable

//PFont f;

p5d::PGraphics pg("localhost", "8888");

void setup() {
  pg.size(480, 270);
  pg.frameRate(10);

  // Step 3: Create Font
  //f = createFont("Arial", 16);
}

void draw() {
  pg.background(255);
  pg.textSize(16); //textFont(f, 16); // Step 4: Specify font to be used
  pg.fill(0);         // Step 5: Specify font color

  // Step 6: Display Text
  pg.text("Mmmmm ... Strings ...", 10, pg.height/2);
}

int main(int argc, char **argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);

  pg.listen();
}