ser:main.o tcpServer.o loadBalanceServer.o
	g++ main.o tcpServer.o loadBalanceServer.o -o main -g -lssl -lcrypto -levent -ljson -std=c++11
main.o:main.cpp
	g++ main.cpp -c -g
tcpServer.o:tcpServer.cpp
	g++ tcpServer.cpp -c -g
loadBalanceServer.o:loadBalanceServer.cpp
	g++ loadBalanceServer.cpp -c -g 

clean:
	rm -rf *.o
	rm main