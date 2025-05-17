cmake_minimum_required(VERSION 3.13)

project(TheSpacemen VERSION 1.0 LANGUAGES CXX)

# Force 32-bit build (if on 64-bit machine with mingw)
set(CMAKE_GENERATOR_PLATFORM Win32)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    "C:/Libraries/SFML-2.1/include"
    "C:/Libraries/SFML-2.1/include/SFML"
    "C:/msys64/mingw32/include"
    ${PROJECT_SOURCE_DIR}/include
)

# Source files
file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Executable
add_executable(TheSpacemen ${SOURCES})

# Link directories (where SFML libs reside)
link_directories("C:/Libraries/SFML-2.1/lib")

# Link SFML dynamically (do NOT link sfml-main if you have your own main)
target_link_libraries(TheSpacemen
    sfml-graphics
    sfml-window
    sfml-system
)

# Ensure using dynamic SFML DLLs (not static)
add_definitions(-DSFML_DYNAMIC)

# Set output directory for built executable (optional)
set_target_properties(TheSpacemen PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

# Optional: Copy SFML DLLs to output directory after build (manual step recommended)
