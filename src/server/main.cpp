#include "server.h"


int main() {
  LOG_FUNC_TRACE();
  //unsigned short port;
	//std::cout << "input port:";
	//std::cin >> port;
  std::string ip("127.0.0.1");
  Server ser(ip, 7000, 3);
  return 0;
}
