target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Structures.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Structures.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Structures.inl"
)