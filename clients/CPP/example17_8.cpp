#include "p5lib.h"
#include <string.h>

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 17-8: Characters along a curve 

// The message to be displayed
char message [] = "text along a curve";
//PFont f;

// The radius of a circle
float r = 100;

void setup() {
  p5_size(480, 270);
  //f = createFont("Georgia", 40);
  p5_textSize(40);
  //p5_textFont(f);
  // The text must be centered!
  p5_textAlign(P5_CENTER);
}

void draw() {
    p5_background(255);

     // Start in the center and draw the circle
     p5_translate(p5_width/2, p5_height/2);
     p5_noFill();
     p5_stroke(0);
     p5_ellipse(0, 0, r*2, r*2);

     // We must keep track of our position along the curve
     float arclength = 0;

     // For every box
     for (int i = 0; i < strlen(message); i ++ ) {

       // The character and its width
       char currentChar = message[i];
       // Instead of a constant width, we check the width of each character.
	   float w = p5_textWidth(&currentChar); 
       // Each box is centered so we move half the width
       arclength += w/2;

       // Angle in radians is the arclength divided by the radius
       // Starting on the left side of the circle by adding PI
       float theta = P5_PI + arclength / r;

       p5_pushMatrix();

       // Polar to Cartesian conversion allows us to find the point along the curve. See Chapter 13 for a review of this concept.
       p5_translate(r*cos(theta), r*sin(theta)); 
       // Rotate the box (rotation is offset by 90 degrees)
       p5_rotate(theta + P5_PI/2); 

       // Display the character
       p5_fill(0);
       p5_text(&currentChar, 0, 0);

       p5_popMatrix();

       // Move halfway again
       arclength += w/2;
     }
 }

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
