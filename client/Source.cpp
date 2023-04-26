


#include "Utils.h"

int __cdecl main(int argc, char** argv){

	const char* b = "MSG";

	Client cl;
	cl->init("localhost");
	cl->open();
	cl->sendBuffer(b);
	std::string msgRec = cl->receiveBuffer();
	cl->close();
	
	std::cout<<msgRec;
	std::string pause;
	std::cin >> pause;
}
