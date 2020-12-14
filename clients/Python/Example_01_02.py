import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 1-2: noFill

pg = p5d.PGraphics()

pg.size(480, 270)
pg.background(255)

# noFill() leaves the shape with only an outline.
pg.noFill()
pg.stroke(0)
pg.ellipse(60, 60, 100, 100)

pg.listen()