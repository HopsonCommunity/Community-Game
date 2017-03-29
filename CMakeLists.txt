# Specify the minimum CMAKE version required
cmake_minimum_required(VERSION 2.8)

# Your project's name
project(Community-Game)

# Make your header file accessible to the compiler
include_directories(include)
include_directories(dependencies/sfml/include)

add_definitions(-DSFML_STATIC)

# Add all files from the source/ folder to CMake
file(GLOB SRC
    "source/*.cpp"
)

# Use SFML
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(dependencies/sfml)

# Define the executable
add_executable(Community-Game ${SRC})
target_link_libraries(Community-Game sfml-graphics sfml-window sfml-system)

# Enable C++ 11
set_target_properties(Community-Game PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
