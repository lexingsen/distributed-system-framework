ser:main.o tcpServer.o mthread.o threadPool.o control.o view.o sql.o tcpConnect.o
	g++ -g main.o tcpServer.o mthread.o threadPool.o control.o view.o sql.o tcpConnect.o -o ser -L /usr/lib/mysql -lmysqlclient -ljson -levent -lpthread
main.o:main.cpp
	g++ main.cpp -c -g
tcpServer.o:tcpServer.cpp
	g++ tcpServer.cpp -c -g
threadPool.o:threadPool.cpp
	g++ threadPool.cpp -c -g
mthread.o:mthread.cpp 
	g++ mthread.cpp -c -g
control.o:control.cpp
	g++ control.cpp -c -g
view.o:view.cpp
	g++ view.cpp -c -g
sql.o:sql.cpp
	g++ sql.cpp -c -g
tcpConnect.o:tcpConnect.cpp
	g++ tcpConnect.cpp -c -g
clean:
	rm *.o -rf
	rm ser
