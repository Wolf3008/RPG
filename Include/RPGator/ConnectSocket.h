#pragma once

class ConnectSocket //Socket wrapper
{
public:
	//WSADATA wsaData;
	SOCKET connectSocket;

	bool Send(char *packet, int length);
	int Receive(char *packet);

	ConnectSocket(void);
	~ConnectSocket(void);
};