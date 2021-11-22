
#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include<inttypes.h>

/* ethernet communication header */
#include "../header/ethernet_parser.h"
#include "../header/ethernet_structure.h"
#include "../header/ethernet_test_show.h"
/* end ethernet communication header */

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_PORT "7"

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

int __cdecl main(void)
{
    /* Parser Init */
    EtherNetStructure_Init();
    /* End Parser Init */

    /* Buffer */
    int8_t* sendBuff;
    int8_t* recvBuff = (int8_t*)malloc(totalSize);
    /* End Buffer */

    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;

    /* Initialize Winsock */
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    /* Resolve the server addressand port */
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf_s("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    /* Create a SOCKET for connecting to server */
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf_s("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    /* Setup the TCP listening socket */
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf_s("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf_s("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    /* Accept a client socket */
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf_s("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    /* No longer need server socket */
    closesocket(ListenSocket);

    /* Receive until the peer shuts down the connection */
    do {
        iResult = recv(ClientSocket, (char*)recvBuff, totalSize, 0);
        if (iResult > 0) {
            printf_s("Bytes received: %d\n", iResult);
            if(DataDivideMsgState(recvBuff, MsgStateRecv))
            if(DataDivideJointParamSettingStruct(recvBuff, MsgStateRecv, jParamGet)) printf_jointParam();
            if(DataDivideJointTrajectorySetStruct(recvBuff, MsgStateRecv, jTrajGet)) printf_jointTraj();
            if(DataDivideCartesianParameterSettingStruct(recvBuff, MsgStateRecv, cParamGet)) printf_CartesianParam();
            if(DataDivideCartesianTrajectorySetStruct(recvBuff, MsgStateRecv, cTrajGet)) printf_CartesianTraj();
            if(DataDivideJointTaregetStruct(recvBuff, MsgStateRecv, jTargetGet)) printf_JointTarget();
            if(DataDivideCartesianTargetStruct(recvBuff, MsgStateRecv, cTargetGet)) printf_CartesianTarget();
            if(DataDivideServerSystemData(recvBuff, MsgStateRecv, ServerData)) printf_ServerSystemData();
            
            if (MsgStateRecv->commState == REGISTRATION){
                printf_s("Registration\n");
                /* Registration */
                MsgStateSend->packetType[0] = 0;
                MsgStateSend->packetType[1] = 0;
                MsgStateSend->commState = REGISTRATION_COMPLETE;
                MsgStateSend->payloadSize = MsgStateSize;

                iSendResult = send(ClientSocket, (char *)MsgStateSend, MsgStateSize, 0);
                if (iSendResult == SOCKET_ERROR) {
                    printf_s("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
                printf_s("Bytes sent: %d\n", iSendResult);
                /* End Registration */
            }
            else if (MsgStateRecv->commState == SERVO_ON) {
                printf_s("Servo On\n");
                /* Servo On */
                MsgStateSend->packetType[0] = 64;	// 64
                MsgStateSend->packetType[1] = 0;
                MsgStateSend->commState = SERVO_ON_COMPLETE;
                MsgStateSend->payloadSize = MsgStateSize + ServerSystemDataSize;

				ServerSystemDataSet();
				sendBuff = (int8_t*)malloc(MsgStateSize + ServerSystemDataSize);
				DataGethering2((int8_t*)MsgStateSend, (int8_t*)ServerData, sendBuff);

                iSendResult = send(ClientSocket, (char *)sendBuff, MsgStateSize + ServerSystemDataSize, 0);
                if (iSendResult == SOCKET_ERROR) {
                    printf_s("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
                printf_s("Bytes sent: %d\n", iSendResult);
				free(sendBuff);
                /* End Servo On */
            }
            else if (MsgStateRecv->commState == TUNING_STATE) {
                printf_s("Tunning State\n");
                /* Tunning State */
                MsgStateSend->packetType[0] = 0;
                MsgStateSend->packetType[1] = 0;
                MsgStateSend->commState = TUNING_STATE_COMPLETE;
                MsgStateSend->payloadSize = MsgStateSize;

                iSendResult = send(ClientSocket, (char*)MsgStateSend, MsgStateSize, 0);
                if (iSendResult == SOCKET_ERROR) {
                    printf_s("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
                printf_s("Bytes sent: %d\n", iSendResult);
                /* End Tunning State */
            }
            else if (MsgStateRecv->commState == HOMING) {
                printf_s("Homing State\n");
                /* Homing */
                MsgStateSend->packetType[0] = 64;	// 64
                MsgStateSend->packetType[1] = 0;
                MsgStateSend->commState = HOMING_COMPLETE;
                MsgStateSend->payloadSize = MsgStateSize + ServerSystemDataSize;

                ServerSystemDataSet();
                sendBuff = (int8_t*)malloc(MsgStateSize + ServerSystemDataSize);
                DataGethering2((int8_t*)MsgStateSend, (int8_t*)ServerData, sendBuff);
				
                iSendResult = send(ClientSocket, (char*)sendBuff, MsgStateSize + ServerSystemDataSize, 0);
                if (iSendResult == SOCKET_ERROR) {
                    printf_s("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
                printf_s("Bytes sent: %d\n", iSendResult);
				free(sendBuff);
                /* End Homing */
            }
            else if (MsgStateRecv->commState == FREE_STATE) {
                /* Free State */
				MsgStateSend->packetType[0] = 79;	// 1, 2, 4, 8, 64
				MsgStateSend->packetType[1] = 0;
				MsgStateSend->commState = FREE_STATE;
				MsgStateSend->payloadSize = MsgStateSize +
					JointParamSetStructSize +
					JointTrajSetStructSize +
					CartesianParamSetStructSize +
					CartesianTrajSetStructSize +
					ServerSystemDataSize;

				JointParameterSet(METHOD_FIX);
				JointTrajectorySet(METHOD_FIX);
				CartesianParamSet(METHOD_FIX);
				CartesianTrajectorySet(METHOD_FIX);
				ServerSystemDataSet();

				sendBuff = (int8_t*)malloc(
					MsgStateSize + 
					JointParamSetStructSize +
					JointTrajSetStructSize +
					CartesianParamSetStructSize +
					CartesianTrajSetStructSize +
					ServerSystemDataSize);

				DataGethering6(
					(int8_t*)MsgStateSend,
					(int8_t*)jParamSet,
					(int8_t*)jTrajSet,
					(int8_t*)cParamSet,
					(int8_t*)cTrajSet,
					(int8_t*)ServerData, 
					sendBuff);

				iSendResult = send(ClientSocket, (char*)sendBuff, MsgStateSize +
					JointParamSetStructSize +
					JointTrajSetStructSize +
					CartesianParamSetStructSize +
					CartesianTrajSetStructSize +
					ServerSystemDataSize,
					0);
				if (iSendResult == SOCKET_ERROR) {
					printf_s("send failed with error: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					return 1;
				}
				printf_s("Bytes sent: %d\n", iSendResult);
				free(sendBuff);
                /* End Free State */
            }
			
        }
        else if (iResult == 0)
            printf_s("Connection closing...\n");
        else {
            printf_s("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
    } while (iResult > 0);

    /* shutdown the connection since we're done */
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf_s("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    /* cleanup */
    free(recvBuff);
    closesocket(ClientSocket);
	system("pause");
    WSACleanup();
    
    return 0;
}

