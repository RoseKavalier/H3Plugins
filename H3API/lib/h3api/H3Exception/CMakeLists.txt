target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Exception.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Exception.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Exception.inl"
)