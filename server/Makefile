CC = gcc
# Linux (default)
LDFLAGS = -lGL -lGLU -lglut -lm -lpthread -lluajit
#CFLAGS = -w -std=gnu99 -m32
CFLAGS = -lm

RM = rm -f

UNAME := $(shell uname)

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
  LDFLAGS = -lopengl32 -lwinmm -lgdi32 -lws2_32 -lglu32 -lglut32 -lluajit
  CFLAGS += -D_WIN32
endif

# OS X
ifeq "$(UNAME)" "Darwin"
  LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT -lluajit -pagezero_size 10000 -image_base 100000000
  CFLAGS += -D__APPLE__
endif

all : Diokol

Diokol : Diokol.c
	$(CC) $(CFLAGS) Diokol.c -o Diokol -L../lib -I../include $(LDFLAGS)

clean :
	$(RM) *.o $(PROG) *.*~