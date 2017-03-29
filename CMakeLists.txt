# Specify the minimum CMAKE version required
cmake_minimum_required(VERSION 2.8)

# Your project's name
project(Community-Game)

# Make your header file accessible to the compiler
include_directories(include)

# CMake Modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

# Add all files from the source/ folder to CMake
file(GLOB SRC
    "source/*.cpp"
)

# Use SFML
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

# Define the executable
add_executable(Community-Game ${SRC})

# Enable C++ 11
set_target_properties(Community-Game PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
