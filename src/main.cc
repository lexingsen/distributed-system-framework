
#include <string>
#include <iostream>


// input : /home/ubuntu/test/src/utils/tcpServer.cc
// output : tcpServer.cc   push requst -> code review


std::string GetSubStringAfterLastXianGang1(std::string msg) {
     int len=msg.size();
  std::string s;
  int i=len -1;
  for(;i>0;i--)
  {
    if(msg[i]=='/')
    {
      break;
    }
  }
  s=msg.substr(i + 1, len-i);
  return s;
}

std::string GetSubStringAfterLastXianGang2(std::string msg) {
    const char* c = msg.c_str();
    const char* p = NULL;
    while (*c != '\0') {
        if (*c == '/') {
            p = c + 1;
        } 
        ++c;
    }
    return p;
}

 int main() {
    std::string msg = "/home/ubuntu/test/src/utils/tcpServer.cc";
    std::string res = GetSubStringAfterLastXianGang2(msg);
    std::cout << res << std::endl;
    return 0;
 }