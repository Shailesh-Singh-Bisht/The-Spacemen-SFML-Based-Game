cmake_minimum_required(VERSION 3.13)
project(TheSpacemen VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SFML root and paths
set(SFML_ROOT "C:/Libraries/SFML-2.5.1")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")

# Add includes
include_directories(${SFML_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/include)
link_directories(${SFML_LIBRARY_DIR})

# Add source files
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/*.rc")


# Define the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Use dynamic linking
add_definitions(-DSFML_DYNAMIC)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Output binary to /Spacemen
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Spacemen"
)

# Copy necessary SFML DLLs for runtime (for ReactOS)
if(WIN32)
    file(GLOB SFML_DLLS
        "${SFML_ROOT}/bin/sfml-graphics-2.dll"
        "${SFML_ROOT}/bin/sfml-window-2.dll"
        "${SFML_ROOT}/bin/sfml-system-2.dll"
        "${SFML_ROOT}/bin/sfml-audio-2.dll"
        "${SFML_ROOT}/bin/openal32.dll"
    )
    file(COPY ${SFML_DLLS} DESTINATION "${PROJECT_SOURCE_DIR}/Spacemen")
endif()
