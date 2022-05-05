#include "server.h"


int main(int argc, char* argv[]) {
  LOG_FUNC_TRACE();
  if (argc < 2) {
    std::cout << "[usage] ./server port" << std::endl;
    return 0;
  } 
  std::string ip("127.0.0.1");
  Server ser(ip, atoi(argv[1]), 3);
  return 0;
}
