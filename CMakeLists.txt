cmake_minimum_required(VERSION 3.15)
project(paperml LANGUAGES C)

file(GLOB_RECURSE ALL_SOURCES 
    "src/*.c"
)

add_library(paperml SHARED ${ALL_SOURCES})

target_include_directories(paperml 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(paperml PUBLIC m)
target_include_directories(paperml PRIVATE include/paperml)
target_compile_options(paperml PRIVATE -std=c89 -pedantic -Wall -Wextra -Werror=implicit-function-declaration -Werror=declaration-after-statement -Wno-sign-compare -ansi -g -O2)

install(TARGETS paperml EXPORT papermlTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY include/paperml DESTINATION include)