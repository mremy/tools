project( rev C )
cmake_minimum_required( VERSION 2.6 )

set( VERSION_MAJOR 0 )
set( VERSION_MINOR 1 )
set( VERSION_PATCH 0 )
set( VERSION ${VERSION_MAJOR}.${VERSION_MINOR} )

set( rev_src main.c )

add_executable( rev ${rev_src} )

# EOF
