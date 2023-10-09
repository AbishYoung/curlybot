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
link_libraries(${CURL_LIBRARIES})

# curlybot executable
set(CURLYBOT_SOURCES
    src/curlybot.c
    src/astring.c
    src/querystring.c
    src/urlencode.c
)
set(CURLYBOT_HEADERS
    include/astring.h
    include/querystring.h
    include/urlencode.h
)

add_executable(curlybot ${CURLYBOT_SOURCES} ${CURLYBOT_HEADERS})
target_include_directories(curlybot PUBLIC include)
target_link_libraries(curlybot ${CURL_LIBRARIES})

# Create a custom target to run the program
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/bin/curlybot
    DEPENDS curlybot
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)