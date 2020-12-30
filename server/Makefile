CC = gcc
# Linux (default)
LDFLAGS = -lGL -lGLU -lglut -lpthread -lluajit -ldl -lm -lrmcast
#CFLAGS = -w -std=gnu99 -m32
CFLAGS =

RM = rm -f

UNAME := $(shell uname)

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
  CC = x86_64-w64-mingw32-gcc
  LDFLAGS = -lopengl32 -lwinmm -lgdi32 -lws2_32 -lglu32 -lglut32 -lluajit -lrmcast
  CFLAGS += -D_WIN32 -Wl,-subsystem,windows
endif

# OS X
ifeq "$(UNAME)" "Darwin"
  LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT -lluajit -lrmcast -pagezero_size 10000 -image_base 100000000
  CFLAGS += -D__APPLE__
endif

all : Diokol.bin

Diokol.bin : Diokol.c
	$(CC) $(CFLAGS) Diokol.c -o Diokol.bin -L../lib -I../include $(LDFLAGS)

clean :
	rm -f Diokol.bin