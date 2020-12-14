import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 4-4: Many variables

# We've got 8 variables now!  All  of type float.
circleX = 0
circleY = 0
circleW = 50
circleH = 100
circleStroke = 255
circleFill = 0
backgroundColor = 255
change = 0.5

# Your basic setup
def setup():
  pg.size(480, 270)

def draw():
  global circleX, circleY, circleW, circleH, circleStroke
  global circleFill, backgroundColor, change
  # Draw the background and the ellipse
  # Variables are used for everything: 
  # background, stroke, fill, location, and size.
  pg.background(backgroundColor)
  pg.stroke(circleStroke)
  pg.fill(circleFill)
  pg.ellipse(circleX, circleY, circleW, circleH)

  # Change the values of all variables
  # The variable change is used to increment 
  # and decrement the other variables.
  circleX = circleX + change
  circleY = circleY + change
  circleW = circleW + change
  circleH = circleH - change
  circleStroke = circleStroke - change
  circleFill = circleFill + change
  
pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.listen()