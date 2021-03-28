aux_source_directory(. SRC_LIST)

add_executable(server ${SRC_LIST})

target_link_libraries(server)