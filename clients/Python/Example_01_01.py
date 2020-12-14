import diokol

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 1-1: stroke and fill

dk = diokol.createGraphics()

dk.size(150, 200)
dk.background(255)
dk.stroke(0)
dk.fill(150)
dk.rect(50, 50, 75, 100)

dk.listen()
