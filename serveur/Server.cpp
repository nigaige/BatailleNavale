﻿#include "GameUtils.h"


Server::Server(_In_ HINSTANCE hInstance):hInstance_(hInstance){
}

Server::~Server()
{
}


bool Server::init()
{
    ListenSocket = INVALID_SOCKET;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return false;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;


    createGhostWindow();

    createListening();

	return true;
}

void Server::createGhostWindow(){

    wc_ = { 0 };
    ZeroMemory(&wc_, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc_.cbSize = sizeof(WNDCLASSEX);
    wc_.style = CS_HREDRAW | CS_VREDRAW;
    wc_.lpfnWndProc = &WndProc;
    wc_.hInstance = hInstance_;
    wc_.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc_.lpszClassName = "WindowClass1";


    // register the window class
    RegisterClassEx(&wc_);

    hwnd_ = CreateWindowEx(0, "WindowClass1", 0, 0, 0, 0, 0, 0, 0, 0, hInstance_, NULL);

    SetWindowLongPtr(hwnd_, GWLP_USERDATA, LONG_PTR(this));

}

void Server::createListening(){

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return;
        //THROW?
    }


    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;



    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return;
        //THROW
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return;
        //THROW
    }

   WSAAsyncSelect(ListenSocket, hwnd_, WM_SOCKET, FD_ACCEPT | FD_CLOSE);

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
        //THROW
    }
    freeaddrinfo(result);

    listen(ListenSocket, SOMAXCONN);


}


void Server::openClientSocket(WPARAM wParam){

    // Accept an incoming connection
    if (ClientSocket.size() < maxClient_) {
        ClientSocket.push_back(accept(wParam, NULL, NULL));
        WSAAsyncSelect(ClientSocket[ClientSocket.size() - 1], hwnd_, WM_SOCKET, FD_ALL_EVENTS);
    }
    else {
        //Max connexion reached
        closesocket(accept(wParam, NULL, NULL));
        //TODO Send room full msg
    }
}

void Server::closeClientSocket(WPARAM wParam){
    int sockIndex;
    sockIndex = findSocket(wParam);
    closesocket(ClientSocket[sockIndex]);
    ClientSocket.erase(ClientSocket.begin() + sockIndex);
}

int Server::findSocket(int socketValue){
    int count = 0;
    for (SOCKET sock : ClientSocket) {
        if (sock == socketValue) return count;
        count++;
    }
    return -1;
}






int Server::findBufferLen(int socketIndex){
    string stash = "";
    do {
        iResult = recv(ClientSocket[socketIndex], recvbuf, 1, 0);
        if (iResult < 0) return 0;
        if (recvbuf[0] != ':') {
            stash += recvbuf;
        }
    } while (recvbuf[0] != ':' && iResult > 0);
    std::cout<<stash;
    return stoi(stash);
}

string Server::recieveClientData(int socketIndex)
{
    memset(recvbuf, 0, sizeof(recvbuf));

    string all = "";
    iResult = recv(ClientSocket[socketIndex], recvbuf, findBufferLen(socketIndex), 0);
    if (iResult > 0)
        printf("Bytes received: %d\n", iResult);
    else if (iResult == 0)
        printf("Connection closed\n");
    else {
       // if (WSAGetLastError() == WSAEWOULDBLOCK)break;  //Nothing left to read
        printf("recv failed with error: %d\n", WSAGetLastError());
    }
            
           
    //printf(recvbuf);
    all += recvbuf;
    cout<<all;
    return all;
}

bool Server::sendClientData(int socketIndex, char* msg){

    std::string s = to_string((int)strlen(msg)) + ":";
    char const* pchar = s.c_str();  //use char const* as target type
    iResult = send(ClientSocket[socketIndex], pchar, (int)strlen(pchar), 0);

    iResult = send(ClientSocket[socketIndex], msg, (int)strlen(msg), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        return false;
    }
    printf("Bytes Sent: %ld\n", iResult);
    return true;
}

LRESULT Server::realWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    int sockIndex;
    string data;

    // sort through and find what code to run for the message given
    switch (message)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        return 0;
        // this message is read when the window is closed
    case WM_DESTROY:
    {
        // close the application entirely
        PostQuitMessage(0);
        return 0;
    }
    case WM_SOCKET:
        printf("msg recieved : ");

        switch (WSAGETSELECTEVENT(lParam)) {
        case FD_ACCEPT:
            // Prepare accepted socket for read, write, and close notification
            printf("FD_ACCEPT\n");
            openClientSocket(wParam);
            scb->callBack("", -1);
            break;

        case FD_READ:
            //  Recieved data to be read on the wParam socket
            printf("FD_READ\n");

            sockIndex = findSocket(wParam);
            data = recieveClientData(sockIndex);
            std::cout<<data;
            scb->callBack(data, sockIndex);
            break;

        case FD_WRITE:
            // The socket in wParam is ready for sending data
            printf("FD_WRITE\n");
            break;

        case FD_CLOSE:
            //  Connexion just closed
            printf("FD_CLOSE\n");
            closeClientSocket(wParam);
            break;
        }


        break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}

bool Server::ProcessMessage()
{
    MSG msg;

    while (PeekMessage(&msg, hwnd_, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

void Server::closeServer(){
    while (ClientSocket.size() > 0) {
        closeClientSocket(ClientSocket[0]);
    }
    closesocket(ListenSocket);
    WSACleanup();

}
