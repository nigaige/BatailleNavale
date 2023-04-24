


#include "Utils.h"

int __cdecl main(int argc, char** argv){

	const char* b = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";

	Client cl;
	cl.init("localhost");
	cl.open();
	cl.sendBuffer(b);
	std::string msgRec = cl.receiveBuffer();
	cl.close();
	
	std::cout<<msgRec;
	std::string pause;
	std::cin >> pause;
}
