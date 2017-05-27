# Specify the minimum CMAKE version required
cmake_minimum_required(VERSION 2.8)

# Your project's name
project(Community-Game)

# Make your header file accessible to the compiler
include_directories(include)

# Add all files from the source/ folder to CMake
file(GLOB_RECURSE SRC
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
)

# Define the executable
add_executable(${PROJECT_NAME} ${SRC})

include_directories(deps/SFML/include)
add_definitions(-DSFML_STATIC)
if(WIN32)
        add_definitions( -D_CRT_SECURE_NO_WARNINGS )
endif()

enable_testing()

set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(deps/SFML)

#Lua include
set(LUA_SOURCE_DIR "deps/Lua/src")
include_directories(${LUA_SOURCE_DIR})

#LuaBridge include
include_directories(deps/LuaBridge)

#Lua build
add_subdirectory(${LUA_SOURCE_DIR})

# Copy static files
# Tired of manually copying it
file(COPY res/ DESTINATION Debug/res/)

target_link_libraries(${PROJECT_NAME} lualib sfml-network sfml-graphics sfml-window sfml-system sfml-audio)

# Enable C++ 14
if (NOT UNIX)
	set_target_properties(${PROJECT_NAME} PROPERTIES
	    CXX_STANDARD 14
	    CXX_STANDARD_REQUIRED ON
	    CXX_EXTENSIONS OFF
	)
else()
	add_definitions(-std=c++14)
endif()

