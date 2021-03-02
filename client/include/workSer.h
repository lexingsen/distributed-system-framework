/*************************************************************************
    > File Name: workSer.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Sun 25 Nov 2018 05:59:11 AM PST
 ************************************************************************/

#ifndef __WORKSER_H__
#define __WORKSER_H__

#include "tcpConnect.h"
//单例模式
class WorkSer{
public:
	bool recvFromWorkSer(string& str);
	bool sendToWorkSer(const string& message);

	//首先连接负载均衡服务器，负载均衡服务器发送过来一个ip和port
	//使用发送给来的socket去连接服务器

	//通过此静态方法 单例出对象
	static WorkSer* getWorkSer(){
		if(_workSer == NULL){
			if(_workSer == NULL){
				_workSer = new WorkSer();
			}
		}
		return _workSer;
	}
private:
	WorkSer();
	static WorkSer* _workSer;
	TcpConnect* _ser;
};


#endif
