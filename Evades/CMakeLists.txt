cmake_minimum_required (VERSION 3.8)

project(Evades)

set(CMAKE_SUPPRESS_REGENERATION true)

set(RESOURCES_SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")
set(RESOURCES_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/resources")

file(GLOB_RECURSE _source_library CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*")
file(GLOB_RECURSE _source_s_list CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/source/*")

add_executable (Evades
	${_source_library}
	${_source_s_list}
	"main.cpp"
)

# Link SFML libraries based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(Evades
        ${CMAKE_SOURCE_DIR}/library/sfml-audio-d.lib
        ${CMAKE_SOURCE_DIR}/library/sfml-graphics-d.lib
        ${CMAKE_SOURCE_DIR}/library/sfml-network-d.lib
        ${CMAKE_SOURCE_DIR}/library/sfml-system-d.lib
        ${CMAKE_SOURCE_DIR}/library/sfml-window-d.lib
    )
else()
    target_link_libraries(Evades
        ${CMAKE_SOURCE_DIR}/library/sfml-audio.lib
        ${CMAKE_SOURCE_DIR}/library/sfml-graphics.lib
        ${CMAKE_SOURCE_DIR}/library/sfml-network.lib
        ${CMAKE_SOURCE_DIR}/library/sfml-system.lib
        ${CMAKE_SOURCE_DIR}/library/sfml-window.lib
    )
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/source)

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