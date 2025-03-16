# PLAYER LIBRARY
add_library(PlayerLib STATIC player.cpp)
target_include_directories(PlayerLib PUBLIC headers)
target_link_libraries(PlayerLib PRIVATE SDL3::SDL3)

# WORLD LIBRARY
add_library(WorldLib STATIC world.cpp)
target_include_directories(WorldLib PUBLIC headers)
target_link_libraries(WorldLib PRIVATE SDL3::SDL3)