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

	// Create a TCP listening socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create the listening socket." << endl;
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
	
	// UDP PORT INFORMATION
	const char* srcIP = "127.0.0.1";
	const char* destIP = "127.0.0.1";
	sockaddr_in dest;
	sockaddr_in local;
	WSAData data;
	WSAStartup(MAKEWORD(2, 2), &data);
	ULONG* srcAddr = new ULONG;
	ULONG* destAddr = new ULONG;

	local.sin_family = AF_INET;
	inet_pton(AF_INET, srcIP, srcAddr);
	local.sin_addr.s_addr = *srcAddr;
	local.sin_port = htons(0);

	dest.sin_family = AF_INET;
	inet_pton(AF_INET, destIP, destAddr);
	dest.sin_addr.s_addr = *destAddr;
	dest.sin_port = htons(49001);

	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	bind(s, (sockaddr *)&local, sizeof(local));

	// Getting ready to receive data from TCP
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
	const int num_subjects = 16;
	//int subjects[7] = { 1, 3, 4, 16, 17, 18, 20 };
	int subjects[num_subjects] = {1, 3, 4, 8, 13, 16, 17, 18, 20, 21, 25, 29, 37, 38, 39, 58};
	const int total_msg_len = 5 + 36 * num_subjects;

	// Accept and echo message back to client
	char buf[4096];
	unsigned char msg_out[total_msg_len];
	unsigned char msg_out_section[36];
	ZeroMemory(msg_out_section, 36);
	ZeroMemory(msg_out, total_msg_len);
	int idx = 5;

	while (true)
	{
		ZeroMemory(buf, 4096);
		
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

			// Generate msg_out
			// DATA0 header
			msg_out[0] = 68;
			msg_out[1] = 65;
			msg_out[2] = 84;
			msg_out[3] = 65;
			msg_out[4] = 64;

			// Looping over number of subjects and adding them to the msg_out
			for (int n = 0; n <= num_subjects - 1; n++)
			{
				Plane_1.encode(msg_out_section, subjects[n]);
								
				for (int j = 0; j <= 35; j++)
				{
					msg_out[idx] = msg_out_section[j];
					idx++;
				}
			}

			// Printing the message to the console
			for (int j = 0; j < total_msg_len; j++)
			{
				cout << (int)msg_out[j] << ' ';
			}
			cout << endl;

			// Sending the message to UDP port 49001
			sendto(s, (const char*)&msg_out, total_msg_len, 0, (sockaddr *)&dest, sizeof(dest));
			idx = 5;
		}
	}

	// Close
	closesocket(clientSocket);

	// Cleanup Winsock
	WSACleanup();

	return 0;
}

