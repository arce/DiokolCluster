# -*- mode: c; tab-width: 4; indent-tabs-mode: nil; -*-
#
# This file is part of p5Display.
#
# Copyright (c) 2014-2016 Armando Arce
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would
#    be appreciated but is not requirepg.
#
# 2. Altered source versions must be plainly marked as such, and must not
#    be misrepresented as being the original software.
#
# 3. This notice may not be removed or altered from any source
#    distribution.
#
import socket

class color():
  def __init__(self,clrId):
      self.clrId = clrId

class PFont():
  def __init__(self,fntId):
      self.fntId = fntId

class PImage():
  def __init__(self,imgId):
      self.imgId = imgId

class PShape():
  def __init__(self,shpId):
      self.shpId = shpId
      
class PNumber():
  idCount = 0
  def __init__(self,numId):
      self.id = numId
  def set(self,value):
      self.value = value
  def get(self):
      return self.value

class PGraphics():
  HALF_PI = 1.57079632679489661923
  PI = 3.14159265358979323846
  QUARTER_PI = 0.7853982
  TAU = 6.28318530717958647693
  TWO_PI = 6.28318530717958647693
  
  MOUSE_DOWN = 0
  MOUSE_UP = 1
  MOUSE_LEFT = 0
  MOUSE_RIGHT = 1
  
  PIE = 0
  OPEN = 1
  CHORD = 2
  CENTER = 3
  RADIUS = 4
  CORNER = 5
  CORNERS = 6
  POINTS = 7
  LINES = 8
  TRIANGLES = 9
  TRIANGLE_FAN = 10
  TRIANGLE_STRIP = 11
  QUADS = 12
  QUAD_STRIP = 13
  POLYGON = 14
  CLOSE = 15
  OPEN = 16
  LEFT = 17
  RIGHT = 18
  TOP = 19
  BOTTOM = 20
  BASELINE = 21
  modes = ['PIE','OPEN','CHORD','CENTER','RADIUS','CORNER','CORNERS','POINTS','LINES','TRIANGLES','TRIANGLE_FAN','TRIANGLE_STRIP','QUADS','QUAD_STRIP','POLYGON','CLOSE','OPEN','LEFT','RIGHT','TOP','BOTTOM','BASELINE']

  def __init__(self,host='localhost',port=9555):
    self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    self.s.connect((host, port))
    self.shpCount = 1
    self.fntCount = 1
    self.imgCount = 1
    self.clrCount = 1
    self.numCount = 1
    self.strCount = 1
    self.pmouseX = 0
    self.pmouseY = 0
    self.mouseX = 0
    self.mouseY = 0
    self.posX = 0
    self.posY = 0
    self.key = 0
    self.frameCount = 0
    self.width = 0
    self.height = 0
    self.mousePressed__ = None
    self.mouseMoved__ = None
    self.keyPressed__ = None
    self.draw__ = None
    self.setup__ = None
    self.idle__ = None
    self.mousePressedDef = False
    self.mouseMovedDef = False
    self.keyPressedDef = False
    self.drawDef = False
    self.setupDef = False
    self.idleEventDef = False
    self.cache = []

  def send(self,msg):
    self.s.sendall(str.encode(msg))

  def flush(self):
    return

  def send1(self,msg):
    self.cache.append(msg)

  def flush1(self):
    for msg in self.cache:
      self.s.sendall(msg)
    self.cache = []
    
  def varNum(self,v):
    if isinstance(v,PNumber):
        return '$'+str(v.id)
    else:
        return v
  
  def mouseClickedFunc(self,param):
    self.mouseClicked__ = param
    self.mouseClickedDef = True
    self.send('.enableMouseClicked\n')

  def mouseDraggedFunc(self,param):
    self.mouseDragged__ = param
    self.mouseDraggedDef = True
    self.send('.enableMouseDragged\n')

  def mouseMovedFunc(self,param):
    self.mouseMoved__ = param
    self.mouseMovedDef = True
    self.send('.enableMouseMoved\n')
            
  def mousePressedFunc(self,param):
    self.mousePressed__ = param
    self.mousePressedDef = True
    self.send('.enableMousePressed\n')

  def mouseReleasedFunc(self,param):
    self.mouseReleased__ = param
    self.mouseReleasedDef = True
    self.send('.enableMouseReleased\n')

  def mouseWheelFunc(self,param):
    self.mouseWheel__ = param
    self.mouseWheelDef = True
    self.send('.enableMouseWheel\n')
        
  def keyPressedFunc(self,param):
    self.keyPressed__ = param
    self.keyPressedDef = True
    self.send('enableKeyPressed\n')

  def drawFunc(self,param):
    self.draw__ = param
    self.drawDef = True

  def setupFunc(self,param):
    self.setup__ = param
    self.setupDef = True

  def idleFunc(self,param):
    self.idle__ = param
    self.idleDef = True

 # Structure

  def processResponse__(self,resp):
    lines = resp.decode("utf-8").split('\n')
    for line in lines:
      tokens = line.split(' ')
      event = tokens[0]
      if ((event=='mouseClicked') or
          (event=='mouseDragged') or 
          (event=='mouseMoved') or 
          (event=='mousePressed') or 
          (event=='mouseReleased')):
        self.pmouseX = self.mouseX
        self.pmouseY = self.mouseY
        self.mouseX = int(tokens[1])
        self.mouseY = int(tokens[2])
      if (event=='mousePressed'):
        self.mouseButton = int(tokens[3])
        self.mousePressed = True
      if (event=='keyPressed'):
        self.key = chr(int(tokens[1]))
        self.keyPressed = True
      if (event=='idleEvent'):
        self.frameCount = int(tokens[1])
    
      if (event=='mouseClicked') and self.mouseClickedDef:
        self.mouseClicked__()
      elif (event=='mouseDragged') and self.mouseDraggedDef:
        self.mouseDragged__()
      elif (event=='mouseMoved') and self.mouseMovedDef:
        self.mouseMoved__()
      elif (event=='mousePressed') and self.mousePressedDef:
        self.mousePressed__()
      elif (event=='mouseReleased') and self.mouseReleasedDef:
        self.mouseReleased__()
      elif (event=='mouseWheel') and self.mouseWheelDef:
        self.mouseWheel__()
      elif (event=='keyPressed') and self.keyPressedDef:
        self.keyPressed__()
      elif (event=='idleEvent') and self.idleEventDef:
        self.idle__()
    #if (self.drawDef):
    #  self.draw__()
    self.flush()

  def listen__(self):
    while (True):
      recvbuf = self.s.recv(4096)
      self.processResponse__(recvbuf)

  def listen(self):
    if (self.setupDef):
        self.setup__()
    if (self.drawDef):
        self.draw__()
    self.flush()
    self.listen__()

  def loop(self):
    self.send('loop\n')

  def noLoop(self):
    self.send('noLoop\n')

  def popStyle(self):
    self.send('popStyle\n')

  def pushStyle(self):
    self.send('pushStyle\n')

  def redraw(self):
    self.send('redraw\n')

 # Environment

  def frameRate(self,rate):
    self.send('frameRate '+str(rate)+'\n')

  def noSmooth(self):
    self.send('noSmooth\n')

  def size(self,w,h):
    self.width = w
    self.height = h
    self.send('.size '+str(w)+' '+str(h)+'\n')

  def position(self,x,y):
    self.x = x
    self.y = y
    self.send('.position '+str(x)+' '+str(y)+'\n')

  def smooth(self):
    self.send('smooth\n')

 # Shape - createShape

  def loadShape(self,filename):
    self.shpCount = self.shpCount+1
    shpId = self.shpCount
    cmd = 'loadShape "'+filename+'" '+str(shpId)
    self.send(cmd+'\n')
    return PShape(shpId)

  def createShape(self,kind,*arg):
    self.shpCount = self.shpCount+1
    shpId = self.shpCount
    cmd = 'createShape '+str(shpId)+' '+shapes[kind]+' '
    for i in range(0, len(arg)):
      cmd += str(arg[i])+' '
    self.send(cmd+'\n')
    return PShape(shpId)

  def shape(self,shp,*arg):
    cmd = 'shape '+str(shp.shpId)+' '
    for i in range(0, len(arg)):
      cmd += str(arg[i])+' '
    self.send(cmd+'\n')

 # Shape - 2D Primitives

  def arc(self,a,b,c,d,start,stop,mode=OPEN):
    a = self.varNum(a)
    b = self.varNum(b)
    c = self.varNum(c)
    d = self.varNum(d)
    start = self.varNum(start)
    stop = self.varNum(stop)
    self.send('arc '+str(a)+' '+str(b)+' '+str(c)+' '+str(d)+' '+str(start)+' '+str(stop)+' '+self.modes[mode]+'\n')

  def ellipse(self,a,b,c,d):
    a = self.varNum(a)
    b = self.varNum(b)
    c = self.varNum(c)
    d = self.varNum(d)
    self.send('ellipse '+str(a)+' '+str(b)+' '+str(c)+' '+str(d)+'\n')

  def line(self,x1,y1,x2,y2):
    x1 = self.varNum(x1)
    y1 = self.varNum(y1)
    x2 = self.varNum(x2)
    y2 = self.varNum(y2)
    self.send('line '+str(x1)+' '+str(y1)+' '+str(x2)+' '+str(y2)+'\n')

  def point(self,x,y):
    x = self.varNum(x)
    y = self.varNum(y)
    self.send('point '+str(x)+' '+str(y)+'\n')

  def quad(self,x1,y1,x2,y2,x3,y3,x4,y4):
    x1 = self.varNum(x1)
    y1 = self.varNum(y1)
    x2 = self.varNum(x2)
    y2 = self.varNum(y2)
    x3 = self.varNum(x3)
    y3 = self.varNum(y3)
    x4 = self.varNum(x4)
    y4 = self.varNum(y4)
    self.send('quad '+str(x1)+' '+str(y1)+' '+str(x2)+' '+str(y2)+' '+str(x3)+' '+str(y3)+' '+str(x4)+' '+str(y4)+'\n')

  def rect(self,a,b,c,d):
    a = self.varNum(a)
    b = self.varNum(b)
    c = self.varNum(c)
    d = self.varNum(d)
    self.send('rect '+str(a)+' '+str(b)+' '+str(c)+' '+str(d)+'\n')

  def triangle(self,x1,y1,x2,y2,x3,y3):
    x1 = self.varNum(x1)
    y1 = self.varNum(y1)
    x2 = self.varNum(x2)
    y2 = self.varNum(y2)
    x3 = self.varNum(x3)
    y3 = self.varNum(y3)
    self.send('triangle '+str(x1)+' '+str(y1)+' '+str(x2)+' '+str(y2)+' '+str(x3)+' '+str(y3)+'\n')

  # Shape - Curves

  def bezier(self,x1,y1,x2,y2,x3,y3,x4,y4):
    x1 = self.varNum(x1)
    y1 = self.varNum(y1)
    x2 = self.varNum(x2)
    y2 = self.varNum(y2)
    x3 = self.varNum(x3)
    y3 = self.varNum(y3)
    x4 = self.varNum(x4)
    y4 = self.varNum(y4)
    self.send('bezier '+str(x1)+' '+str(y1)+' '+str(x2)+' '+str(y2)+' '+str(x3)+' '+str(y3)+' '+str(x4)+' '+str(y4)+'\n')

  def bezierDetail(self,detail):
    self.send('bezierDetail '+str(detail)+'\n')

  def curve(self,x1,y1,x2,y2,x3,y3,x4,y4):
    x1 = self.varNum(x1)
    y1 = self.varNum(y1)
    x2 = self.varNum(x2)
    y2 = self.varNum(y2)
    x3 = self.varNum(x3)
    y3 = self.varNum(y3)
    x4 = self.varNum(x4)
    y4 = self.varNum(y4)
    self.send('curve '+str(x1)+' '+str(y1)+' '+str(x2)+' '+str(y2)+' '+str(x3)+' '+str(y3)+' '+str(x4)+' '+str(y4)+'\n')

  # Shape - Attributes

  def ellipseMode(self,mode):
    self.send('ellipseMode '+self.modes[mode]+'\n')

  def rectMode(self,mode):
    self.send('rectMode '+self.modes[mode]+'\n')

  def strokeWeight(self,weight):
    self.send('strokeWeight '+str(weight)+'\n')

  # Vertex

  def beginShape(self,mode=POLYGON):
    self.send('beginShape '+self.modes[mode]+'\n')

  def endShape(self,mode=OPEN):
    self.send('endShape '+self.modes[mode]+'\n')

  def vertex(self,x,y):
    self.send('vertex '+str(x)+' '+str(y)+'\n')

  # Transform

  def popMatrix(self):
    self.send('popMatrix\n')

  def popMatrix(self):
    self.send('popMatrix\n')

  def rotate(self,a):
    a = self.varNum(a)  
    self.send('rotate '+str(a)+'\n')

  def scale(self,sx,sy=1):
    sx = self.varNum(sx)
    sy = self.varNum(sy) 
    self.send('scale '+str(sx)+' '+str(sy)+'\n')

  def translate(self,dx,dy=0):
    dx = self.varNum(dx)
    dy = self.varNum(dy)
    self.send('translate '+str(dx)+' '+str(dy)+'\n')

  # Color -settings

  def backgroundHex(self,*arg):
      if (len(arg)==1):
        self.send('.background 0x'+format(arg[0], '02x')+'\n')
      elif (len(arg)==2):
        self.send('.background 0x'+format(arg[0], '02x')+' '+str(arg[1])+'\n')

  def background(self,*arg):
      cmd = '.background '
      for i in range(0, len(arg)):
          cmd += str(arg[i])+' '
      self.send(cmd+'\n')
 
  def clear(self):
      self.send('.clear\n')

  def fillHex(self,*arg):
      if (len(arg)==1):
        self.send('fill 0x'+format(arg[0], '02x')+'\n')
      elif (len(arg)==2):
        self.send('fill 0x'+format(arg[0], '02x')+' '+str(arg[1])+'\n')

  def fill(self,*arg):
      cmd = 'fill'
      for i in range(0, len(arg)):
          cmd += ' '+str(arg[i])
      self.send(cmd+'\n')

  def noFill(self):
      self.send('noFill\n')

  def noStroke(self):
      self.send('noStroke\n')

  def strokeHex(self,*arg):
      if (len(arg)==1):
        self.send('stroke 0x'+format(arg[0], '02x')+'\n')
      elif (len(arg)==2):
        self.send('stroke 0x'+format(arg[0], '02x')+' '+str(arg[1])+'\n')

  def stroke(self,*arg):
      cmd = 'stroke'
      for i in range(0, len(arg)):
          cmd += ' '+str(arg[i])
      self.send(cmd+'\n')

  # Color - Creating & Reading

  def color(self,*arg):
    clrId = self.clrCount
    self.clrCount = self.clrCount+1
    cmd = 'color '+str(clrId)
    for i in range(0, len(arg)):
        cmd += str(arg[i])+' '
    self.send(cmd+'\n')
    return color(clrCount)
      
  # Image - Loading & Displaying
  
  def loadImage(self,filename):
    imgId = self.imgCount
    self.imgCount = self.imgCount+1
    cmd = 'loadImage "'+filename+'" '+str(imgId)
    self.send(cmd+'\n')
    return PImage(imgId)
    
  def image(self,img,*arg):
      cmd = 'image '+str(img.imgId)+' '
      for i in range(0, len(arg)):
          cmd += str(arg[i])+' '
      self.send(cmd+'\n')
      
  def imageMode(self,mode):
    self.send('imageMode '+self.modes[mode]+'\n')

  # Typography - Loading & Displaying
  
  def loadFont(self,filename):
    self.fntCount = self.fntCount+1
    fntId = self.fntCount
    cmd = 'loadFont "'+filename+'" '+str(fntId)
    self.send(cmd+'\n')
    return PFont(fntId)
    
  def text(self,text,*arg):
    cmd = 'text "'+text+'" '
    for i in range(0, len(arg)):
        cmd += str(varNum(arg[i]))+' '
    self.send(cmd+'\n')

  def textFont(self,fnt):
      self.send('textFont '+str(fnt.fntId)+'\n')

  def textSize(self,size):
      self.send('textSize '+str(size)+'\n')

  def textAlign(self,mode1,mode2=BASELINE):
      self.send('textAlign '+self.modes[mode1]+' '+self.modes[mode2]+'\n')
      
  # Variables
  
  def number(self,value):
      var = PNumber(self.numCount)
      self.numCount+=1
      var.set(value)
      self.send('.defineNumber '+str(var.id)+' '+str(var.get())+'\n')
      return var

  def set(self,var,value):
      var.set(value)
      self.send('.set '+str(var.id)+' '+str(var.get())+'\n')
