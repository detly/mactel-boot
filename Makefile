VERSION=0.9

PRODUCTVERSION ?= Linux

default: SystemVersion.plist hfs-bless

hfs-bless: bless.c
	$(CC) -g -o hfs-bless bless.c

SystemVersion.plist: SystemVersion.plist.in
	sed "s/PRODUCTVERSION/$(PRODUCTVERSION)/" SystemVersion.plist.in >SystemVersion.plist

clean:
	rm hfs-bless SystemVersion.plist

install: hfs-bless SystemVersion.plist
	install -D hfs-bless $(DESTDIR)/usr/sbin/hfs-bless
	install -D -m 644 bless.1 $(DESTDIR)/usr/share/man/man1/hfs-bless.1

dist:
	rm -rf mactel-boot-$(VERSION)
	mkdir mactel-boot-$(VERSION)
	cp GPL bless.1 bless.c Makefile SystemVersion.plist.in Copyright mactel-boot-$(VERSION)
	tar jcf mactel-boot-$(VERSION).tar.bz2 mactel-boot-$(VERSION)
