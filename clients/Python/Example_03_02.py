import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com
#
# Example 3-2: mouseX and mouseY

def setup():
  global x,y
  pg.size(480, 270)
  pg.position(100,200)
  x = pg.number(0)
  y = pg.number(0)

def draw():
  global x,y
  # Try moving background() to setup() and see the difference!
  pg.background(255)

  # Body
  pg.stroke(0)
  pg.fill(175)
  pg.rectMode(pg.CENTER)

  # mouseX is a keyword that the sketch replaces with the horizontal position of the mouse.
  # mouseY is a keyword that the sketch replaces with the vertical position of the mouse.
  pg.rect(x, y, 50, 50)

def mouseMoved():
  global x,y
  pg.set(x,pg.mouseX)
  pg.set(y,pg.mouseY)

pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.mouseMovedFunc(mouseMoved)
pg.listen()