
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/SDL-release-2.28.1")

target_link_libraries(${EXE_NAME} PUBLIC SDL2)
