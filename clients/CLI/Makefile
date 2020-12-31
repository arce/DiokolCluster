CC = gcc
# Linux (default)
LDFLAGS = -lGL -lGLU -lglut -ldl -lreadline -ldl -lm -lrmcast
#CFLAGS = -w -std=gnu99 -m32
CFLAGS =

RM = rm -f

UNAME := $(shell uname)

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
  LDFLAGS = -lopengl32 -lwinmm -lgdi32 -lws2_32 -lglu32 -lglut32 -lreadline
  CFLAGS += -D_WIN32
endif

# OS X
ifeq "$(UNAME)" "Darwin"
  LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT -lreadline -pagezero_size 10000 -image_base 100000000
  CFLAGS += -D__APPLE__
endif

all : diokol-cli

diokol-cli : diokol-cli.c
	$(CC) $(CFLAGS) diokol-cli.c -o diokol-cli -L../../lib -I../../include $(LDFLAGS)

clean :
	$(RM) *.o $(PROG) *.*~