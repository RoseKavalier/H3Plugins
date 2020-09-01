target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Bitset.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Bitset.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Bitset.inl"
)