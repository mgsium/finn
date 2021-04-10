#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define _WIN32_WINNT 0x501

#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")
#define DEFAULT_PORT "27015"

int main(int argc, char **argv) {
    // Initialize WSADATA object
    WSADATA  wsaData;

    // Call WSAStartup
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Check for failure
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    // Create a socket
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Get Address Info
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    std::cout << argv[1] << std::endl;
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create Socket
    SOCKET ConnectSocket = INVALID_SOCKET;
    ptr = result;
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    // Check for connection errors
    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    char * n;
    std::cout << "Press return to end: ";
    std::cin >> n;

    return 0;
}
