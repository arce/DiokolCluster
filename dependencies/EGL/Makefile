INCDIR=-I./Common -I$(SDKSTAGE)/opt/vc/include -I$(SDKSTAGE)/opt/vc/include/interface/vcos/pthreads -I$(SDKSTAGE)/opt/vc/include/interface/vmcs_host/linux

LIBS=-lGLESv2 -lEGL -lm -lbcm_host -L$(SDKSTAGE)/opt/vc/lib

CFLAGS+=-DRPI_NO_X

test_pi:	test_pi.c
	gcc $(CFLAGS) test_pi.c -o ./$@ ${INCDIR} ${LIBS}