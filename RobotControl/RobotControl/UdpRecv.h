#pragma once
#include <stdio.h>
#include <winsock2.h>
#include "RobotControl.h"

#pragma comment(lib,"ws2_32.lib")

#define UDP_RECV_PORT 12345
#define CENTER_GAMEPAD_NUMBER 50
//buff
#define UDP_RECVBUFF_SIZE 8
#define GAMEPAD_RIGHT_BUFF_NUMBER 0
#define GAMEPAD_LEFT_BUFF_NUMBER 1
#define GAMEPAD_BUTTON_BUFF_NUMBER 2
#define HEALTH_COUNT_BUFF_NUMBER 6
#define CHECKSUM_BUFF_NUMBER 7

class CUdpRecv
{
private:
	WSAData wsaData;
	SOCKET sock;
	struct sockaddr_in addr;
	char buf[UDP_RECVBUFF_SIZE];
	int check_sum;
public:
	CUdpRecv(void);
	~CUdpRecv(void);
	void Recv();

	bool udp_error_flag;	//エラーフラグ
};

