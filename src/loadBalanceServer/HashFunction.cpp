#pragma once

#include <cstring>
#include <openssl/md5.h>
#include "HashFunction.h"

long MD5HashFunction::getHashValue(const std::string& sock) {
    long hashValue = 0;
    unsigned char x[16];
    bzero(x, sizeof(x));
    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, sock.c_str(), strlen(sock.c_str()));
    MD5_Final(x, &md5);

    for (int i=0; i<4; ++i) {
        hashValue += 
        ((long)(x[i*4+3]&0xff) << 24) |
        ((long)(x[i*4+2]&0xff) << 16) |
        ((long)(x[i*4+1]&0xff) << 8 ) |
        ((long)(x[i*4+0]&0xff) << 0 );
    }
    return hashValue;
}