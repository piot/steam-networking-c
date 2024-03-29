cmake_minimum_required(VERSION 3.17)
project(steam_networking C)

set(CMAKE_C_STANDARD 99)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(isDebug TRUE)
else()
  message("no debug")
  set(isDebug FALSE)
endif()

if(isDebug)
  message("Debug build detected")
  add_compile_definitions(CONFIGURATION_DEBUG TYRAN_CONFIGURATION_DEBUG)
  set(CONFIGURATION_DEBUG 1)
endif()


add_compile_definitions(TORNADO_OS_MACOS)

set(DEPS ../../deps/)

file(GLOB lib_src FOLLOW_SYMLINKS "*.c")

add_library(steam_networking STATIC ${lib_src})

target_compile_options(
  steam_networking
  PRIVATE -Wall
          -Wextra
          -Wshadow
          -Wstrict-aliasing
          -pedantic
          -Wno-declaration-after-statement
          -Wno-extra-semi-stmt
          -Wno-undef
          -Wno-unused-variable
          -Wno-unused-parameter
          -Wno-padded
          -Werror=implicit-function-declaration
          -Werror=incompatible-pointer-types
          -Werror=missing-prototypes
          -Werror=int-conversion
          -Werror=return-type
          -Werror=incompatible-function-pointer-types
)

if(COMPILER_CLANG)
  target_compile_options(steam_networking PRIVATE -Wmost -Weverything
                                      -Werror=missing-variable-declarations)
endif()

target_include_directories(steam_networking PUBLIC ${DEPS}piot/steam-api-c/src/include)
target_include_directories(steam_networking PUBLIC ${DEPS}piot/clog/src/include)
target_include_directories(steam_networking PUBLIC ${DEPS}piot/tiny-libc/src/include)
target_include_directories(steam_networking PUBLIC ${DEPS}piot/atheneum/src/include)
target_include_directories(steam_networking PUBLIC ../include)
