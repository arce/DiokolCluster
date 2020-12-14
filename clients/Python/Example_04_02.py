import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 4-2: Using variables

# Declare and initialize two integer variables at the top of the code.
circleX = 100
circleY = 100

def setup():
  pg.size(480, 270)

def draw():
  global circleX,circleY
  pg.background(255)
  pg.stroke(0)
  pg.fill(175)
  # Use the variables to specify the location of an ellipse.
  pg.ellipse(circleX, circleY, 50, 50)

pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.listen()