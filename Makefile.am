SUBDIRS=src tests

DISTCLEANFILES= *.orig *.rej *~ *.bak core

EXTRA_DIST = BUGS RELEASE \
	@PACKAGE@.spec.in \
	@PACKAGE@.lsm.in \
	config/*

dist-hook: @PACKAGE@.spec.in @PACKAGE@.lsm.in
	cp @PACKAGE@.spec $(distdir)
	cp @PACKAGE@.lsm $(distdir)
								
gui:
	cd src; make gui

