/*************************************************************************
    > File Name: Transfer.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Sun 25 Nov 2018 05:59:11 AM PST
 ************************************************************************/

#ifndef __WORKSER_H__
#define __WORKSER_H__

#include "tcpConnect.h"
//单例模式

class Transfer {
public:
	bool recvFromMainSer(std::string& msg);
	bool sendToMainSer(const std::string& msg);

	static Transfer* getInstance() {
		static Transfer transfer;
		return &transfer; 
	}
private:
	Transfer();
	TcpConnect* m_transferClient;
};



#endif
