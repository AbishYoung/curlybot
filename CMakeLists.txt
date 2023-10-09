cmake_minimum_required(VERSION 3.5)

project(curlybot)

# specify c language and flags
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -pedantic -pedantic-errors -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-value -Wno-unused-result")

# specify binary and object output directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# find and link against libcurl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

# astring static library
set(ASTRING_SOURCES
    src/astring.c
)
set(ASTRING_HEADERS
    include/astring.h
)
add_library(astring STATIC ${ASTRING_SOURCES} ${ASTRING_HEADERS})
target_include_directories(astring PUBLIC include)

# querystring static library
set(QUERYSTRING_SOURCES
    src/querystring.c
)
set(QUERYSTRING_HEADERS
    include/querystring.h
)
add_library(querystring STATIC ${QUERYSTRING_SOURCES} ${QUERYSTRING_HEADERS})
target_include_directories(querystring PUBLIC include)

# curlybot executable
set(CURLYBOT_SOURCES
    src/curlybot.c
)
add_executable(curlybot ${CURLYBOT_SOURCES})
target_include_directories(curlybot PUBLIC include)
target_link_libraries(curlybot astring querystring ${CURL_LIBRARIES})