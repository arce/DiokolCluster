import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 3-4: Drawing a continuous line
def setup():
  global x1,x2,y1,y2
  pg.size(480, 270)
  pg.background(255)
  x1 = pg.number(0)
  y1 = pg.number(0)
  x2 = pg.number(0)
  y2 = pg.number(0)

def draw():
  global x1,x2,y1,y2
  pg.stroke(0)

  # Draw a line from previous mouse location to current mouse location.
  pg.line(x1, y1, x2, y2)
  
def mouseMoved():
  global x1,x2,y1,y2
  pg.set(x1,pg.pmouseX)
  pg.set(y1,pg.pmouseY)
  pg.set(x2,pg.mouseX)
  pg.set(y2,pg.mouseY)

pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.mouseMovedFunc(mouseMoved)
pg.listen()