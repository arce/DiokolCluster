import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 15-1: "Hello World" images

# Declaring a variable of type PImage
# PImage is a class available from the Processing core library.
# PImage img; 

def setup():
  global img
  pg.size(320, 250)
  # Make a new instance of a PImage by loading an image file
  img = pg.loadImage("data/runde_bird_cliffs.jpg")

def draw():
  global img
  pg.background(0)
  # The image() function displays the image at a location
  # in this case the point (0,0).
  pg.imageMode(pg.CORNERS)
  pg.image(img, 50, 50, 200, 200)

pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.listen()