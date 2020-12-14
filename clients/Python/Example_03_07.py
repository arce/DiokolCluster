import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 3-7: Translated Zoog?

def setup():
  global x,y
  pg.size(480, 270)
  x = pg.number(0)
  y = pg.number(0)

def draw():
  global x,y
  pg.background(255)
  pg.rectMode(pg.CENTER)
  pg.ellipseMode(pg.CENTER)

  # Draw everything relative to (mouseX, mouseY)
  pg.translate(x, y)

  # Draw Zoog's body
  pg.stroke(0)
  pg.fill(175)
  pg.rect(0, 0, 20, 100)

  # Draw Zoog's head
  pg.stroke(0)
  pg.fill(255)
  pg.ellipse(0, -30, 60, 60)
  # Draw Zoog's eyes
  pg.stroke(0)
  pg.fill(0)
  pg.ellipse(-19, -30, 16, 32)
  pg.ellipse( 19, -30, 16, 32)

  # Draw Zoog's legs
  pg.stroke(0)
  pg.line(-10, 50, -20, 60)
  pg.line( 10, 50, 20, 60)

def mouseMoved():
  global x,y
  pg.set(x,pg.mouseX)
  pg.set(y,pg.mouseY)
  pg.redraw()

#pg = p5d.PGraphics("192.168.0.26")
pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.mouseMovedFunc(mouseMoved)
pg.listen()