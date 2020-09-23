cmake_minimum_required (VERSION 2.8)
project (dia2code)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# Enable C11
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

IF(CMAKE_COMPILER_IS_GNUCC)
	SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}  -std=c99   -pthread -g")
	# Hide warnings
	SET(dia2code_warnings
		-Wno-unused-variable
		-Wno-unused-function
		-Wno-pointer-sign
		-Wno-unused-but-set-variable
		-Wno-stringop-truncation
		-Wno-maybe-uninitialized
		)
	STRING(REPLACE ";" " " dia2code_warnings "${dia2code_warnings}")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${dia2code_warnings}")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

# libxml2
if(WIN32)
include_directories(libxml2/include)
find_library(LIBXML2_LIBRARIES NAMES libxml2 PATHS libxml2/lib)
else(WIN32)
if($ENV{MACHINE_ENSEA})
include_directories("/users/perm/gosselin/lib/libxml2/include/libxml2")
set(LIBXML2_LIBRARIES "/users/perm/gosselin/lib/libxml2/lib/libxml2.so")
else($ENV{MACHINE_ENSEA})
find_package (LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})
endif($ENV{MACHINE_ENSEA})
endif(WIN32)

# Sources
file(GLOB_RECURSE main_sources src/*.c)

# Executables
add_executable(dia2code ${main_sources})
target_link_libraries(dia2code ${LIBXML2_LIBRARIES})


