target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Memory.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Memory.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Memory.inl"
)