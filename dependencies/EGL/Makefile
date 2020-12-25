LIBFLAGS=-L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lGL -lGLU 
INCLUDEFLAGS=-I/opt/vc/include -I/opt/vc/include/interface/vmcs_host/linux -I/opt/vc/include/interface/vcos/pthreads -fPIC

test_pi:	test_pi.c
	gcc test_pi.c $(INCLUDEFLAGS)