
set(lib_shared_target shared_static)

# Generate header files from dia UML files
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../state.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../engine.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../utils.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../ai.dia")

# Find all source files to compile into a library
file(GLOB_RECURSE shared_sources *.cpp)

# Find library Boost
find_package(Boost 1.50 COMPONENTS system filesystem REQUIRED)
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
message(STATUS "Boost include directory: ${Boost_INCLUDE_DIRS}")


# Build the "shared" library and add required includes
add_library(${lib_shared_target} STATIC ${shared_sources} ${jsoncpp_sources})
add_dependencies(${lib_shared_target} generate-headers)
target_include_directories(${lib_shared_target} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${jsoncpp_include_dir}
  )

target_link_libraries(${lib_shared_target}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

# vim: set sw=2 sts=2 et:

