lib_LTLIBRARIES = libnormvol.la

#libdir = $(plugindir)/$(VISUALIZATION_PLUGIN_DIR)

libnormvol_la_LDFLAGS = -module -avoid-version
libnormvol_la_LIBS = @GTK_LIBS@ @PTHREAD_LIBS@ @INTLLIBS@

COMMON_CFLAGS = -O2 -Wall -W \
	-I$(top_builddir) -I$(top_srcdir) \
	-D_REENTRANT @GTK_CFLAGS@
COMMON_SRC = normvol.c normvol.h smooth.c smooth.h cfg.c cfg.h \
	about.c about.h config.h monitor.c monitor.h\
	support.c support.h interface.c interface.h callbacks.c callbacks.h

CFLAGS = $(COMMON_CFLAGS)
libnormvol_la_SOURCES =  $(COMMON_SRC)
