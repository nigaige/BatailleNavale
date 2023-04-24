#pragma once
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "80"

class Socket
{


    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket;
    SOCKET ClientSocket[2];

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;


public:
    bool init();
    bool open();
    bool sendBuffer(const char* buffer);
    std::string receiveBuffer();

    void close();

};

