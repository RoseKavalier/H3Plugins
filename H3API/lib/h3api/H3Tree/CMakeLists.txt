target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Tree.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Tree.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Tree.inl"
)