
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "80"


#include "Utils.h"
#include "GameUtils.h"

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


void createConsole() {
    #define _CRT_SECURE_NO_WARNINGS

    FILE* fpstdin = stdin, * fpstdout = stdout, * fpstderr = stderr;
    AllocConsole();
    freopen_s(&fpstdout, "CONOUT$", "w", stdout);
    freopen_s(&fpstderr, "CONOUT$", "w", stderr);
    freopen_s(&fpstdin, "CONIN$", "r", stdin);

}


int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd){

    createConsole();
#ifdef DEBUG
#endif // DEBUG


    GameManager* gameManager = new GameManager();
    GameManagerCallback* gm = new GameManagerCallback(gameManager);
    Server* srv = new Server(hInstance);
    srv->setScb(gm);
    gameManager->setServer(srv);
    srv->init();
    MSG msg;




  //  srv->socketEvent(&GameManager::Update);














    while (1) {
        srv->ProcessMessage();
    }

    return 0;
}




