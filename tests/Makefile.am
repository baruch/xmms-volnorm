TESTS=testload
bin_PROGRAMS = testload

#LIBS = @GTK_LIBS@ @PTHREAD_LIBS@
LIBS = @GTK_LIBS@
LDADD = ../src/libnormvol.la

COMMON_CFLAGS = -O2 -Wall -W -I$(top_builddir) -I$(top_srcdir) -D_REENTRANT @GTK_CFLAGS@

COMMON_SRC = testload.c xmms_dummy.c

CFLAGS = $(COMMON_CFLAGS)
testload_SOURCES =  $(COMMON_SRC)
