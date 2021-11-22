#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <winsock2.h>
#include <iostream>

#include <inttypes.h>

/* ethernet communication header */
#include "../header/ethernet_parser.h"
#include "../header/ethernet_structure.h"
#include "../header/ethernet_test_show.h"
/* end ethernet communication header */

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment(lib, "ws2_32");

/* extern */
extern struct MsgState* MsgStateSend;
extern struct MsgState* MsgStateRecv;

extern struct ServerSystemData* ServerData;

extern struct JointParameterSettingStruct* jParamSet;
extern struct JointParameterSettingStruct* jParamGet;

extern struct JointTrajectorySetStruct* jTrajSet;
extern struct JointTrajectorySetStruct* jTrajGet;

extern struct CartesianParameterSettingStruct* cParamSet;
extern struct CartesianParameterSettingStruct* cParamGet;

extern struct CartesianTrajectorySetStruct* cTrajSet;
extern struct CartesianTrajectorySetStruct* cTrajGet;

extern struct JointTargetStruct* jTargetSet;
extern struct JointTargetStruct* jTargetGet;

extern struct CartesianTargetStruct* cTargetSet;
extern struct CartesianTargetStruct* cTargetGet;
/* end extern */

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main()
{
	/* Parser Init */
	EtherNetStructure_Init();
	/* End Parser Init */

	/* Buffer */
	int8_t* sendBuff = (int8_t*)malloc(MsgStateSize);
	int8_t* recvBuff = (int8_t*)malloc(totalSize);
	/* End Buffer */

	int time_stamp = 0;
	uint32_t count = 0;

	/* IpAddress */
	std::string ipAddress = "127.0.0.1"; //"192.168.0.117"; 
	int port = 7;
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[30];
	int strLen;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
		std::cerr << "WSASTartup() error!" << std::endl;
	}
	
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	{
		std::cerr << "socket() error" << std::endl;
		return -1;
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	servAddr.sin_port = htons(port);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		std::cerr << "connect() error!" << std::endl;
		return -1;
	}


	/* Registration */
	MsgStateSend->packetType[0] = 0;
	MsgStateSend->packetType[1] = 0;
	MsgStateSend->commState = REGISTRATION;
	MsgStateSend->payloadSize = MsgStateSize;

	int sendResult = send(hSocket, (char*)MsgStateSend, MsgStateSize, 0);
	if (sendResult == -1)
	{
		printf_s("Registration Send Error!!!\n");
	}

	strLen = recv(hSocket, (char*)MsgStateRecv, MsgStateSize, 0);
	if (strLen == -1){
		printf_s("Registration Recv Error!!!\n");
	}
	/* End Registration */

	while (1) {
		if (MsgStateRecv->commState == REGISTRATION_COMPLETE) {
			printf_s("Registration Complete!!\n");
			/* Servo On */
			MsgStateSend->packetType[0] = 0;
			MsgStateSend->packetType[1] = 0;
			MsgStateSend->commState = SERVO_ON;
			MsgStateSend->payloadSize = MsgStateSize;
			int sendResult = send(hSocket, (char*)MsgStateSend, MsgStateSize, 0);
			if (sendResult == -1)
			{
				printf_s("Registration Send Error!!!\n");
			}
			printf_s("Bytes sent: %d\n", sendResult);

			strLen = recv(hSocket, (char*)recvBuff, totalSize, 0);
			if (strLen == -1) {
				printf_s("Registration Recv Error!!!\n");
			}
			printf_s("Bytes received: %d\n", strLen);
			DataDivideMsgState(recvBuff, MsgStateRecv);
			/* End Servo On */
		}
		else if (MsgStateRecv->commState == SERVO_ON_COMPLETE) {
			printf_s("Servo On Complete!!\n");
			/* Tunning State */
			MsgStateSend->packetType[0] = 15; //  1, 2, 4, 8
			MsgStateSend->packetType[1] = 0;
			MsgStateSend->commState = TUNING_STATE;
			MsgStateSend->payloadSize = MsgStateSize + 
				JointParamSetStructSize + 
				JointTrajSetStructSize + 
				CartesianParamSetStructSize + 
				CartesianTrajSetStructSize;
			
			JointParameterSet(METHOD_FIX);
			JointTrajectorySet(METHOD_FIX);
			CartesianParamSet(METHOD_FIX);
			CartesianTrajectorySet(METHOD_FIX);

			sendBuff = (int8_t*)malloc(MsgStateSize + 
				JointParamSetStructSize + 
				JointTrajSetStructSize +
				CartesianParamSetStructSize + 
				CartesianTrajSetStructSize);

			DataGethering5(
				(int8_t*)MsgStateSend, 
				(int8_t*)jParamSet, 
				(int8_t*)jTrajSet, 
				(int8_t*)cParamSet, 
				(int8_t*)cTrajSet, 
				sendBuff);
			
			int sendResult = send(hSocket, (char*)sendBuff, 
				MsgStateSize +
				JointParamSetStructSize +
				JointTrajSetStructSize +
				CartesianParamSetStructSize +
				CartesianTrajSetStructSize, 
				0);

			if (sendResult == -1){
				printf_s("Tunning State Send Error!!!\n");
			}
			printf_s("Bytes sent: %d\n", sendResult);

			strLen = recv(hSocket, (char*)recvBuff, totalSize, 0);
			if (strLen == -1) {
				printf_s("Tunning State Recv Error!!!\n");
			}
			printf_s("Bytes received: %d\n", strLen);
			DataDivideMsgState(recvBuff, MsgStateRecv);
			if (DataDivideJointParamSettingStruct(recvBuff, MsgStateRecv, jParamGet)) printf_jointParam();
			if (DataDivideJointTrajectorySetStruct(recvBuff, MsgStateRecv, jTrajGet)) printf_jointTraj();
			if (DataDivideCartesianParameterSettingStruct(recvBuff, MsgStateRecv, cParamGet)) printf_CartesianParam();
			if (DataDivideCartesianTrajectorySetStruct(recvBuff, MsgStateRecv, cTrajGet)) printf_CartesianTraj();
			/* End Tunning State */
		}
		else if (MsgStateRecv->commState == TUNING_STATE_COMPLETE) {
			printf_s("Tunning Complete!!\n");
			/* Homing */
			MsgStateSend->packetType[0] = 16;	// 16
			MsgStateSend->packetType[1] = 0;
			MsgStateSend->commState = HOMING;
			MsgStateSend->payloadSize = MsgStateSize + JointTargetStructSize;
			
			JointTargetSet(METHOD_FIX);

			sendBuff = (int8_t*)malloc(
				MsgStateSize +
				JointTargetStructSize
				);
			
			DataGethering2(
				(int8_t*)MsgStateSend,
				(int8_t*)jTargetSet,
				sendBuff);
			int sendResult = send(hSocket, (char*)sendBuff, MsgStateSize + JointTargetStructSize, 0);
			if (sendResult == -1)
			{
				printf_s("Homing State Send Error!!!\n");
			}
			printf_s("Bytes sent: %d\n", sendResult);

			strLen = recv(hSocket, (char*)recvBuff, totalSize, 0);
			if (strLen == -1) {
				printf_s("Homing Recv Error!!!\n");
			}
			printf_s("Bytes received: %d\n", strLen);
			
			DataDivideMsgState(recvBuff, MsgStateRecv); 
			if (DataDivideServerSystemData(recvBuff, MsgStateRecv, ServerData)) printf_ServerSystemData();
			/* End Homing */
		}
		else if (MsgStateRecv->commState == HOMING_COMPLETE) {
			printf_s("Homing Complete!!\n");

			/* Free State */
			MsgStateSend->packetType[0] = 63;
			MsgStateSend->packetType[1] = 0;
			MsgStateSend->commState = FREE_STATE;
			MsgStateSend->payloadSize = MsgStateSize +
				JointParamSetStructSize +
				JointTrajSetStructSize +
				CartesianParamSetStructSize +
				CartesianTrajSetStructSize +
				JointTargetStructSize +
				CartesianTargetStructSize;

			JointParameterSet(METHOD_FIX);
			JointTrajectorySet(METHOD_FIX);
			CartesianParamSet(METHOD_FIX);
			CartesianTrajectorySet(METHOD_FIX);
			JointTargetSet(METHOD_FIX);
			CartesianTargetSet(METHOD_FIX);

			sendBuff = (int8_t*)malloc(
				MsgStateSize +
				JointParamSetStructSize +
				JointTrajSetStructSize +
				CartesianParamSetStructSize +
				CartesianTrajSetStructSize +
				JointTargetStructSize +
				CartesianTargetStructSize);

			DataGethering7(
				(int8_t*)MsgStateSend,
				(int8_t*)jParamSet,
				(int8_t*)jTrajSet,
				(int8_t*)cParamSet,
				(int8_t*)cTrajSet,
				(int8_t*)jTargetSet,
				(int8_t*)cTargetSet,
				sendBuff);

			int sendResult = send(hSocket, (char*)sendBuff,
				MsgStateSize +
				JointParamSetStructSize +
				JointTrajSetStructSize +
				CartesianParamSetStructSize +
				CartesianTrajSetStructSize +
				JointTargetStructSize +
				CartesianTargetStructSize,
				0);
			if (sendResult == -1) {
				printf_s("Tunning State Send Error!!!\n");
			}
			printf_s("Bytes sent: %d\n", sendResult);

			strLen = recv(hSocket, (char*)recvBuff, totalSize, 0);
			if (strLen == -1) {
				printf_s("Free State Start Error!!!\n");
			}
			printf_s("Bytes received: %d\n", strLen);

			DataDivideMsgState(recvBuff, MsgStateRecv);
			if (DataDivideJointParamSettingStruct(recvBuff, MsgStateRecv, jParamGet)) printf_jointParam();
			if (DataDivideJointTrajectorySetStruct(recvBuff, MsgStateRecv, jTrajGet)) printf_jointTraj();
			if (DataDivideCartesianParameterSettingStruct(recvBuff, MsgStateRecv, cParamGet)) printf_CartesianParam();
			if (DataDivideCartesianTrajectorySetStruct(recvBuff, MsgStateRecv, cTrajGet)) printf_CartesianTraj();
			if (DataDivideServerSystemData(recvBuff, MsgStateRecv, ServerData)) printf_ServerSystemData();
			/* End Free State */
		}
		else if (MsgStateRecv->commState == FREE_STATE) {
			printf_s("Free State!!\n");

			/* Free State */
			MsgStateSend->packetType[0] = 63;
			MsgStateSend->packetType[1] = 0;
			MsgStateSend->commState = FREE_STATE;
			MsgStateSend->payloadSize = MsgStateSize +
				JointParamSetStructSize +
				JointTrajSetStructSize +
				CartesianParamSetStructSize +
				CartesianTrajSetStructSize +
				JointTargetStructSize +
				CartesianTargetStructSize;

			JointParameterSet(METHOD_FIX);
			JointTrajectorySet(METHOD_FIX);
			CartesianParamSet(METHOD_FIX);
			CartesianTrajectorySet(METHOD_FIX);
			JointTargetSet(METHOD_FIX);
			CartesianTargetSet(METHOD_FIX);

			sendBuff = (int8_t*)malloc(
				MsgStateSize +
				JointParamSetStructSize +
				JointTrajSetStructSize +
				CartesianParamSetStructSize +
				CartesianTrajSetStructSize +
				JointTargetStructSize +
				CartesianTargetStructSize);

			DataGethering7(
				(int8_t*)MsgStateSend,
				(int8_t*)jParamSet,
				(int8_t*)jTrajSet,
				(int8_t*)cParamSet,
				(int8_t*)cTrajSet,
				(int8_t*)jTargetSet,
				(int8_t*)cTargetSet,
				sendBuff);

			int sendResult = send(hSocket, (char*)sendBuff,
				MsgStateSize +
				JointParamSetStructSize +
				JointTrajSetStructSize +
				CartesianParamSetStructSize +
				CartesianTrajSetStructSize +
				JointTargetStructSize +
				CartesianTargetStructSize,
				0);
			if (sendResult == -1) {
				printf_s("Free State Send Error!!!\n");
			}
			printf_s("Bytes sent: %d\n", sendResult);

			strLen = recv(hSocket, (char*)recvBuff, totalSize, 0);
			if (strLen == -1) {
				printf_s("Free State Recv Error!!!\n");
			}
			printf_s("Bytes received: %d\n", strLen);

			DataDivideMsgState(recvBuff, MsgStateRecv);
			if (DataDivideJointParamSettingStruct(recvBuff, MsgStateRecv, jParamGet)) printf_jointParam();
			if (DataDivideJointTrajectorySetStruct(recvBuff, MsgStateRecv, jTrajGet)) printf_jointTraj();
			if (DataDivideCartesianParameterSettingStruct(recvBuff, MsgStateRecv, cParamGet)) printf_CartesianParam();
			if (DataDivideCartesianTrajectorySetStruct(recvBuff, MsgStateRecv, cTrajGet)) printf_CartesianTraj();
			if (DataDivideServerSystemData(recvBuff, MsgStateRecv, ServerData)) printf_ServerSystemData();
			/* End Free State */
		}
		if(sendBuff != NULL) free(sendBuff);
	}

	// clean up
	free(recvBuff);
	closesocket(hSocket);
	system("pause");
	WSACleanup();
	return 0;
}