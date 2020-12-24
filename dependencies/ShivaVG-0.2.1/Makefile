# Linux (default)
EXE = test_tiger
LDFLAGS = -lGL -lGLU -lglut -lOpenVG -ldl

# Windows (cygwin)
ifeq ($(OS), "Windows_NT")
        EXE = test_tiger.exe
                LDFLAGS = -lopengl32 -lglu32 -lglut32 -lOpenVG
endif

# OS X
ifeq "$(shell uname)" "Darwin"
        LDFLAGS = -framework Carbon -framework OpenGL -lglfw -lOpenVG
endif

all: test_tiger

test_tiger: test_tiger.o glad.o test_tiger_paths.o test.o libOpenVG.a
	gcc -lm -o test_tiger glad.o test.o test_tiger_paths.o -L. $< $(CFLAGS) $(LDFLAGS)

test_tiger.o: test_tiger.c test_tiger_paths.c
	gcc -O -c test_tiger.c test_tiger_paths.c -I.

glad.o: glad.c
	gcc -O -c glad.c -I.
	
test.o: test.c test.h
	gcc -O -c test.c -I.
	
shArrays.o: shArrays.c shArrays.h
	gcc -O -c shArrays.c -I.

shCommons.o: shCommons.c shCommons.h
	gcc -O -c shCommons.c -I.
	
shContext.o: shContext.c shContext.h
	gcc -O -c shContext.c -I.

shExtensions.o: shExtensions.c shExtensions.h
	gcc -O -c shExtensions.c -I.

shGeometry.o: shGeometry.c shGeometry.h
	gcc -O -c shGeometry.c -I.

shImage.o: shImage.c shImage.h
		gcc -O -c shImage.c -I.

shMath.o: shMath.c shMath.h
		gcc -O -c shMath.c -I.

shPaint.o: shPaint.c shPaint.h
		gcc -O -c shPaint.c -I.

shParams.o: shParams.c
		gcc -O -c shParams.c -I.

shPath.o: shPath.c shPath.h
		gcc -O -c shPath.c -I.

shPipeline.o: shPipeline.c
		gcc -O -c shPipeline.c -I.

shVectors.o: shVectors.c shVectors.h
		gcc -O -c shVectors.c -I.

shVgu.o: shVgu.c
		gcc -O -c shVgu.c -I.

libOpenVG.a: shArrays.o shCommons.o shContext.o shExtensions.o shGeometry.o shImage.o shMath.o shPaint.o shParams.o shPath.o shPipeline.o shVectors.o shVgu.o
	ar rcs libOpenVG.a shArrays.o shCommons.o shContext.o shExtensions.o shGeometry.o shImage.o shMath.o shPaint.o shParams.o shPath.o shPipeline.o shVectors.o shVgu.o

libs: libOpenVG.a

clean:
	rm -f test_tiger *.o *.a *.gch #This way is cleaner than your clean