target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Defines.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Defines.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Defines.inl"
)