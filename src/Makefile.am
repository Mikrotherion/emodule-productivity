MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = -I. \
	   -I$(top_srcdir) \
	   -I$(includedir) \
	   @E_CFLAGS@

pkgdir = $(datadir)/$(MODULE_ARCH)
pkg_LTLIBRARIES = module.la
module_la_SOURCES = e_mod_main.h \
		    e_mod_main.c \
                    e_mod_config.c \
		    e_mod_log.c \
		    e_mod_config_worktools.c \
                    e_mod_config_windows.c \
		    e_mod_config_schedule.c

module_la_LIBADD = @E_LIBS@
module_la_LDFLAGS = -module -avoid-version
module_la_DEPENDENCIES = $(top_builddir)/config.h

clean-local:
	rm -rf *~
