aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./dbConnectionPool DBCONNECTIONPOOL_LIST)
add_definitions("-g")
add_executable(server ${SRC_LIST} ${DB_LIST} ${DBCONNECTIONPOOL_LIST})

target_link_libraries(server pthread json event mysqlclient)