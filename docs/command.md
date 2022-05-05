sudo apt-get install manpages-posix manpages-posix-dev



### 引入redis的头文件和动态库
- wget https://github.com/redis/hiredis/archive/refs/tags/v1.0.2.tar.gz
- tar -zxvf v1.0.2.tar.gz
- cd hiredis-1.0.2
- make
- make install
- ldconfig



### redis的镜像及容器的安装部署
docker pull redis
docker run --name dsf-redis -d redis => 容器
docker exec -it 上一步产生的容器id /bin/bash
redis-cli -h 127.0.0.1 -p 6379

### mysql的镜像及容器的安装部署
docker pull mysql:5.7.32
docker run --name dsf-mysql -p 3306:3306 -e MYSQL_ROOT_PASSWORD=你的root密码 -d mysql:5.7.32 => 容器id
docker exec -it 上一步产生的容器id /bin/bash
mysql -uroot -p1234
xxx
xxx
xx
exit;