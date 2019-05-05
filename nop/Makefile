#
# Makefile
#

PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
SBINDIR=$(PREFIX)/sbin

DEBUG=2
LCFLAGS=-O0 -DDEBUG=$(DEBUG)
ALL=nop

all: $(ALL)

nop: Makefile nop.c
	gcc $(LDFLAGS) -o nop nop.c

clean:
	@rm $(ALL)

install:
	cp nop $(BINDIR)

# EOF
