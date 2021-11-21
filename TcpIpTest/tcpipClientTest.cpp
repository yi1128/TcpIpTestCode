#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <winsock2.h>
#include <iostream>

/* ethernet communication header */
#include "ethernet_structure.h";
#include "ethernet_parser.h";
/* end ethernet communication header */

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment(lib, "ws2_32");

#define METHOD_FIX 1
#define METHOD_CONTINUOUS 2

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

extern struct JointTargetStruct* jTarget;
extern struct JointTargetStruct* jTargetGet;

extern struct CartesianTargetStruct* cTarget;
extern struct CartesianTargetStruct* cTargetGet;
/* end extern */

void JointParameterSet(int method);
void JointTrajectorySet(int method);

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
	int8_t* Buffer;
	int8_t* inBuff;
	int8_t* inBuff2;
	int8_t* inBuff3;

	Buffer = (int8_t*)malloc(sizeof(int8_t));
	inBuff = (int8_t*)malloc(sizeof(int8_t));
	inBuff2 = (int8_t*)malloc(sizeof(int8_t));
	inBuff3 = (int8_t*)malloc(sizeof(int8_t));
	/* End Buffer */

	int time_stamp = 0;
	uint32_t count = 0;

	std::string ipAddress = "127.0.0.1"; //"192.168.0.117"; 
	int port = 7;
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[30];
	int strLen;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		std::cerr << "WSASTartup() error!" << std::endl;

	std::cerr << "WSASTartup()!" << std::endl;
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	{
		std::cerr << "socket() error" << std::endl;
		return -1;
	}
	std::cerr << "socket()!" << std::endl;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	servAddr.sin_port = htons(port);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		std::cerr << "connect() error!" << std::endl;
		return -1;
	}
	std::cerr << "Connect Complete!!" << std::endl;

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
			strLen = recv(hSocket, (char*)MsgStateRecv, MsgStateSize, 0);
			if (strLen == -1) {
				printf_s("Registration Recv Error!!!\n");
			}
			printf_s("%d\n", MsgStateRecv->commState);
			/* End Servo On */
		}
		else if (MsgStateRecv->commState == SERVO_ON_COMPLETE) {
			printf_s("Servo On Complete!!\n");
			/* Tunning State */
			MsgStateSend->packetType[0] = 3; // 1 : JointParameterSettingStruct 2 : JointTrajectorySetStruct
			MsgStateSend->packetType[1] = 0;
			MsgStateSend->commState = TUNING_STATE;
			MsgStateSend->payloadSize = MsgStateSize + JointParamSetStructSize + JointTrajSetStructSize;
		
			JointParameterSet(METHOD_FIX);
			JointTrajectorySet(METHOD_FIX);
		
			
			printf_s("Convert To Buffer\n");
			MsgStateToBuffer(MsgStateSend,inBuff);
			JointParameterSettingStructToBuffer(jParamSet, inBuff2);
			JointTrajectorySetStructToBuffer(jTrajSet, inBuff3);
			printf_s("Data Gethering\n");

			printf_s("%d %d %d\n", _msize(inBuff), _msize(inBuff2), _msize(inBuff3));
			DataGethering3(inBuff, inBuff2, inBuff3, Buffer);
			printf_s("%d\n", _msize(Buffer));
			int sendResult = send(hSocket, (char*)Buffer, MsgStateSend->payloadSize, 0);
			if (sendResult == -1)
			{
				printf_s("Registration Send Error!!!\n");
			}

			strLen = recv(hSocket, (char*)MsgStateRecv, MsgStateSize, 0);
			if (strLen == -1) {
				printf_s("Registration Recv Error!!!\n");
			}

			//free(Buffer);
			//free(inBuff);
			//free(inBuff2);
			//free(inBuff3);
			/* End Tunning State */
		}
		else if (MsgStateRecv->commState == TUNING_STATE_COMPLETE) {
			/* Homing */

			/* End Homing */
		}
		else if (MsgStateRecv->commState == HOMING_COMPLETE) {
		
				/* Free State */
				//int sendResult = send(hSocket, (char*)&sendData, sizeof(TCP_COMM_TEST_SET), 0);
				if (sendResult == -1)
				{

				}

				//strLen = recv(hSocket, (char*)&recvData, sizeof(TCP_COMM_TEST_SET), 0);
				if (strLen == -1)
				{

					break;
				}
				/* End Free State */
		}
	}
	closesocket(hSocket);
	WSACleanup();
	system("pause");
	return 0;
}

void JointParameterSet(int method) 
{
	if (method == METHOD_FIX) {
		jParamSet->jointTorquePgain[0] = 1.11;
		jParamSet->jointTorquePgain[1] = 2.22;
		jParamSet->jointTorquePgain[2] = 3.33;
		jParamSet->jointTorquePgain[3] = 4.44;

		jParamSet->jointTorqueIgain[0] = 5.55;
		jParamSet->jointTorqueIgain[1] = 6.66;
		jParamSet->jointTorqueIgain[2] = 7.77;
		jParamSet->jointTorqueIgain[3] = 8.88;

		jParamSet->jointTorqueDgain[0] = 9.99;
		jParamSet->jointTorqueDgain[1] = 10.111;
		jParamSet->jointTorqueDgain[2] = 11.111;
		jParamSet->jointTorqueDgain[3] = 12.222;

		jParamSet->jointPositionPgain[0] = 13.33;
		jParamSet->jointPositionPgain[1] = 14.44;
		jParamSet->jointPositionPgain[2] = 15.55;
		jParamSet->jointPositionPgain[3] = 16.6666;

		jParamSet->jointPositionIgain[0] = 17.777;
		jParamSet->jointPositionIgain[1] = 18.888;
		jParamSet->jointPositionIgain[2] = 19.999;
		jParamSet->jointPositionIgain[3] = 20.222;

		jParamSet->jointPositionDgain[0] = 21.111;
		jParamSet->jointPositionDgain[1] = 22.222;
		jParamSet->jointPositionDgain[2] = 23.3333;
		jParamSet->jointPositionDgain[3] = 24.4444;

		jParamSet->jointGravityGain[0] = 25.5555;
		jParamSet->jointGravityGain[1] = 26.6666;
		jParamSet->jointGravityGain[2] = 27.7777;
		jParamSet->jointGravityGain[3] = 28.8888;

		jParamSet->jointFrictionGain[0] = 29.9999;
		jParamSet->jointFrictionGain[1] = 30.1111;
		jParamSet->jointFrictionGain[2] = 31.1111;
		jParamSet->jointFrictionGain[3] = 32.22222;

		jParamSet->jointCurrentGain[0] = 33.33333;
		jParamSet->jointCurrentGain[1] = 34.44444;
		jParamSet->jointCurrentGain[2] = 35.555;
		jParamSet->jointCurrentGain[3] = 36.6666;

		jParamSet->jointConstantTorque[0] = 37.7777;
		jParamSet->jointConstantTorque[1] = 38.8888;
		jParamSet->jointConstantTorque[2] = 39.99999;
		jParamSet->jointConstantTorque[3] = 40.0141;

		jParamSet->jointConstantSpring[0] = 41.1111;
		jParamSet->jointConstantSpring[1] = 42.2222;
		jParamSet->jointConstantSpring[2] = 43.3333;
		jParamSet->jointConstantSpring[3] = 44.4444;

		jParamSet->jointConstantEfficiency[0] = 45.5555;
		jParamSet->jointConstantEfficiency[1] = 46.6666;
		jParamSet->jointConstantEfficiency[2] = 47.777;
		jParamSet->jointConstantEfficiency[3] = 48.8;
	}
	else if (method == METHOD_CONTINUOUS) {

	}
}

void JointTrajectorySet(int method)
{
	if (method == METHOD_FIX) {
		jTrajSet->JointTrajecotryTime[0] = 200.11;
		jTrajSet->JointTrajecotryTime[1] = 321.11;
		jTrajSet->JointTrajecotryTime[2] = 4631.11;
		jTrajSet->JointTrajecotryTime[3] = 567.11;

		jTrajSet->JointTrajectoryAcc[0] = 3123.156;
		jTrajSet->JointTrajectoryAcc[1] = 76345.156;
		jTrajSet->JointTrajectoryAcc[2] = 364523.156;
		jTrajSet->JointTrajectoryAcc[3] = 234123.156;
	}
	else if (method == METHOD_CONTINUOUS) {

	}
}