#define _CRT_SECURE_NO_WARNINGS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif 

#include<Windows.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iphlpapi.h>
#include<iostream>
using namespace std;

#pragma comment(lib, "WS2_32.lib")

#define DEFAULT_PORT			"27015"
#define DEFAULT_BUFFER_LENGTH	1500
#define SZ_SORRY  "Sorry, but all is busy"

VOID WINAPI HandleClient(SOCKET ClientSocket);
CONST INT MAX_CLIENTS = 3;
SOCKET clients[MAX_CLIENTS] = {};
DWORD dwThreadIDs[MAX_CLIENTS] = {};
HANDLE hThreads[MAX_CLIENTS] = {};

INT g_connected_clients_count = 0;

void main()
{
	setlocale(LC_ALL, "");

	WSAData wsaData;

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		cout << "Error: WSAstartup failed: " << iResult << endl;
		return;
	}

	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	addrinfo* result = NULL;
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		WSACleanup();
		cout << "Error: getaddrinfo failed: " << iResult << endl;
		return;
	}
	cout << hints.ai_addr << endl;

	SOCKET ListenSocket =
		socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET)
	{
		cout << "Error: Socket creation failed: " << WSAGetLastError() << endl;
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	iResult = bind(ListenSocket, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		cout << "Error: bind failed with code " << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		cout << "Error: Listen failed with code " << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		freeaddrinfo(result);
		WSACleanup();
		return;
	}


	while (true)
	{
		SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
		if (g_connected_clients_count < MAX_CLIENTS)
		{
			clients[g_connected_clients_count] = ClientSocket;
			hThreads[g_connected_clients_count] =
				CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HandleClient, (LPVOID)clients[g_connected_clients_count], 0, &dwThreadIDs[g_connected_clients_count]);
			g_connected_clients_count++;
		}
		else
		{
			CHAR receive_buffer[DEFAULT_BUFFER_LENGTH] = {};
			INT iResult = recv(ClientSocket, receive_buffer, DEFAULT_BUFFER_LENGTH, 0);
			if (iResult > 0)
			{
				cout << "Bytes received: " << iResult << endl;
				cout << "Message: " << receive_buffer << endl;
				INT iSendResult = send(ClientSocket, SZ_SORRY, strlen(SZ_SORRY), 0);
				closesocket(ClientSocket);
			}
		}
	}

	WaitForMultipleObjects(MAX_CLIENTS, hThreads, TRUE, INFINITE);

	closesocket(ListenSocket);
	freeaddrinfo(result);
	WSACleanup();
}

VOID WINAPI HandleClient(SOCKET ClientSocket)
{
	BOOL init = TRUE;
	SOCKADDR_IN peer;
	CHAR address[16] = {};
	INT address_length = 16;
	ZeroMemory(&peer, sizeof(peer));
	getpeername(ClientSocket, (SOCKADDR*)&peer, &address_length);
	inet_ntop(AF_INET, &peer.sin_addr, address, 16);
	int port = ((peer.sin_port & 0xFF) << 8) + (peer.sin_port >> 8);
	cout << address << ":" << port << endl;
	INT iResult = 0;
	CHAR nickname[32]{};
	CHAR recvbuffer[DEFAULT_BUFFER_LENGTH] = {};
	CHAR sendbuffer[DEFAULT_BUFFER_LENGTH] = {};
	int recv_buffer_lennth = DEFAULT_BUFFER_LENGTH;
	do
	{
		ZeroMemory(recvbuffer, sizeof(recvbuffer));
		ZeroMemory(sendbuffer, sizeof(sendbuffer));
		iResult = recvfrom(ClientSocket, recvbuffer, recv_buffer_lennth, 0, (SOCKADDR*)&peer, &address_length);
		if (init)
		{
			strcpy(nickname, strrchr(recvbuffer, ' '));
			sprintf(sendbuffer, "%s connected from [%s:%i]", nickname, address, port);
			init = FALSE;
		}
		else
		{
			sprintf(sendbuffer, "%s[%s:%i] - %s", nickname, address, port, recvbuffer);
		}
		if (iResult > 0)
		{
			inet_ntop(AF_INET, &peer.sin_addr, address, INET_ADDRSTRLEN);
			cout << "Bytes received from " << address << ":" << port << " - " << iResult << " - ";
			cout << recvbuffer << endl;
			CHAR sz_responce[] = "Hello, I am Server! Nice to meet you!";
			for (int i = 0; i < g_connected_clients_count; i++)
			{
				INT iSendResult = send(clients[i], sendbuffer, strlen(sendbuffer), 0);
				if (iSendResult == SOCKET_ERROR)
				{
					cout << "Error: Send failed with code: " << WSAGetLastError() << endl;
					closesocket(ClientSocket);
				}
			}
		}
		else if (iResult == 0)
		{
			cout << "Connection closing..." << endl;
			closesocket(ClientSocket);
		}
		else
		{
			cout << "Error: recv() failed with code " << WSAGetLastError() << endl;
			closesocket(ClientSocket);
		}
	} while (iResult > 0);
}