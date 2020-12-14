CC = gcc
# Linux (default)
LDFLAGS = -lGL -lGLU -lglut -lm -lpthread
#CFLAGS = -w -std=gnu99 -m32
CFLAGS = -w -std=gnu99 -m64

RM = rm -f

UNAME := $(shell uname)

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
  LDFLAGS = -lopengl32 -lwinmm -lgdi32 -lws2_32 -lglu32 -lglut32
  CFLAGS += -D_WIN32
endif

# OS X
ifeq "$(UNAME)" "Darwin"
  LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
  CFLAGS += -D__APPLE__
endif

all : DiokolServer

DiokolServer : src/DiokolServer.c
	$(CC) $(CFLAGS) src/DiokolServer.c ini/ini.c -o DiokolServer $(LDFLAGS)

clean :
	$(RM) *.o $(PROG) *.*~