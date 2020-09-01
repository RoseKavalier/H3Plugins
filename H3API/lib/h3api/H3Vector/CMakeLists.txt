target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Vector.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Vector.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Vector.inl"
)