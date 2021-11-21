
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

/* ethernet communication header */
#include "ethernet_structure.h";
#include "ethernet_parser.h";
/* end ethernet communication header */

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
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

extern struct JointTargetStruct* jTarget;
extern struct JointTargetStruct* jTargetGet;

extern struct CartesianTargetStruct* cTarget;
extern struct CartesianTargetStruct* cTargetGet;
/* end extern */

void print_jointParam();
void printf_jointTraj();

int __cdecl main(void)
{
    /* Parser Init */
    EtherNetStructure_Init();
    /* End Parser Init */

    /* Buffer */
    int8_t* Buffer;
    /* End Buffer */

    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
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

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf_s("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf_s("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
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

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf_s("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {
        iResult = recv(ClientSocket, (char*)MsgStateRecv, MsgStateSize, 0);
        if (iResult > 0) {
            printf_s("Bytes received: %d\n", iResult);
          
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
                MsgStateSend->packetType[0] = 0;
                MsgStateSend->packetType[1] = 0;
                MsgStateSend->commState = SERVO_ON_COMPLETE;
                MsgStateSend->payloadSize = MsgStateSize;

                iSendResult = send(ClientSocket, (char *)MsgStateSend, MsgStateSize, 0);
                if (iSendResult == SOCKET_ERROR) {
                    printf_s("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
                printf_s("Bytes sent: %d\n", iSendResult);
                /* End Servo On */
            }
            else if (MsgStateRecv->commState == TUNING_STATE) {
                printf_s("Tunning State\n");
                /* Tunning State */
                int size = (int)MsgStateRecv->payloadSize - MsgStateSize;
                Buffer = (int8_t*)malloc(size);
                int iResult2 = recv(ClientSocket, (char*)Buffer, size, 0);
                if (iResult2 > 0) {
                    printf_s("Tunning State Recv Error !!!\n");
                }
                printf_s("Bytes received: %d\n", iResult2);

                DataDivideJointParamSettingStruct(Buffer, MsgStateRecv, jParamGet);
                print_jointParam();
                DataDivideJointTrajectorySetStruct(Buffer, MsgStateRecv, jTrajGet);
                printf_jointTraj();

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
                /* Homing */

                /* End Homing */
            }
            else if (MsgStateRecv->commState == FREE_STATE) {
                /* Free State */

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

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf_s("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();
    system("pause");
    return 0;
}

void print_jointParam()
{
    printf("\nJoint Parameters Get : \n");
    for (int i = 0; i < 4; i++)
    {
        printf_s("%f\n", jParamGet->jointTorquePgain[i]);
        printf_s("%f\n", jParamGet->jointTorqueIgain[i]);
        printf_s("%f\n", jParamGet->jointTorqueDgain[i]);
        printf_s("%f\n", jParamGet->jointPositionPgain[i]);
        printf_s("%f\n", jParamGet->jointPositionIgain[i]);
        printf_s("%f\n", jParamGet->jointPositionDgain[i]);
        printf_s("%f\n", jParamGet->jointGravityGain[i]);
        printf_s("%f\n", jParamGet->jointFrictionGain[i]);
        printf_s("%f\n", jParamGet->jointCurrentGain[i]);
        printf_s("%f\n", jParamGet->jointConstantTorque[i]);
        printf_s("%f\n", jParamGet->jointConstantSpring[i]);
        printf_s("%f\n", jParamGet->jointConstantEfficiency[i]);
    }
    printf("----------------------------------------------\n");
}

void printf_jointTraj()
{
    printf("\nJoint Trajectory Get : \n");
    for (int i = 0; i < 4; i++)
    {
        printf_s("%f\n", jTrajGet->JointTrajecotryTime[i]);
        printf_s("%f\n", jTrajGet->JointTrajectoryAcc[i]);
    }
    printf("----------------------------------------------\n");
}