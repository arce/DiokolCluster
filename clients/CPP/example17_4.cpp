#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 17-3: Scrolling headlines 

// An array of news headlines

char *headlines[] = {
  "Processing downloads break downloading recorpg.", 
  "New study shows computer programming lowers cholesterol.",
};

//PFont f; // Global font variable
float x; // Horizontal location
int index = 0;

void setup() {
  p5_size(480, 270);
  p5_frameRate(10);

  //f = createFont( "Arial", 16);

  // Initialize headline offscreen
  x = p5_width;
}

void draw() {
	p5_background(255);
	p5_fill(0);

	// Display headline at x location
	p5_textSize(16); //p5_textFont(f, 16);
	p5_textAlign(P5_LEFT);

	// A specific String from the array is displayed according to the value of the "index" variable.
	p5_text(headlines[index], x, p5_height-20); 

	// Decrement x
	x = x - 3;

	// If x is less than the negative width, then it is off the screen
	// textWidth() is used to calculate the width of the current String.
	float w = p5_textWidth(headlines[index]); 
	if (x < -w) {
	  x = p5_width;
	  // index is incremented when the current String has left the screen in order to display a new String.
	  index = (index + 1) % 2 ; //strlen(headlines);
	}
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
