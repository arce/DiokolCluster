import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 3-3: Zoog as dynamic sketch with variation

def setup():
  global x,y1,y2
  pg.size(480, 270)  # Set the size of the window
  pg.position(200,200)
  x = pg.number(0)
  y1 = pg.number(0)
  y2 = pg.number(0)

def draw():
  global x,y1,y2
  pg.background(255)  # Draw a white background 

  # Set ellipses and rects to CENTER mode
  pg.ellipseMode(pg.CENTER)
  pg.rectMode(pg.CENTER)

  # Draw Zoog's body
  pg.stroke(0)
  pg.fill(175)
  # Zoog's body is drawn at the location (mouseX, mouseY).
  pg.rect(x, y1, 20, 100)

  # Draw Zoog's head
  pg.stroke(0)
  pg.fill(255)
  # Zoog's head is drawn above the body at the location (mouseX, mouseY - 30).
  pg.ellipse(x, y2, 60, 60)

  # Eyes
  pg.fill(0)
  pg.ellipse(221, 115, 16, 32) 
  pg.ellipse(259, 115, 16, 32)

  # Legs
  pg.stroke(0)
  pg.line(230, 195, 220, 205)
  pg.line(250, 195, 260, 205)

def mouseMoved():
  global x,y1,y2
  pg.set(x,pg.mouseX)
  pg.set(y1,pg.mouseY)
  pg.set(y2,pg.mouseY-30)

pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.mouseMovedFunc(mouseMoved)
pg.listen()