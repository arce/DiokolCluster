#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 17-1: Simple displaying text

// Step 2: Declare PFont variable

//PFont f;

void setup() {
  p5_size(640, 480);

  // Step 3: Create Font
  //f = createFont("Arial", 16);
}

void draw() {
  p5_background(255);
  p5_textSize(16); //textFont(f, 16); // Step 4: Specify font to be used
  p5_fill(0);         // Step 5: Specify font color

  // Step 6: Display Text
  p5_text("Mmmmm ... Strings ...", 10, p5_height/2);
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
