import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 4-3: Varying variables

# Declare and initialize two integer variables at the top of the code.
circleX = 0
circleY = 100

def setup():
  pg.size(480, 270)

def draw():
  pg.background(255)
  pg.stroke(0)
  pg.fill(175)
  # Use the variables to specify the location of an ellipse.
  pg.ellipse(circleX, circleY, 50, 50)

  # An assignment operation that increments the value of circleX by 1.
  circleX = circleX + 1

pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.listen()