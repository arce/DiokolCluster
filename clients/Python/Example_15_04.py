import p5d

# Learning Processing
# Daniel Shiffman
# http://www.learningprocessing.com

# Example 15-4: Image sequence

maxImages = 10  # Total # of images
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
  
  pg. background(0)
  pg.image(images[imageIndex], 0, 0)

  # increment image index by one each cycle
  # use modulo " % "to return to 0 once the end of the array is reached
  imageIndex = (imageIndex + 1) % len(images)
  
pg = p5d.PGraphics()
pg.setupFunc(setup)
pg.drawFunc(draw)
pg.listen()