aux_source_directory(src SRC_FILES)

add_library(HashTable STATIC ${SRC_FILES})

target_include_directories(HashTable PUBLIC include)

# target_link_libraries(template template_2)