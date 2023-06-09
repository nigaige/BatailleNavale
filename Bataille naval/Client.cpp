
#include "Utils.h"

using namespace std;
#define WM_SOCKET WM_USER +1 


Client::Client()
{
}

bool Client::init(PCSTR addr) {
	WSADATA wsaData;
	ConnectSocket = INVALID_SOCKET;

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

	addr_ = addr;

	//WSAAsyncSelect(ConnectSocket, hwnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);


	return true;


}

bool Client::open()
{

	// Resolve the server address and port
	iResult = getaddrinfo(addr_, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return false;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return false;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return false;
	}

	printf("connected !\n");
	return true;
}

bool Client::sendBuffer(const char* buffer) {
	//buffer;

	std::string s = patch::to_string((int)strlen(buffer)) + ":";
	char const* pchar = s.c_str();  //use char const* as target type
	iResult = send(ConnectSocket, pchar, (int)strlen(pchar), 0);


	iResult = send(ConnectSocket, buffer, (int)strlen(buffer), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return false;
	}
	printf("Bytes Sent: %ld\n", iResult);

	return true;
}

int Client::findBufferLen() {
	string stash = "";
	do {
		iResult = recv(ConnectSocket, recvbuf, 1, 0);
		if (iResult < 0) return 0;
		if (recvbuf[0] != ':') {
			stash += recvbuf;
		}
	} while (recvbuf[0] != ':' && iResult > 0);
	std::cout << stash;
	return stoi(stash);
}


std::string Client::receiveBuffer() {
	string all = "";
	memset(recvbuf, 0, sizeof(recvbuf));
	cout << "buffer content : " << recvbuf << endl;

	fd_set rfds;

	FD_ZERO(&rfds);
	FD_SET(ConnectSocket, &rfds);

	int recVal = select(ConnectSocket, &rfds, NULL, NULL, &tv);
	switch (recVal) {
	case(0):
		//Timeout
		break;
	case(-1):
		//Error
		break;
	default:

		all = "";
		iResult = recv(ConnectSocket, recvbuf,findBufferLen(), 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			std::cout << recvbuf << std::endl;
		}

		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());
		//printf(recvbuf);
		all += recvbuf;
		//std::cout << "le pb est la => " << iResult << std::endl;

		break;
	}
	return all;

}

void Client::close() {
	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return;
	}


	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

}
