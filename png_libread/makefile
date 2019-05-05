#
# makefile
#

ALL=png_libread CMakeCache.txt  CMakeFiles  cmake_install.cmake  Makefile

all: png_libread

png_libread: LDFLAGS=-lpng

cmake:
	cmake CMakeLists.txt
	$(MAKE) -f Makefile

clean:
	@-rm -Rf $(ALL)
# EOF
