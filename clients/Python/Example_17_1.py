import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com
#
# Example 17-1: Simple displaying text

def setup():
  global f
  pg.size(640, 480);

  # Step 3: Create Font
  f = pg.loadFont("fonts/lucida.txf")

def draw():
  global f
  pg.background(255)
  pg.textFont(f)     # Step 4: Specify font to be used
  pg.textSize(16)
  pg.fill(0)         # Step 5: Specify font color

  # Step 6: Display Text
  pg.text("Mmmmm ... Strings ...", 10, pg.height/2);

pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.listen()