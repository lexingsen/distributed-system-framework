#pragma once

#include <string>

class HashFunction {
public:
    virtual long getHashValue(const std::string& sock) = 0;  
};

class MD5HashFunction : public HashFunction {
    virtual long getHashValue(const std::string& sock);
};