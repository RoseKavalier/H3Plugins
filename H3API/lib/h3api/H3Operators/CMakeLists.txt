target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Operators.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Operators.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Operators.inl"
)