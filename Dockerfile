FROM ubuntu:18.04
MAINTAINER lsc
# 安装libevent mysql openssl(md5) json 运行时动态库 主要是.so和头文件

COPY sources.list /etc/apt
RUN apt-get update --fix-missing && apt-get install -y fontconfig --fix-missing -y
RUN apt-get install libevent-dev -y
RUN apt-get install libjsoncpp-dev -y
RUN ln -s /usr/include/jsoncpp/json/ /usr/include/json
RUN cp /lib/x86_64-linux-gnu/libjsoncpp.so /lib/
RUN cp /lib/x86_64-linux-gnu/libjsoncpp.so /usr/lib
RUN apt-get install libmysqlclient-dev -y
RUN apt-get install libssl-dev -y
RUN apt-get install git
RUN git clone https://github.com/lexingsen/distributed-system-framework.git
RUN apt-get install cmake
RUN apt-get install g++
RUN apt-get install gdb
