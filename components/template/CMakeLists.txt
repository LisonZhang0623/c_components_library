aux_source_directory(src SRC_FILES)

add_library(template STATIC ${SRC_FILES})

target_include_directories(template PUBLIC include)

# target_link_libraries(template template_2)