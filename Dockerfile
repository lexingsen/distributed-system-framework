FROM ubuntu:18.04
MAINTAINER lsc

# 编译构建开发工具
RUN apt-get update --fix-missing && apt-get install -y fontconfig --fix-missing -y
RUN apt-get install wget -y
RUN apt-get install gcc -y
RUN apt-get install gdb -y
RUN apt-get install g++ -y
RUN apt-get install make -y
RUN apt-get install vim -y
RUN apt-get install cmake -y
RUN apt-get install git -y

# mysql&redis的中间件  mysql-server redis-server
RUN apt-get install mysql-server -y
RUN apt-get install redis  -y

# libevent&redis&mysql的头文件以及动态库
RUN apt-get install libmysqlclient-dev -y
RUN apt-get install libevent-dev -y


# 1、redis的api和so
# RUN wget https://github.com/redis/hiredis/archive/refs/tags/v1.0.2.tar.gz
# RUN tar -zxvf v1.0.2.tar.gz
# RUN cd hiredis-1.0.2
# RUN make
# RUN make

RUN mkdir /opt/app
COPY . /opt/app/
WORKDIR /opt/app
RUN cp libhiredis.so /usr/local/lib
RUN cp -r ./hiredis  /usr/local/include/hiredis
RUN echo '/usr/local/lib' >>/etc/ld.so.conf
RUN ldconfig


# 2、git下载不了代码  ssh的私钥配置的有问题  git clone dsf的代码
# WORKDIR /tmp
# COPY id_rsa .
# RUN git clone git@gitee.com:lexingsen/dsf-lsc.git