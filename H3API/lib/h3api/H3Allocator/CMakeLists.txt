target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Allocator.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Allocator.inl"
)