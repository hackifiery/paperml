cmake_minimum_required(VERSION 3.15)
project(paperml LANGUAGES C)

file(GLOB_RECURSE ALL_SOURCES 
    "src/*.c"
)

add_library(paperml SHARED ${ALL_SOURCES})

target_include_directories(paperml PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(paperml PRIVATE include/paperml)

install(TARGETS paperml EXPORT papermlTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY include/paperml DESTINATION include)