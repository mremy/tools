# CmakeLists.txt for png_libread
cmake_minimum_required( VERSION 2.8 )
project( png_libread )
set( SRCS ${PROJECT_NAME}.c )
include( FindPNG )
add_executable( ${PROJECT_NAME} ${SRCS} )
target_link_libraries( ${PROJECT_NAME} ${PNG_LIBRARIES} )
# EOF
