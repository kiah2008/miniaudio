project(miniaudio_examples VERSION 0.1.0)

if(SUPPORT_PLAYBACK)
MESSAGE(STATUS "##### building simple playback")
add_executable(simple_playback simple_playback.c)
target_include_directories(simple_playback PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(simple_playback PRIVATE dl m miniaudio)
endif()