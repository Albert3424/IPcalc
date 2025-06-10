#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <iphlpapi.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFFER_LENGTH 1500
#define SZ_SORRY "Sorry, but all is busy"

int main() 
{
    setlocale(LC_ALL, "");

    WSAData wsaData;
    INT iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != 0) 
    {
        cout << "WSAStartup failed with code: " << iResult << endl;
        return 1;
    }

    addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    addrinfo* result = NULL;
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) 
    {
        cout << "getaddrinfo() failed with code: " << iResult << endl;
        WSACleanup();
        return 1;
    }

    SOCKET connect_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connect_socket == INVALID_SOCKET) 
    {
        cout << "Socket creation failed with code: " << WSAGetLastError() << endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    iResult = connect(connect_socket, result->ai_addr, result->ai_addrlen);
    if (iResult == SOCKET_ERROR) 
    {
        cout << "Unable to connect to Server" << endl;
        closesocket(connect_socket);
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    if (getsockname(connect_socket, (sockaddr*)&client_addr, &client_addr_len) == SOCKET_ERROR) 
    {
        cout << "getsockname failed with code: " << WSAGetLastError() << endl;
    }
    else 
    {
        char client_ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip_str, INET_ADDRSTRLEN);
        int client_port = ntohs(client_addr.sin_port);
        cout << "Connect to server." << endl;
        cout << "IP-адрес клиента: " << client_ip_str << ", Порт: " << client_port << endl;
    }

    CHAR send_buffer[DEFAULT_BUFFER_LENGTH] = "Hello Server, I am Client";
    CHAR recvbuffer[DEFAULT_BUFFER_LENGTH]{};

    do 
    {
        iResult = send(connect_socket, send_buffer, (int)strlen(send_buffer), 0);
        if (iResult == SOCKET_ERROR)
        {
            cout << "Send data failed with code: " << WSAGetLastError() << endl;
            closesocket(connect_socket);
            freeaddrinfo(result);
            WSACleanup();
            return 1;
        }
        cout << iResult << " Bytes sent: " << endl;

        iResult = recv(connect_socket, recvbuffer, DEFAULT_BUFFER_LENGTH, 0);
        if (iResult > 0) 
        {
            cout << "Bytes received: " << iResult << ", Message: " << recvbuffer << endl;
        }
        else if (iResult == 0) 
        {
            cout << "Connection closed" << endl;
        }
        else 
        {
            cout << "Receive failed with code: " << WSAGetLastError() << endl;
        }

        if (strcmp(recvbuffer, SZ_SORRY) == 0) break;

        ZeroMemory(send_buffer, sizeof(send_buffer));
        ZeroMemory(recvbuffer, sizeof(recvbuffer));

        cout << "Введите сообщение: ";
        SetConsoleCP(1251);
        cin.getline(send_buffer, DEFAULT_BUFFER_LENGTH);
        SetConsoleCP(866);


    } while (iResult > 0 && strcmp(send_buffer, "exit"));

    iResult = shutdown(connect_socket, SD_SEND);
    closesocket(connect_socket);
    freeaddrinfo(result);
    WSACleanup();

    system("PAUSE");
    return 0;
}
