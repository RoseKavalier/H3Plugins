target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Base.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Base.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Base.inl"
)