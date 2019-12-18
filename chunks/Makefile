# SOF
#
# make.chunks
#
BIN = chunks
COMMON = Makefile
PREFIX ?= /usr/local

all: LC_ALL=C
all: chunks

debug: DEBUG=20
debug: chunks

chunks: DEBUG=0
chunks: chunks.c chunks.h crc.c $(COMMON)
	@gcc -Wall -o chunks chunks.c crc.c

.PHONY: clean
clean:
	-@rm $(BIN)

.PHONY: install
install: chunks
	cp chunks $(PREFIX)/bin/

# vim: set ft=make:
# EOF
