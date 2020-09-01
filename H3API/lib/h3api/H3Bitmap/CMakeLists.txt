target_sources(H3API PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/H3Bitmap.cpp")

target_sources(H3API PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/H3Bitmap.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/H3Bitmap.inl"
)