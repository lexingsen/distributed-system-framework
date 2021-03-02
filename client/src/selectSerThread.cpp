/*************************************************************************
    > File Name: selectSerThreaed.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 06:07:48 PM PST
 ************************************************************************/

#include "selectSerThread.h"

//信息采集器线程函数用来处理信息采集机器的连接
selectSerThread::selectSerThread(){
	cout<<"please input selectSer ip address:";
	string ip;
	cin>>ip;
	cout<<"please input selectSer port:";
	short port;
	cin>>port;
	_selectSer = new TcpServer(ip,port);//给出信息采集器的ip地址和端口号
	_base = event_base_new();

	//监听信息采集器连接的事件处理器
	cout<<"_selectSer->getListenFd = "<<_selectSer->getListenFd()<<endl;
	struct event* listenEvent = event_new(_base, _selectSer->getListenFd(), EV_READ|EV_PERSIST, selectSerThread::listen_cb, _selectSer);
	if(listenEvent == NULL){
		cerr<<"call selectSerThread::selectSerThread(),select cli listen event create error:errno:"<<errno<<endl;
		return ;
	}
	event_add(listenEvent,NULL);

	//在selectThreadRun中进行监听
	pthread_t id;
	pthread_create(&id,NULL,selectSerThread::selectThreadRun,(void*)_base);
}



void selectSerThread::sendSelect(int fd,string& str){
	cout<<"call selectSerThread::sendSelect()!"<<endl;
	_selectSer->Send(fd,str);
}




