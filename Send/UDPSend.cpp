#include "StdAfx.h"
#include "UDPSend.h"


CUDPSend::CUDPSend(void)
{
	WSAStartup(MAKEWORD(2,0), &wsaData);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(UDP_SEND_PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(UDP_SEND_ADDR);
	h_count=0;
}


CUDPSend::~CUDPSend(void)
{
		closesocket(sock);
		WSACleanup();
}

void CUDPSend::send(void)
{
		gamePadData.Update();
		memset(buf,0,sizeof(buf));
		check_sum=0;
		//gamepadデータ
		buf[GAMEPAD_RIGHT_BUFF_NUMBER]=(char)(gamePadData.right);
		buf[GAMEPAD_LEFT_BUFF_NUMBER]=(char)(gamePadData.left);
		buf[GAMEPAD_BUTTON_BUFF_NUMBER]=(char)(gamePadData.button);
		
		//ヘルシーカウンタ
		h_count+=1;
		if(h_count==HEALTH_COUNT_MAX+1)h_count=0;
		buf[HEALTH_COUNT_BUFF_NUMBER]=(char)(h_count);

		//チェックサム
		for(int i=0;i<CHECKSUM_BUFF_NUMBER;i++)check_sum+=buf[i];
		buf[CHECKSUM_BUFF_NUMBER]=(char)(check_sum);

		sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
		TRACE(_T("send!\n"));
}