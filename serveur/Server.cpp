#include "Utils.h"


/*
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    printf("truc\n");

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
        switch (WSAGETSELECTEVENT(lParam)) {
        case FD_ACCEPT:
            printf("FD_ACCEPT");

            // Accept an incoming connection

            accept(wParam, NULL, NULL);

            // Prepare accepted socket for read, write, and close notification

           // WSAAsyncSelect(Accept, hDlg, WM_SOCKET, FD_READ │ FD_WRITE │ FD_CLOSE);

            break;

        case FD_READ:
            printf("FD_READ");

            // Receive data from the socket in wParam

            break;

        case FD_WRITE:
            printf("FD_WRITE");

            // The socket in wParam is ready for sending data

            break;

        case FD_CLOSE:
            printf("FD_CLOSE");

            // The connection is now closed

           // closesocket((SOCKET)wParam);

            break;
        }


        break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}

*/


Server::Server(_In_ HINSTANCE hInstance):hInstance_(hInstance){}

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

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

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

    auto rc = WSAAsyncSelect(ListenSocket, hwnd_, WM_SOCKET, FD_ACCEPT | FD_CLOSE);

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

    iResult = listen(ListenSocket, SOMAXCONN);


}




void Server::openClientSocket()
{
}

void Server::closeClientSocket()
{
}

int Server::findSocket(int socketValue){
    int count = 0;
    for (SOCKET sock : ClientSocket) {
        if (sock == socketValue) return count;
        count++;
    }
    return -1;
}

string Server::recieveClientData(int clientSocket)
{
    string all = "";
    do {
        iResult = recv(ClientSocket[clientSocket], recvbuf, recvbuflen, 0);
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());
        //printf(recvbuf);
        all += recvbuf;
    } while (iResult > 0);
    return all;
}

LRESULT Server::realWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    printf("msg recieved : ");
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
        switch (WSAGETSELECTEVENT(lParam)) {
        case FD_ACCEPT:
            printf("FD_ACCEPT\n");

            // Accept an incoming connection
            if (ClientSocket.size() < maxClient_) {
                ClientSocket.push_back(accept(wParam, NULL, NULL));
                WSAAsyncSelect(ClientSocket[ClientSocket.size()-1], hwnd_, WM_SOCKET, FD_ALL_EVENTS);
            }
            else {
                closesocket(accept(wParam, NULL, NULL));
                //TODO Send room full msg
            }
                

            // Prepare accepted socket for read, write, and close notification


            break;

        case FD_READ:
            printf("FD_READ\n");
            sockIndex = findSocket(wParam);
            data = recieveClientData(sockIndex);
            std::cout<<data;
            // Receive data from the socket in wParam

            //wparam <=socket address



            break;

        case FD_WRITE:
            printf("FD_WRITE\n");

            // The socket in wParam is ready for sending data

            break;

        case FD_CLOSE:
            printf("FD_CLOSE\n");
            sockIndex = findSocket(wParam);
            closesocket(ClientSocket[sockIndex]);
            ClientSocket.erase(ClientSocket.begin() + sockIndex);
            // The connection is now closed

           // closesocket((SOCKET)wParam);

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