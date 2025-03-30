add_subdirectory(utils)

# PLAYER LIBRARY
add_library(PlayerLib STATIC player.cpp)
target_include_directories(PlayerLib PUBLIC
    ${CMAKE_SOURCE_DIR}/src/engine/utils
    ${CMAKE_SOURCE_DIR}/src/engine/headers
    ${CMAKE_BINARY_DIR}/config
)
target_link_libraries(PlayerLib PRIVATE TextureUtils SDL3::SDL3)

# WORLD LIBRARY
add_library(WorldLib STATIC world.cpp)
target_include_directories(WorldLib PUBLIC ${CMAKE_SOURCE_DIR}/src/engine/utils
    ${CMAKE_SOURCE_DIR}/src/engine/headers
    ${CMAKE_BINARY_DIR}/config
)
target_link_libraries(WorldLib PRIVATE TextureUtils PlayerLib SDL3::SDL3)

# CAMERA LIBRARY
add_library(CameraLib STATIC camera.cpp)
target_include_directories(CameraLib PUBLIC headers)
target_link_libraries(CameraLib PRIVATE SDL3::SDL3)
