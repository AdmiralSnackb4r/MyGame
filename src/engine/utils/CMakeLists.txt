# TEXTURE UTILS LIBRARY
add_library(TextureUtils STATIC textureUtils.cpp)
target_include_directories(TextureUtils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TextureUtils PRIVATE SDL3::SDL3)