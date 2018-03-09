// DCS_Cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ws2tcpip.h>
#include "Aircraft.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
	// Initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't initialize winsock." << endl;
		return 0;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket." << endl;
		return 0;
	}

	// Bind ip and port to socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(8001);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell winsock the socket is for listening
	listen(listening, SOMAXCONN);

	// Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST]; // Client's remote name
	char service[NI_MAXHOST]; // Service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << service << endl;
	}
	else 
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " <<
			ntohs(client.sin_port) << endl;
	}

	// Close listening socket
	closesocket(listening);

	// Build the aircraft object
	Aircraft Plane_1;
	int subjects[7] = { 20, 3, 17, 21, 16, 4, 37 };

	// Accept and echo message back to client
	char buf[4096];
	unsigned char msg_out[41];
	uint8_t *vp;

	while (true)
	{
		ZeroMemory(buf, 4096);
		ZeroMemory(msg_out, 41);

		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). Quitting." << endl;
			break;
		}

		if (bytesReceived == 0)
		{
			cout << "Client disconnected" << endl;
			break;
		}
		else
		{
			Plane_1.decode(buf);

			

			//for (int n = 0; n <= 6; n++)
			//{
				// "DATA " header
				msg_out[0] = 68;
				msg_out[1] = 65;
				msg_out[2] = 84;
				msg_out[3] = 65;
				msg_out[4] = 0;

				// Subject of the message
				msg_out[5] = subjects[0];

				vp = (uint8_t*)&Plane_1.latitude;
				msg_out[9] = vp[0];
				msg_out[10] = vp[1];
				msg_out[11] = vp[2];
				msg_out[12] = vp[3];

				vp = (uint8_t*)&Plane_1.longitude;
				msg_out[13] = vp[0];
				msg_out[14] = vp[1];
				msg_out[15] = vp[2];
				msg_out[16] = vp[3];

				vp = (uint8_t*)&Plane_1.altitude;
				msg_out[17] = vp[0];
				msg_out[18] = vp[1];
				msg_out[19] = vp[2];
				msg_out[20] = vp[3];

				vp = (uint8_t*)&Plane_1.altitude;
				msg_out[21] = vp[0];
				msg_out[22] = vp[1];
				msg_out[23] = vp[2];
				msg_out[24] = vp[3];

				cout << msg_out << endl;

			//}
		}
	}

	// Close
	closesocket(clientSocket);

	// Cleanup Winsock
	WSACleanup();

	return 0;
}

