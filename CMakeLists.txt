cmake_minimum_required(VERSION 3.13)

project(Spacemen LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Target 32-bit build explicitly (if needed)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "This project requires 32-bit build, but 64-bit is detected.")
endif()

# Specify your SFML installation directories
set(SFML_ROOT "C:/Libraries/SFML-2.1")

# Include directories for SFML and your project headers
include_directories(
    ${SFML_ROOT}/include
    ${PROJECT_SOURCE_DIR}/include
)

# Source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/MenuScreen.cpp
    src/StoryScreen.cpp          # new story screen cpp
    src/GameOverScreen.cpp
    src/WinScreen.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Laser.cpp
)

# Create executable
add_executable(Spacemen ${SOURCES})

# Link SFML libraries dynamically using import libs (.a)
# Important: Use -lsfml-xxx to link against the import libs in SFML_ROOT/lib
target_link_libraries(Spacemen
    ${SFML_ROOT}/lib/libsfml-graphics.a
    ${SFML_ROOT}/lib/libsfml-window.a
    ${SFML_ROOT}/lib/libsfml-system.a
    ${SFML_ROOT}/lib/libsfml-audio.a
)

# Post-build: Copy necessary SFML DLLs and OpenAL DLL to output directory (next to exe)
add_custom_command(TARGET Spacemen POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_ROOT}/bin/sfml-graphics-2.dll"
        "${SFML_ROOT}/bin/sfml-window-2.dll"
        "${SFML_ROOT}/bin/sfml-system-2.dll"
        "${SFML_ROOT}/bin/sfml-audio-2.dll"
        "${SFML_ROOT}/bin/openal32.dll"
        $<TARGET_FILE_DIR:Spacemen>
)

# Optional: copy assets folder to build dir on build
add_custom_command(TARGET Spacemen POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Spacemen>/assets"
)

# Additional compiler flags (if needed, e.g., for debugging)
target_compile_options(Spacemen PRIVATE -Wall -Wextra -Wpedantic)

# Set output directory for the executable (optional)
set_target_properties(Spacemen PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)
