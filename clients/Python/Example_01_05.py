import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 1-5: Zoog

pg = p5d.PGraphics()

pg.size(480, 270)
pg.background(255)
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

pg.listen()