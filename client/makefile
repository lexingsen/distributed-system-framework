cli:main.o system.o system.o worker.o workSer.o selectSerThread.o tcpConnect.o tcpServer.o
	g++ main.o system.o worker.o workSer.o selectSerThread.o tcpConnect.o tcpServer.o -o cli -g -ljson -levent
main.o:main.cpp
	g++ main.cpp -c
system.o:system.cpp
	g++ system.cpp -c
worker.o:worker.cpp
	g++ worker.cpp -c
workSer.o:workSer.cpp
	g++ workSer.cpp -c
selectSerThread.o:selectSerThread.cpp	
	g++ selectSerThread.cpp -c
tcpConnect.o:tcpConnect.cpp
	g++ tcpConnect.cpp -c
tcpServer.o:tcpServer.cpp
	g++ tcpServer.cpp -c
clean:
	rm *.o -rf
	rm cli
