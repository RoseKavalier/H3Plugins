cmake_minimum_required(VERSION 3.17)

set(CMAKE_GENERATOR_PLATFORM Win32)

project (H3API)

add_library(H3API STATIC "")

add_subdirectory(include)

add_compile_definitions(_H3API_LIBRARY_)

file(GLOB_RECURSE _source_list *.cpp* *.inl* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

if(NOT BINARY_CUSTOM_DIR)
    set_target_properties(H3API PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
    install(TARGETS H3API DESTINATION lib)
endif()