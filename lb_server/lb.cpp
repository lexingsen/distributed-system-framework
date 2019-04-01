/*************************************************************************
    > File Name: lb.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Fri 11 Jan 2019 06:50:03 PM PST
 ************************************************************************/

#include "lb.h"

Node::Node(){_vNodeNum = 0;}
Node::Node(int count, const string& ip, short port){
	this->_ip = ip;
	this->_port = port;
	this->_vNodeNum = count;
}

void Node::setNode(const string& ip, short port){
	this->_ip = ip;
	this->_port = port;
}
int    Node::getVNodeNum(){return this->_vNodeNum;}//获取虚拟节点的个数
short  Node::getPort(){return this->_port;}//获取端口
string Node::getIp(){return this->_ip;}//获取ip地址

VNode::VNode(){this->_hash = -1;this->_node = NULL;}//设置虚拟节点初始hash值为-1  所指向的物理节点的地址为NULL
VNode::VNode(Node* node){this->_hash = -1;this->_node = node;}//
void   VNode::setVNode(Node* node){this->_node = node;}//设置虚拟节点指向的实体节点
Node*  VNode::getPNode(){return this->_node;}		  //获取虚拟节点指向的实体节点
void   VNode::setHash(long hash){this->_hash = hash;}  //设置虚拟节点的哈希值
long   VNode::getHash(){return this->_hash;}           //获取虚拟节点的哈希值


//使用md5散列函数 获取socket字符串对应的hash值    H(socket string) = value string
long MD5HashFun::getHashVal(const string& address){
	long hash = 0;
	unsigned char digest[16];
	MD5_CTX md5;
	MD5_Init(&md5);
	MD5_Update( &md5, address.c_str(), strlen( address.c_str() ) );
	MD5_Final( digest, &md5 );


	for(int i=0; i<4; ++i){
		hash += ( (long)(digest[i*4+3]&0xFF) << 24 )|
				( (long)(digest[i*4+2]&0xFF) << 16 )|
				( (long)(digest[i*4+1]&0xFF) << 8  )|
				( (long)(digest[i*4+0]&0xFF) << 0  );
	}

	return hash;
}

//一致性hash类的构造函数    
ConHash::ConHash(HashFun* pfun){
	if(pfun==NULL){
		cout<<"未给定hash函数!"<<endl;
		return;
	}
	this->_pfun     = pfun;
	this->_vNodeNum = 0;
	this->_VNodeMap = new map<unsigned long, VNode*>();
}
void ConHash::setHashFun(HashFun* pfun){_pfun = pfun;}
int  ConHash::addNode(Node* node){
	if(node == NULL){
		cout<<"实体节点为NULL!"<<endl;
		return -1;
	}
	if( node->getVNodeNum() <= 0 ){
		cout<<"该实体节点没有虚拟节点!"<<endl;
		return -1;
	}

	//获取实体节点的ip和port组成一个字符串，给对应的虚拟节点赋哈希值
	string ipStr  = node->getIp();
	unsigned short port = node->getPort();
	char portStr[10] = {0};
	sprintf(portStr, "%d", port);
	string sock = ipStr+portStr;

	char str[100];
	char num[100];
	VNode* vnode;
	unsigned long hash = 0;
	strcpy(str, sock.c_str() );
	for(int i=0; i< node->getVNodeNum(); ++i){
		vnode = new VNode( node );

		sprintf(num, "%d", i);
		strcat(str, num);

		hash = _pfun->getHashVal( str );//获取str的hash值
		vnode->setHash( hash );
		
		map<unsigned long, VNode*>::iterator it = _VNodeMap->find(hash);
		if( it == _VNodeMap->end() ){
			if(vnode!=NULL){
				_VNodeMap->insert( make_pair(hash, vnode) );
				this->_vNodeNum ++;
			}
		}
		else{
			cout<<"发现冲突，hash = "<<hash <<endl;
		}	
	}
	map<unsigned long, VNode*>::iterator it = _VNodeMap->begin();
	if(it==_VNodeMap->end())cout<<"不存在虚拟节点!"<<endl;
	/*
	cout<<"=====ConHash::addNode()输出虚拟节点开始====="<<endl;
	for(; it!=_VNodeMap->end(); ++it){
		cout<<it->first<<":"<<it->second->getPNode()->getIp()<<","<<it->second->getPNode()->getPort()<<endl;
	}
	cout<<"=====ConHash::addNode()输出虚拟节点结束====="<<endl;
	*/
	cout<<"成功增加服务器：ip"<<node->getIp()<<",port = "<<node->getPort()<<"的虚拟节点!"<<endl;
	return 0;
}

int ConHash::delNode(Node* node){
	if(node == NULL)return -1;
	string ipStr = node->getIp();
	short  port  = node->getPort();

	char portStr[10] = {0};
	sprintf(portStr, "%d", port);
	string sock = ipStr + portStr;//由ip和port组成的字符串socket

	char str[100] = {0};
	char num[100] = {0};
	strcpy( str, sock.c_str() );
	
	unsigned long hash = 0;
	for(int i=0; i<node->getVNodeNum(); ++i){
		sprintf(num, "%d", i);
		strcat(str, num);
		hash = _pfun->getHashVal( str );
		_VNodeMap->erase( hash );
	}
	/*
	cout<<"=====ConHash::delNode()输出虚拟节点开始====="<<endl;
	map<unsigned long, VNode*>::iterator it1 = _VNodeMap->begin();
	if(it1==_VNodeMap->end())cout<<"不存在虚拟节点!"<<endl;
	for(; it1!=_VNodeMap->end(); ++it1){
		cout<<"哈希值:"<<it1->first<<",ip = "<<it1->second->getPNode()->getIp()<<",port = "<<it1->second->getPNode()->getPort()<<endl;
	}
	cout<<"=====ConHash::delNode()输出虚拟节点结束====="<<endl;
	*/
	cout<<"成功删除服务器：ip"<<node->getIp()<<",port = "<<node->getPort()<<"的虚拟节点!"<<endl;
	return 0;
}

Node* ConHash::searchPNode(const string& pnode){
	cout<<"call ConHash::searchPNode()"<<endl;
	unsigned long value = this->_pfun->getHashVal( pnode );
	/*在map中查找比value大的最小节点*/

	map<unsigned long, VNode*>::iterator it = _VNodeMap->lower_bound( value );
	if(it == _VNodeMap->end()){
		it = _VNodeMap->begin();
	}
	VNode* vnode = it->second;
	if(vnode != NULL){
		return vnode->getPNode();
	}
	return NULL;
}

int ConHash::getVNode(){return this->_vNodeNum;}



event_base* LBserver::_base = NULL;
ConHash*    LBserver::_hash = NULL;
TcpServer*  LBserver::_lb_server = NULL;
TcpServer*  LBserver::_lb_client = NULL;
map<int, Node*>* LBserver::_serverMap = NULL;
map<int, struct event*>* LBserver::_eventMap = NULL;

LBserver::LBserver(){
	//定义hash函数
	HashFun* fun = new MD5HashFun();
	//创建一致性hash对象
	_hash = new ConHash( fun );
	_base = event_base_new();
	_serverMap = new map<int, Node*>();
	_eventMap = new map<int, struct event*>();

	string serIp;
	short  serPort;
	cout<<"请输入供服务器连接的套接字ip地址:";
	cin>>serIp;
	cout<<"请输入共服务器连接的套接字port号:";
	cin>>serPort;
	_lb_server = new TcpServer(serIp, serPort);


	string cliIp;
	short  cliPort;
	cout<<"请输入供客户端连接的套接字ip地址:";
	cin>>cliIp;
	cout<<"请输入共客户端连接的套接字port号:";
	cin>>cliPort;
	_lb_client = new TcpServer(cliIp, cliPort);
	


	struct event* listen_ser_event = event_new(_base, _lb_server->getListenFd(), EV_READ|EV_PERSIST, LBserver::listenserver_cb, _lb_server);
	cout<<"_lb_server->getListenFd()"<<_lb_server->getListenFd()<<endl;
	if(NULL == listen_ser_event){
		cerr<<"lb_server listen server event fail!errno = "<<errno<<endl;
		return ;
	}
	struct event* listen_cli_event = event_new(_base, _lb_client->getListenFd(), EV_READ|EV_PERSIST, LBserver::listenclient_cb, _lb_client);
	if(NULL == listen_cli_event){
		cerr<<"lb_server listen client event fail!errno = "<<errno<<endl;
		return ;
	}

	event_add(listen_ser_event, NULL);
	cout<<"启动监听服务器连接!"<<endl;
	event_add(listen_cli_event, NULL);
	cout<<"启动监听客户端连接!"<<endl;
	event_base_dispatch( _base );
}




void LBserver::listenclient_cb(int fd, short event, void*arg){
	TcpServer* cb_client = static_cast<TcpServer*>(arg);
	int cliFd = cb_client->Accept();
	if(-1 == cliFd){
		cerr<<"负载均衡服务器连接客户端错误! errno = "<<errno<<endl;
		return ;
	}
	/*说明有客户端请求连接，解析请求连接的port和ip，做成字符串，取得hash值*/
	cout<<"有客户端进行连接，文件描述符:"<<cliFd<<endl;
	struct sockaddr_in cli;
	socklen_t len = sizeof(cli);

	if(!getpeername(cliFd, (struct sockaddr*)&cli, &len)){
		cout<<"客户端ip:"<<inet_ntoa( cli.sin_addr )<<endl;
		cout<<"客户端port号:"<<ntohs( cli.sin_port )<<endl;
	}

	string ipStr = inet_ntoa(cli.sin_addr);
	short port   = ntohs(cli.sin_port);

	char portStr[10] = {0};
	sprintf(portStr, "%d", port);
	string sock = ipStr + portStr;

	Node* tmp = _hash->searchPNode( sock );
	ipStr = tmp->getIp();
	port  = tmp->getPort();

	cout<<"哈希之后得到的socket:ip = "<<ipStr<<", port = "<<port<<endl;
	Json::Value val;
	val["ip"] = ipStr;
	val["port"] = port;

	_lb_client->Send(cliFd, val.toStyledString());
}


void LBserver::listenserver_cb(int fd, short event, void* arg){
	cout<<"LBserver::listenserver_cb fd = "<<fd<<endl;
	TcpServer* server = static_cast<TcpServer*>( arg );
	int cliFd = server->Accept();
	if(-1==cliFd){
		cerr<<"LBserver::listenserver_cb server->Accpet() fail!errno = "<<errno<<endl;
		return;
	}
	//保存套接字和事件，取消监听时会用到
	struct event* serverEvent = event_new( _base, cliFd, EV_READ|EV_PERSIST, LBserver::io_server, server );
	if(serverEvent == NULL){
		cerr<<"event_new() fail!errno = "<<errno<<endl;
		return;
	}
	_eventMap->insert( make_pair(cliFd, serverEvent) );
	event_add( serverEvent, NULL );
}

void LBserver::io_server(int fd, short event, void* arg){
	TcpServer* server = static_cast<TcpServer*>(arg);
	string message;
	if( 0 >= server->Recv(fd, message) ){
		cerr<<"服务器下线，fd ="<<fd<<endl;

		/*取消监听服务器端套接字*/
		map<int, struct event*>::iterator it1 = _eventMap->find( fd );
		if( it1!=_eventMap->end() ){
			event_free( it1->second );
			_eventMap->erase( fd );
		}

		/*删除已经掉线的服务器*/
		map<int, Node*>::iterator it2 = _serverMap->find( fd );
		if( it2!=_serverMap->end() ){
			Node* node = it2->second;
			_hash->delNode( node );
			cout<<"删除服务器，ip="<<node->getIp()<<", port = "<<node->getPort()<<endl;
			delete node;
			node = NULL;
			_serverMap->erase( fd );
		}
		cout<<"=====输出当前哈希环中存在的服务器节点====="<<endl;
		map<int, Node*>::iterator it3 = _serverMap->begin();
		if(it3==_serverMap->end())cout<<"当前负载均衡服务器中没有服务器节点!"<<endl;
		else{
			for(;it3!=_serverMap->end(); ++it3){
				cout<<"服务器文件描述符:"<<it3->first<<",ip = "<<it3->second->getIp()<<",port = "<<it3->second->getPort()<<endl;
			}
		}
		close( fd );
	}
	else{
		cout<<"服务器上线，fd = "<<fd<<endl;
		Json::Value val;
		Json::Reader read;
		if( read.parse(message.c_str(), val) == 0){
			cerr<<"read fail,errno = "<<errno<<endl;
		}
		string temp = val["ip"].toStyledString();
		temp[temp.size()-2] = 0;
		string ip = temp.c_str() + 1;
		short port = val["port"].asInt();

		Node* node = new Node(10, ip, port);
		_hash->addNode( node );
		_serverMap->insert( make_pair(fd, node) );
		cout<<"监听服务器:ip = "<<ip<<",port = "<<port<<endl;

		map<int, Node*>::iterator it4 = _serverMap->begin();
	 	if( it4 == _serverMap->end())cout<<"负载均衡中未存储此服务器!"<<endl;
		cout<<"=====输出当前哈希环中存在的服务器====="<<endl;
		for(; it4!=_serverMap->end(); ++it4){
			cout<<it4->first<<":"<<"ip = "<<it4->second->getIp()<<",port = "<<it4->second->getPort()<<endl;
		}
	}
}


