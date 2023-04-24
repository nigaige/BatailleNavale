
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "80"
#define WM_SOCKET WM_USER +1 

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Utils.h"
// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    FILE* fpstdin = stdin, * fpstdout = stdout, * fpstderr = stderr;
    AllocConsole();
    freopen_s(&fpstdout, "CONOUT$", "w", stdout);
    freopen_s(&fpstderr, "CONOUT$", "w", stderr);
    freopen_s(&fpstdin, "CONIN$", "r", stdin);


    HINSTANCE& hInstance_ = hInstance;
    HWND hwnd_ = NULL;
    WNDCLASSEX wc_ = { 0 };
    ZeroMemory(&wc_, sizeof(WNDCLASSEX));


    // fill in the struct with the needed information
    wc_.cbSize = sizeof(WNDCLASSEX);
    wc_.style = CS_HREDRAW | CS_VREDRAW;
    wc_.lpfnWndProc = WindowProc;
    wc_.hInstance = hInstance_;
    wc_.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc_.lpszClassName = "WindowClass1";

    // register the window class
    RegisterClassEx(&wc_);

    hwnd_ = CreateWindowEx(0, "WindowClass1", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);


    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
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
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    auto rc = WSAAsyncSelect(ListenSocket, hwnd_, WM_SOCKET, FD_ACCEPT | FD_CLOSE);

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);

    //auto rc = WSAAsyncSelect(ListenSocket, hwnd_, WM_SOCKET, FD_ACCEPT | FD_CLOSE);
    //auto rc = WSAEventSelect(ListenSocket, CreateEvent(NULL, TRUE, FALSE, NULL), FD_ALL_EVENTS);

     // filet de connection
    iResult = listen(ListenSocket, SOMAXCONN);
    MSG msg;

    while (1) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                return false;
            // Traduisez le message et envoyez-le � WindowProc() 
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }





    }


/*


    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }


    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();
*/
    return 0;
}


bool ProcessMessage() 
{
    MSG msg;

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}


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

           // Accept = accept(wParam, NULL, NULL);

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