#pragma once



#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "80"

class Client{
private:
	PCSTR addr_ = "";
	char* buff_;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;

	SOCKET ConnectSocket;

	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;

public:
	bool init(PCSTR addr);
	bool open();
	bool sendBuffer(const char* buffer);
	std::string receiveBuffer();
	void close();


};

