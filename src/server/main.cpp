#include "server.h"


int main() {
  unsigned short port;
	std::cout << "input port:";
	std::cin >> port;
  std::string ip("127.0.0.1");
  Server ser(ip, port, 3);
  return 0;
}
