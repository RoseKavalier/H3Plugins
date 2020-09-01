target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3String.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3String.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3String.inl"
)