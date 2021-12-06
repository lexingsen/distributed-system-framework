aux_source_directory(. SRC_LIST)
add_executable(informationCollector ${SRC_LIST})
target_link_libraries(informationCollector jsoncpp)

