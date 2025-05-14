cmake_minimum_required(VERSION 3.10)
project(Spacemen)

set(CMAKE_CXX_STANDARD 14)

# SFML path
set(SFML_DIR "C:/Libraries/SFML-2.1")

# SDL2 & SDL2_mixer paths from MSYS2 32-bit
set(SDL2_INCLUDE_DIR "C:/msys64/mingw32/include/SDL2")
set(SDL2_LIBRARY_DIR "C:/msys64/mingw32/bin")  # Binaries also contain .lib/.dll for linking with MinGW

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${SFML_DIR}/include
    ${SDL2_INCLUDE_DIR}
)

# Link directories
link_directories(
    ${SFML_DIR}/lib
    ${SDL2_LIBRARY_DIR}
)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(Spacemen ${SOURCES})

# Link SFML libraries
target_link_libraries(Spacemen
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Link SDL2 and SDL2_mixer libraries
target_link_libraries(Spacemen
    SDL2.dll
    SDL2_mixer.dll
)
