cmake_minimum_required(VERSION 3.0.0)

project(helloworld)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)





# include_diretories
# include_directories(${WORKING_DIRECTORY})
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/include/logger/)
include_directories(${PROJECT_SOURCE_DIR}/include/utils/)
include_directories(${PROJECT_SOURCE_DIR}/include/thread/)
include_directories(${PROJECT_SOURCE_DIR}/include/threadPool/)
include_directories(${PROJECT_SOURCE_DIR}/include/reactor/)
include_directories(${PROJECT_SOURCE_DIR}/include/view/)
include_directories(${PROJECT_SOURCE_DIR}/include/controller/)
include_directories(${PROJECT_SOURCE_DIR}/include/mainServer/)
include_directories(${PROJECT_SOURCE_DIR}/include/mysqldb/)
include_directories(${PROJECT_SOURCE_DIR}/include/redis/)
add_subdirectory(src)