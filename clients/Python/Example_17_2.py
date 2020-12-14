import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com
#
# Example 17-2: Text align 

def setup():
  global f1,f2
  pg.size(480, 270)
  f1 = pg.loadFont("fonts/charter.txf")
  f2 = pg.loadFont("fonts/lucida.txf")

def draw():
  global f1,f2
  pg.background(255)
  pg.stroke(175)
  pg.line(pg.width/2, 0, pg.width/2, pg.height)
  
  pg.textFont(f1)
  pg.textSize(16)
  pg.fill(0)

  # textAlign() sets the alignment for displaying text. It takes one argument: CENTER, LEFT, or RIGHT.
  pg.textAlign(pg.CENTER)
  pg.text("This text is centered.", pg.width/2, 160)
  pg.textFont(f2)
  pg.textSize(16)
  pg.textAlign(pg.LEFT)
  pg.text("This text is left aligned.", pg.width/2, 200)
  pg.textFont(f1)
  pg.textSize(16)
  pg.textAlign(pg.RIGHT)
  pg.text("This text is right aligned.", pg.width/2, 240)

pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.listen()