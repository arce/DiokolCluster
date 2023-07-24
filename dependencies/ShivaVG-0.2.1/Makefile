CC = cc
LD = cc
CFLAGS = -O -fno-common 
LDFLAGS = -framework Carbon -framework OpenGL -lglfw -lOpenVG

all: test_tiger

test_tiger: test_tiger.o glad.o test_tiger_paths.o test.o libOpenVG.dylib
	$(CC) -lm -o test_tiger glad.o test.o test_tiger_paths.o -L. $< $(CFLAGS) $(LDFLAGS)

test_tiger.o: test_tiger.c test_tiger_paths.c
	$(CC) $(CFLAGS) -c test_tiger.c test_tiger_paths.c -I.

glad.o: glad.c
	$(CC) $(CFLAGS) -c glad.c -I.
	
test.o: test.c test.h
	$(CC) $(CFLAGS) -c test.c -I.
	
shArrays.o: shArrays.c shArrays.h
	$(CC) $(CFLAGS) -c shArrays.c -I.

shCommons.o: shCommons.c shCommons.h
	$(CC) $(CFLAGS) -c shCommons.c -I.
	
shContext.o: shContext.c shContext.h
	$(CC) $(CFLAGS) -c shContext.c -I.

shExtensions.o: shExtensions.c shExtensions.h
	$(CC) $(CFLAGS) -c shExtensions.c -I.

shGeometry.o: shGeometry.c shGeometry.h
	$(CC) $(CFLAGS) -c shGeometry.c -I.

shImage.o: shImage.c shImage.h
	$(CC) $(CFLAGS) -c shImage.c -I.

shMath.o: shMath.c shMath.h
	$(CC) $(CFLAGS) -c shMath.c -I.

shPaint.o: shPaint.c shPaint.h
	$(CC) $(CFLAGS) -c shPaint.c -I.

shParams.o: shParams.c
	$(CC) $(CFLAGS) -c shParams.c -I.

shPath.o: shPath.c shPath.h
	$(CC) $(CFLAGS) -c shPath.c -I.

shPipeline.o: shPipeline.c
	$(CC) $(CFLAGS) -c shPipeline.c -I.

shVectors.o: shVectors.c shVectors.h
	$(CC) $(CFLAGS) -c shVectors.c -I.

shVgu.o: shVgu.c
	$(CC) $(CFLAGS) -c shVgu.c -I.

libOpenVG.dylib: shArrays.o shCommons.o shContext.o shExtensions.o shGeometry.o shImage.o shMath.o shPaint.o shParams.o shPath.o shPipeline.o shVectors.o shVgu.o
	$(LD) -dynamiclib -install_name libOpenVG.dylib -o libOpenVG.dylib -framework OpenGL  shArrays.o shCommons.o shContext.o shExtensions.o shGeometry.o shImage.o shMath.o shPaint.o shParams.o shPath.o shPipeline.o shVectors.o shVgu.o


clean:
	rm -f test_tiger *.o *.a *.gch #This way is cleaner than your clean