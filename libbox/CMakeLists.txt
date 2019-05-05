project(libbox C)
cmake_minimum_required(VERSION 2.6)

set(mylibname box)
set(my_lib_src boxes.c)

# shared library
add_library(${mylibname}-shared SHARED ${my_lib_src})
set_target_properties(${mylibname}-shared PROPERTIES OUTPUT_NAME "${mylibname}")
set_target_properties(${mylibname}-shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS ${mylibname}-shared DESTINATION "${mylibname}/lib")

# static library
add_library(${mylibname}-static STATIC ${my_lib_src})
set_target_properties(${mylibname}-static PROPERTIES OUTPUT_NAME "${mylibname}")
set_target_properties(${mylibname}-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS ${mylibname}-static DESTINATION "${mylibname}/lib")

# include
FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION "${mylibname}/include/${mylibname}")

# EOF
