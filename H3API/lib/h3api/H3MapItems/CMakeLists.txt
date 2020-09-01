target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3MapItems.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3MapItems.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3MapItems.inl"
)