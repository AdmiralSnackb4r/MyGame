add_subdirectory(engine)

add_executable(MyGame main.cpp)

target_link_libraries(MyGame PRIVATE SDL3::SDL3 PlayerLib WorldLib)