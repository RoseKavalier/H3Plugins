target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Stream.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Stream.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Stream.inl"
)