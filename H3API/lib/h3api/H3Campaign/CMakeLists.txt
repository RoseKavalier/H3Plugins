target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Campaign.cpp")

target_sources(H3API PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/H3Campaign.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/H3Campaign.inl"
)