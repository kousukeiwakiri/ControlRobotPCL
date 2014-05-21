#pragma once
#include <stdio.h>
#include <WinSock2.h>
#include "GamePadData.h"

#pragma comment(lib,"ws2_32.lib")
#define UDP_SEND_ADDR "127.0.0.1"	//‘ŠŽè‚ÌIPƒAƒhƒŒƒX
#define UDP_SEND_PORT 12345

//buff
#define UDP_SENDBUFF_SIZE 8
#define GAMEPAD_RIGHT_BUFF_NUMBER 0
#define GAMEPAD_LEFT_BUFF_NUMBER 1
#define GAMEPAD_BUTTON_BUFF_NUMBER 2
#define HEALTH_COUNT_BUFF_NUMBER 6
#define CHECKSUM_BUFF_NUMBER 7
#define HEALTH_COUNT_MAX 10

class CUDPSend
{
private:
	WSAData wsaData;
	SOCKET sock;
	struct sockaddr_in addr;
	char buf[UDP_SENDBUFF_SIZE];
	CGamePadData gamePadData; 
	int h_count;
	int check_sum;
public:
	CUDPSend(void);
	~CUDPSend(void);
	void send();

};

