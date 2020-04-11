VERSION=0.1
CC ?= gcc
CFLAGS ?= -Os -Wall
INSTALL ?= install

TOOL=exportall

$(TOOL): exportall.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: install tarball clean test

install: $(TOOL)
	$(INSTALL) -D -m 755 -t $(DESTDIR)/bin/ $(TOOL)

tarball: $(TOOL)-$(VERSION).tar.zst
$(TOOL)-$(VERSION).tar.zst: $(wildcard *.c)
	git archive --format=tar --prefix=$(TOOL)-$(VERSION)/ HEAD | zstd -c -o $@

test: $(TOOL)
	@for t in ./test/*-test; do echo $$t; $$t; done

clean:
	$(RM) $(TOOL) *.tar.zst
