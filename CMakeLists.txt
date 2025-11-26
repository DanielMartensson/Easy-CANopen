cmake_minimum_required(VERSION 3.16.0)

project(Easy-CANopen C)

# Default value for EASY_CAN_OPEN_TARGET_PLATFORM if not set externally
#set(EASY_CAN_OPEN_TARGET_PLATFORM INTERNAL_CALLBACK)
if(NOT DEFINED EASY_CAN_OPEN_TARGET_PLATFORM)
    set(EASY_CAN_OPEN_TARGET_PLATFORM NO_PLATFORM)
    message(STATUS "EASY_CAN_OPEN_TARGET_PLATFORM = Using NO PLATFORM")
endif()

# Make it a compile definition
add_compile_definitions(EASY_CAN_OPEN_TARGET_PLATFORM=${EASY_CAN_OPEN_TARGET_PLATFORM})

# Collect sources
file(GLOB_RECURSE ALL_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.c")
set(MAIN_SRC "${CMAKE_CURRENT_SOURCE_DIR}/Src/Main.c")
list(REMOVE_ITEM ALL_SOURCE_FILES ${MAIN_SRC})

# Library
add_library(easycanopen STATIC ${ALL_SOURCE_FILES})
target_include_directories(easycanopen PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Src")

# Executable
add_executable(main ${MAIN_SRC})
target_link_libraries(main PRIVATE easycanopen)
target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Src")
