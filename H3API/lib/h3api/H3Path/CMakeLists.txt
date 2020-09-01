target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Path.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Path.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Path.inl"
)