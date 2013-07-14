AM_LDFLAGS=-avoid-version -module -export-dynamic

lib_LTLIBRARIES = libresolvconf_override.la

libresolvconf_override_la_SOURCES = resolvconf-override.c
libresolvconf_override_la_CFLAGS=$(AM_CFLAGS)
libresolvconf_override_la_LDFLAGS=$(AM_LDFLAGS)

install-exec-hook:
	rm -rf $(DESTDIR)$(libdir)/libresolvconf_override.la

uninstall-hook:
	rm -rf $(DESTDIR)$(libdir)/libresolvconf_override.la
