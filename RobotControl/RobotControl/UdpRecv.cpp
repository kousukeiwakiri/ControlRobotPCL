#include "StdAfx.h"
#include "UdpRecv.h"


CUdpRecv::CUdpRecv(void)
{
	WSAStartup(MAKEWORD(2,0), &wsaData);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(UDP_RECV_PORT);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	udp_error_flag=false;
}


CUdpRecv::~CUdpRecv(void)
{
	closesocket(sock);
	WSACleanup();
}

void CUdpRecv::Recv(void)
{


	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);

	//ヘルシーカウンタ確認
	if(theApp.h_count==(int)(buf[HEALTH_COUNT_BUFF_NUMBER])){
		udp_error_flag=true;								//ロボットを停止させる
	}
	theApp.h_count=(int)(buf[HEALTH_COUNT_BUFF_NUMBER]);

	//チェックサム確認
	check_sum=0;
	for(int i=0;i<CHECKSUM_BUFF_NUMBER;i++)check_sum+=(int)(buf[i]);
	if((char)(check_sum)!=buf[CHECKSUM_BUFF_NUMBER]){
		udp_error_flag=true;
	}
	if(udp_error_flag==false){
		theApp.gamepad_right=(int)(buf[GAMEPAD_RIGHT_BUFF_NUMBER]);
		theApp.gamepad_left=(int)(buf[GAMEPAD_LEFT_BUFF_NUMBER]);
		theApp.gamepad_button=(int)(buf[GAMEPAD_BUTTON_BUFF_NUMBER]);
	}
	TRACE(_T("recv!\n"));
}