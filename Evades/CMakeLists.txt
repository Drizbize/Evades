cmake_minimum_required(VERSION 3.10)
project(Evades)

set(CMAKE_SUPPRESS_REGENERATION true)

set(RESOURCES_SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")
set(RESOURCES_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/resources")

file(GLOB_RECURSE _source_library CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*")
file(GLOB_RECURSE _source_s_list CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/source/*")

add_executable(Evades
    ${_source_library}
    ${_source_s_list}
    "main.cpp"
)

#include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/source)

# Find SFML on Linux
find_package(SFML COMPONENTS Graphics Window System REQUIRED)
if(SFML_FOUND)
    target_link_libraries(Evades PRIVATE sfml-graphics sfml-window sfml-system)
else()
    message(FATAL_ERROR "SFML was not found! Make sure SFML is installed and accessible.")
endif()

set_target_properties(Evades PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set_target_properties(Evades PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

# Create the destination directory if it doesn't exist
file(MAKE_DIRECTORY "${RESOURCES_DEST_DIR}")

# Get a list of all files in the destination resources directory
file(GLOB RESOURCES_FILES "${RESOURCES_DEST_DIR}/*")

if (RESOURCES_FILES)
    file(REMOVE ${RESOURCES_FILES})
endif()

file(COPY "${RESOURCES_SOURCE_DIR}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")