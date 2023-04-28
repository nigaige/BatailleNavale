#pragma once
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "80"
#define WM_SOCKET WM_USER +1 

class GameManager;

class Server
{


    HWND hwnd_;
    HINSTANCE& hInstance_;
    WNDCLASSEX wc_;

    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket;
    std::vector<SOCKET> ClientSocket;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    int maxClient_ = 2;
    //void(*socketEvent_) (string msg, int indexSock);
    ServerCallBack* scb = nullptr;

public:
    void setScb(ServerCallBack* callback) { scb = callback; }
    
    Server(_In_ HINSTANCE hInstance);
    virtual ~Server();
    void maxClient(int maxClient) { maxClient_ = maxClient; }
    int maxClient() { return maxClient_; }
    int GetNBClientConnect() { return ClientSocket.size(); }


    bool init();
    void createGhostWindow();
    void createListening();

    void openClientSocket(WPARAM wParam);
    void closeClientSocket(WPARAM wParam);
    int findSocket(int socketValue);

    int findBufferLen(int socketIndex);
    string recieveClientData(int socketIndex) ;
    bool sendClientData(int socketIndex, char* msg);

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        Server* me = (Server*)(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        if (me) return me->realWndProc(hwnd, msg, wParam, lParam);
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    LRESULT CALLBACK realWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    bool ProcessMessage();
    void closeServer();










};

