lb_server:main.o tcpServer.o  lb.o
	g++ main.o tcpServer.o lb.o -o lb_server -lssl -levent -ljson

main.o:main.cpp
	g++ main.cpp -c 
tcpServer.o:tcpServer.cpp
	g++ tcpServer.cpp -c
lb.o:lb.cpp
	g++ lb.cpp -c
clean:
	rm -rf *.o
	rm lb_server
