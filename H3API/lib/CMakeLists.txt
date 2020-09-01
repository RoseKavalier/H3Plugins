add_subdirectory(h3api)

target_sources(H3API PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/H3API.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/patcher_x86.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3Types.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/H3API.natvis"
)