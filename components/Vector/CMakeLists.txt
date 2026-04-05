aux_source_directory(src SRC_FILES)

add_library(Vector STATIC ${SRC_FILES})

target_include_directories(Vector PUBLIC include)

target_link_libraries(
    Vector
    m
)