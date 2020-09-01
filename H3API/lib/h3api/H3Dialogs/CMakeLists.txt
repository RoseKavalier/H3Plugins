target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Dialogs.cpp")

target_sources(H3API PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Dialogs.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Dialogs.inl"
)