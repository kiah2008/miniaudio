cmake_minimum_required(VERSION 3.0.0)
project(miniaudio VERSION 0.1.0)

add_definitions("-DMINIAUDIO_IMPLEMENTATION")

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Android") 
set(extra_libs log)
endif()

add_library(${PROJECT_NAME}  STATIC
    miniaudio.c)

target_include_directories(${PROJECT_NAME} PUBLIC 
${PROJECT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME} dl m ${extra_libs})

option(SUPPORT_PLAYBACK "simple playback" ON)

add_subdirectory(examples)