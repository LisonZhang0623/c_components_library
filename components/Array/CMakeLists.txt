aux_source_directory(src SRC_FILES)

add_library(Array STATIC ${SRC_FILES})

target_include_directories(Array PUBLIC include)

# target_link_libraries(template template_2)