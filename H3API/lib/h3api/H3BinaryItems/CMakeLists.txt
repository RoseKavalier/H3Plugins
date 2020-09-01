target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3BinaryItems.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3BinaryItems.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3BinaryItems.inl"
)