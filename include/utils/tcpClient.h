#ifndef __TCP_CLIENT__H__
#define __TCP_CLIENT__H__

#include <string>
class IpAddressPort;
class Msg;



// struct Msg {
//     std::string m_msg;  
//     int m_numberOfRecvBytes;
// };

class TcpClient {
private:
    int m_sfd; // server fd
public:
    TcpClient(const IpAddressPort&);
    ~TcpClient();
    int SendMsg(const std::string& msg);
    Msg RecvMsg();

    int GetSfd() const;
};



#endif