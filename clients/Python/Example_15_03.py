import p5d
import random

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 15-3: Swapping images

maxImages = 10 # Total # of images
imageIndex = 0 # Initial image to be displayed is the first

# Declaring an array of images.
images = [] 

def setup():
  global images,maxImages

  pg.size(200, 200)

  # Loading the images into the array
  # Don't forget to put the JPG files in the data folder!
  for i in range(0,maxImages):
    images.append(pg.loadImage( 'data/animal' + str(i) + '.jpg' ))

def draw():
  global images,imageIndex

  # Displaying one image
  pg.image(images[imageIndex], 0, 0)

def mousePressed():
  global images,imageIndex
  if (pg.mouseState==pg.MOUSE_DOWN):
  # A new image is picked randomly when the mouse is clicked
  # Note the index to the array must be an integer!
    imageIndex = int(random.randint(0,len(images)-1))

pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.mousePressedFunc(mousePressed)
pg.listen()