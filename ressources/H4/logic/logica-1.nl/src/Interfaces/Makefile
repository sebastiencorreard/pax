# Interfaces/Makefile.  Generated from Makefile.in by configure.

wims_home=../..
PUBDIR=$(wims_home)/public_html/bin
cc=cc
cflags=-g -O2 -Wall
LDFLAGS=
CPPFLAGS=
lopt=-L$(wims_home)/lib -lwims -lm $(rpath)

defines=-DGNU_SOURCE -DVERSION_DATE=\"2017-10-14\"
static=
SETENV_OBJS=
STRIP=strip
commonobj= common.o
progstatic=pari yacas maxima scilab
progdynamic=gap octave m2
progs=$(progstatic) $(progdynamic)
H=../Lib/libwims.h ../config.h ../includes.h ../wimsdef.h
all: $(progs) install

clean:
	rm -f $(progs) *.o

distclean: clean
	cd $(PUBDIR); rm -f $(progs)
	rm -f Makefile

%.o: %.c common.h $(H)
	$(cc) -o $@ $(cflags) $(CPPFLAGS) $(defines) -c $<

install: $(progs)
	$(STRIP) $(progs)
	cp $(progs) $(PUBDIR)

m2: m2.o $(commonobj) $(SETENV_OBJS)
	$(cc) $(cflags) $(LDFLAGS) m2.o $(commonobj) $(SETENV_OBJS) $(lopt) -o $@
octave: octave.o $(commonobj) $(SETENV_OBJS)
	$(cc) $(cflags) $(LDFLAGS) octave.o $(commonobj) $(SETENV_OBJS) $(lopt) -o $@
gap: gap.o $(commonobj) $(SETENV_OBJS)
	$(cc) $(cflags) $(LDFLAGS) gap.o $(commonobj) $(SETENV_OBJS) $(lopt) -o $@

pari: pari.o $(commonobj) $(SETENV_OBJS)
	$(cc) $(cflags) $(LDFLAGS) $(static) pari.o $(commonobj) $(SETENV_OBJS) $(lopt) -o $@
maxima: maxima.o $(commonobj) $(SETENV_OBJS)
	$(cc) $(cflags) $(LDFLAGS) $(static) maxima.o $(commonobj) $(SETENV_OBJS) $(lopt) -o $@
	if [ -e $(wims_home)/chroot/tmp/.chroot ] && [ ! -z `cat common.h | grep CHROOT_PRESENT` ] ; then echo "#define CHROOT_PRESENT" >> common.h ;fi
scilab: scilab.o $(commonobj) $(SETENV_OBJS)
	$(cc) $(cflags) $(LDFLAGS) $(static) scilab.o $(commonobj) $(SETENV_OBJS) $(lopt) -o $@

yacas: yacas.o $(commonobj) $(SETENV_OBJS)
	$(cc) $(cflags) $(LDFLAGS) $(static) yacas.o $(commonobj) $(SETENV_OBJS) $(lopt) -o yacas
