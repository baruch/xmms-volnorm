SUBDIRS=src tests intl po

DISTCLEANFILES= *.orig *.rej *~ *.bak core

EXTRA_DIST = BUGS RELEASE \
	@PACKAGE@.spec.in \
	@PACKAGE@.lsm.in \
	config/* \
	glade/* \
	glade/src/*

dist-hook: @PACKAGE@.spec.in @PACKAGE@.lsm.in
	cp @PACKAGE@.spec $(distdir)
	cp @PACKAGE@.lsm $(distdir)
								
