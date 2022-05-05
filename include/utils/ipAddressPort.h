#ifndef __IPADDRESS_PORT_H__
#define __IPADDRESS_PORT_H__

#include <string>

class IpAddressPort {
private:
    std::string m_ip;
    unsigned short m_port;

public:
    IpAddressPort(std::string, unsigned short);
    std::string ToString() const;
    void SetIpAddress(const std::string& ip);
    std::string GetIpAddress() const;
    void SetPort(unsigned short);
    unsigned short GetPort() const;
};


#endif