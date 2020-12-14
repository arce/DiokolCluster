import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 3-1: Zoog as dynamic sketch

# setup() runs first one time.  
# size() should always be first line of setup

def setup():
  # Set the size of the window
  pg.size(480, 270)

# draw() loops continuously until you close the sketch window.
def draw():
  # Draw a white background
  pg.background(255)

  # Set CENTER mode
  pg.ellipseMode(pg.CENTER)
  pg.rectMode(pg.CENTER)

  # Body
  pg.stroke(0)
  pg.fill(150)
  pg.rect(240, 145, 20, 100)

  # Head
  pg.fill(255)
  pg.ellipse(240, 115, 60, 60)

  # Eyes
  pg.fill(0)
  pg.ellipse(221, 115, 16, 32) 
  pg.ellipse(259, 115, 16, 32)

  # Legs
  pg.stroke(0)
  pg.line(230, 195, 220, 205)
  pg.line(250, 195, 260, 205)
  
pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.listen()