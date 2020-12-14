import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 15-2: Image "sprite"

# PImage head; // A variable for the image file
# float x,y;   // Variables for image location
# float rot;   // A variable for image rotation

def setup():
  global head,x,y,rot
  
  pg.size(200,200)
  
  # Load image, initialize variables
  head = pg.loadImage("data/face.jpg")
  x = 0.0
  y = pg.width/2.0
  rot = 0.0
  pg.frameRate(5)

def draw():
  global head,x,y,rot
  pg.background(255)
  
  # Translate and rotate
  pg.translate(x,y)
  pg.rotate(rot)
  
  # Images can be animated just like regular shapes using variables, translate(), rotate(), and so on.
  pg.imageMode(pg.CENTER)
  pg.image(head,0,0)
  
  # Adjust variables for animation
  x += 1.0
  rot += 0.02
  # if (x > pg.width+head.width):
  #    x = -head.width

pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.listen()