all: rmchat

rmchat: rmchat.o librmcast.a
	gcc -o rmchat rmchat.o -L. -lrmcast -lpthead -lm

rmchat.o: rmchat.c rmcast.h
	gcc -O -c rmchat.c

rmcache.o: rmcache.c rmcache.h
	gcc -O -c rmcache.c

rmevent.o: rmevent.c rmevent.h rmstruct.h
	gcc -O -c rmevent.c
	
rminternals.o: rminternals.c rminternals.h
	gcc -O -c rminternals.c

rmmsg.o: rmmsg.c rmmsg.h
	gcc -O -c rmmsg.c

rmmsgpckt.o: rmmsgpckt.c rmmsgpckt.h
	gcc -O -c rmmsgpckt.c
	
rmtcp.o: rmtcp.c rmtcp.h
		gcc -O -c rmtcp.c
		
rmwinmask.o: rmwinmask.c rmwinmask.h
		gcc -O -c rmwinmask.c
		
rmwcast.o: rmwcast.c rmwcast.h
		gcc -O -c rmwcast.c
		
librmcast.a: rmcache.o rmevent.o rminternals.o rmmsg.o rmmsgpckt.o rmtcp.o rmwinmask.o rmcast.o
	ar rcs librmcast.a rmcache.o rmevent.o rminternals.o rmmsg.o rmmsgpckt.o rmtcp.o rmwinmask.o rmcast.o

libs: librmcast.a

clean:
	rm -f rmchat *.o *.a *.gch #This way is cleaner than your clean