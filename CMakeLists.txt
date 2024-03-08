cmake_minimum_required(VERSION 3.12)
project(tcc)

# set(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_C_FLAGS_RELEASE "-O3 -Wall -Wextra")
SET(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DLOG_LEVEL_DEBUG)
else()
  add_definitions(-DLOG_LEVEL_INFO)
endif()

add_definitions(-DLOG_USE_COLOR)

FILE(GLOB_RECURSE SRCS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c" "3rd/log/*.c")
# set(SRCS ./src/*.c)

add_library(lexer SHARED ${SRCS})

target_include_directories(lexer PRIVATE ./include)
target_include_directories(lexer PRIVATE ./3rd/log)

#=============================
add_executable(tcc demo/tcc.c)
target_link_libraries(tcc lexer)
target_include_directories(tcc PRIVATE ./include)
target_include_directories(tcc PRIVATE ./3rd/log)

#==========install=============
SET(INSTALL_DIR "${CMAKE_SOURCE_DIR}/release")
SET(CMAKE_INSTALL_LIBDIR ${INSTALL_DIR}/lib)
SET(CMAKE_INSTALL_INCLUDEDIR ${INSTALL_DIR}/include)
SET(CMAKE_INSTALL_BINDIR ${INSTALL_DIR}/demo)

INSTALL(TARGETS lexer
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
INSTALL(TARGETS tcc
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
