# SOF
#
# make.chunks
#
COMMON=Makefile
BIN=chunks

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

# vim:set ft=make:
# EOF
