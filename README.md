# 分布式系统框架

## 一.项目简介

##### 这是基于Linux平台C++编写的分布式系统框架，非常适合对Linux后端项目有需求的同学学习。

##### 主要包含四个文件，分别是服务器端、客户端、负载均衡服务器端以及信息采集器。

##### 涉及到的技术：

（1）Linux下socket编程， 封装TcpServer，TcpClient

（2）Libevent网络框架库的使用

（3）服务器端线程池的使用以及其负载均衡

（4）MySQL数据库C接口的C++类封装

（5）单例模式

（6）负载均衡算法之一致性hash算法

（7）CJson格式的消息封装

（8）MD5算法



## 二.项目工作流程

##### 在具体谈整个项目的工作流程前，先来谈谈客户端到底是如何如服务器建立连接的。在未实现负载均衡服务器前，通常我们会为客户端指定服务器的ip地址和端口，直接连接。但是这样存在的问题是服务器当并发量大到一定的程度时，由于压力太大，出现对客户端响应过慢的情况，甚至可能会出现宕机的情况，

![Image text](https://github.com/lexingsen/image/blob/master/1.png)

##### 为了降低单个服务器的压力，我们可以将服务器进行集群式的管理，使用负载均衡服务器来监管集群服务器上每个服务器当前的压力，进行动态的管理。在这种情况下，客户端就需要先去连接负载均衡服务器，让其分配一个当前负载均衡服务器管理的服务器中压力最小的那个，将其ip地址和端口发送给客户端。客户端拿到负载均衡服务器分配给它的服务器的ip地址和端口后，客户端主动断开与负载均衡服务器的连接，转而去连接服务器。


![Image text](https://github.com/lexingsen/image/blob/master/2.png)


### 现在我们来谈整个项目的部署及流程：

<font size=5 color=blue>1.启动负均衡服务器主函数，并分别设置为服务器和客户端用于连接的socket。</font>

![Image text](https://github.com/lexingsen/image/blob/master/3.png)

<font size=5 color=blue>2.启动MySQL数据库服务。</font>

![Image text](https://github.com/lexingsen/image/blob/master/4.png)

<font size=5 color=blue>3.启动服务器主函数，首先连接负载均衡服务器，之后监听客户端的连接。</font>

![Image text](https://github.com/lexingsen/image/blob/master/5.png)

### 这里可以多连几个服务器到负载均衡服务器，便于观察，我们看负载均衡端的log输出。

![Image text](https://github.com/lexingsen/image/blob/master/6.png)

<font size=5 color=blue>4.启动客户端主函数</font>

![Image text](https://github.com/lexingsen/image/blob/master/7.png)
