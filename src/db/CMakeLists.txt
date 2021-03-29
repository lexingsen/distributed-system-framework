aux_source_directory(. SRC_LIST)
message(${SRC_LIST})
add_executable(db ${SRC_LIST})
target_link_libraries(db mysqlclient)