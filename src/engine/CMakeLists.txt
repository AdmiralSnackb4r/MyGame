add_library(PlayerLib STATIC player.cpp)
target_include_directories(PlayerLib PUBLIC headers)

target_link_libraries(PlayerLib PRIVATE SDL3::SDL3)