SUBDIRS=src tests intl po

DISTCLEANFILES= *.orig *.rej *~ *.bak core

EXTRA_DIST = BUGS RELEASE \
	volnorm.spec volnorm.spec.in \
	volnorm.lsm volnorm.lsm.in \
	config glade

dist-hook:
	cd $(distdir) ; \
	rm -rf `find . -name \*CVS\*`
								
