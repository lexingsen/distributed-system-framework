# 分布式系统框架

## 一.项目简介

基于Linux平台C++编写的分布式系统框架，非常适合对Linux后端项目有需求的同学学习。

##### 主要包含服务端，负载均衡服务器，客户端，信息采集器，数据库连接池等

##### 涉及到的技术：

（1）Linux下socket编程， 封装TcpServer，TcpClient

（2）Libevent网络框架库的使用

（3）服务器端线程池模型的创建使用以及其负载均衡

（4）MySQL数据库C接口的C++类封装

（5）数据库连接池

（6）单例模式

（7）负载均衡算法之一致性Hash算法

（8）CJson格式的消息封装

（9）MVC设计模式处理具体业务

（10）MD5算法

（11）cmake


## 三.项目依赖及编译
- 三方库
    - libevent
    - mysql
    - json
    - openssl(md5算法)
- 三方库安装
    - sudo apt-get install libevent-dev
    - sudo apt-get install libjsoncpp-dev
    - sudo apt-get install libmysqlclient-dev
    - sudo apt-get install libssl-dev
- 编译
    - 编译环境
        - g++ 7.5.0
        - cmake 3.10.2
        - os ubuntu 18.04
    - 编译
        ```bash
        source build.sh
        ```

## 四.部署
- 1.安装好mysql数据库，配置好用户名和密码(name:root, password:111111)
- 2.按照doc目录下的sql文件创建数据库和表
- 3.首先启动负载均衡服务器
- 4.启动多个服务器，主动连接负载均衡服务器，让其纳管
- 5.客户端连接服务均衡服务器，让其分配一个合适的服务器ip+port,客户端收到ip+port后，主动去与服务器建连



## 五.项目工作流程



## 六.其他的想法
- 负载均衡服务器与服务器之间的连接属于长连接，设置心跳包或keepalive保活机制
- 增加redis缓存层


## 七.项目架构


## 八.Docker镜像

## 八.QQ交流群
823170006
