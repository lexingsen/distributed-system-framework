aux_source_directory(. SRC_LIST)


add_executable(client ${SRC_LIST})

target_link_libraries(client event pthread jsoncpp)
