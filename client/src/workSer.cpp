/*************************************************************************
    > File Name: workSer.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 06:09:19 PM PST
 ************************************************************************/

#include "workSer.h"
#include "json/json.h"

bool WorkSer::recvFromWorkSer(string& str){
	if(_ser->Recv(str)<=0)
		return false;
	else
		return true;
}

bool WorkSer::sendToWorkSer(const string& message){
	return _ser->Send(message);
}

WorkSer::WorkSer(){
	cout<<"call WorkSer::WorkSer()!"<<endl;
	_ser = new TcpConnect();
	string LBip;
	short LBport;
	cout<<"请输入负载均衡服务器的ip地址:";
	cin>>LBip;
	cout<<"请输入负载均衡服务器的port号:";
	cin>>LBport;
	_ser->Connect(LBip, LBport);

	string str;
	_ser->Recv( str );

	Json::Value val;
	Json::Reader read;
	if( -1 == read.parse(str.c_str(),val) ){
		cout<<"read json fail!errno = "<<errno<<endl;
		return ;
	}
	string serIp = val["ip"].asString();
	short serPort = val["port"].asInt();

	close( _ser->getConnectFd() );
	_ser->Connect(serIp,serPort);
}

