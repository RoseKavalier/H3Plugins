add_subdirectory(Interface)

target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Plugins.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Plugins.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Plugins.inl"
)