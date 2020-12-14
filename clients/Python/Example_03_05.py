import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com
#
# Example 3-5: mousePressed and keyPressed

def setup():
  pg.size(480, 270)
  pg.background(255)

def draw():
  # Nothing happens in draw() in this example!
  pass

# Whenever a user clicks the mouse the code written inside mousePressed() is executed.
def mousePressed():
  pg.stroke(0)
  pg.fill(175)
  pg.rectMode(pg.CENTER)
  pg.rect(pg.mouseX, pg.mouseY, 16, 16)

# Whenever a user presses a key the code written inside keyPressed() is executed.
def keyPressed():
  pg.background(255)

pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.mousePressedFunc(mousePressed)
pg.keyPressedFunc(keyPressed)
pg.listen()