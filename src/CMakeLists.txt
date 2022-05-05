add_definitions("-g -std=c++11") # to_string


# 只需要部分源文件进行编译时
# add_executable(server ./utils/tcpServer.cc ./utils/ipAddressPort.cc ./logger/timeStamp.cc ./logger/message.cc ./logger/logger.cc)
# add_executable(client ./utils/tcpClient.cc ./utils/ipAddressPort.cc ./logger/timeStamp.cc ./logger/message.cc ./logger/logger.cc)
# add_executable(thread ./reactor/reactor.cc  ./thread/thread.cc ./logger/timeStamp.cc ./logger/message.cc ./logger/logger.cc)
# add_executable(threadPool  ./thread/thread.cc ./reactor/reactor.cc ./threadPool/threadPool.cc ./logger/timeStamp.cc ./logger/message.cc ./logger/logger.cc)
# add_executable(reactor ./reactor/reactor.cc ./logger/timeStamp.cc ./logger/message.cc ./logger/logger.cc)
# add_executable(controller ./view/view.cc ./controller/controller.cc ./logger/timeStamp.cc ./logger/message.cc ./logger/logger.cc)
# add_executable(view ./view/view.cc ./logger/timeStamp.cc ./logger/message.cc ./logger/logger.cc)
add_executable(server ./mysqldb/mysqldb.cc ./redis/redis.cc ./utils/ipAddressPort.cc ./controller/controller.cc ./utils/tcpServer.cc ./mainServer/mainServer.cc ./threadPool/threadPool.cc ./thread/thread.cc ./reactor/reactor.cc ./view/view.cc ./logger/timeStamp.cc ./logger/message.cc ./logger/logger.cc)
# add_executable(sql ./mysqldb/mysqldb.cc ./logger/timeStamp.cc ./logger/message.cc ./logger/logger.cc)
# add_executable(redis ./redis/redis.cc ./logger/timeStamp.cc ./logger/message.cc ./logger/logger.cc)
# target_link_libraries(server pthread event)
target_link_libraries(server pthread event hiredis mysqlclient)
# target_link_libraries(redis hiredis)
# target_link_libraries(sql mysqlclient)