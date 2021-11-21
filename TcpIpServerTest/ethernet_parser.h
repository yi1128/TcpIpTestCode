#pragma once
#include "ethernet_structure.h"

//#ifdef WIN32
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
//#endif

/* Variable Declaration */
int MsgStateSize = 0;
int AxisServerDataSize = 0;
int ServerSystemDataSize = 0;
int JointParamSetStructSize = 0;
int JointTrajSetStructSize = 0;
int CartesianParamSetStructSize = 0;
int CartesianTrajSetStructSize = 0;
int JointTargetStructSize = 0;
int CartesianTargetStructSize = 0;

MsgState* MsgStateSend;
MsgState* MsgStateRecv;

ServerSystemData* ServerData;

JointParameterSettingStruct* jParamSet;
JointParameterSettingStruct* jParamGet;

JointTrajectorySetStruct* jTrajSet;
JointTrajectorySetStruct* jTrajGet;

CartesianParameterSettingStruct* cParamSet;
CartesianParameterSettingStruct* cParamGet;

CartesianTrajectorySetStruct* cTrajSet;
CartesianTrajectorySetStruct* cTrajGet;

JointTargetStruct* jTargetSet;
JointTargetStruct* jTargetGet;

CartesianTargetStruct* cTargetSet;
CartesianTargetStruct* cTargetGet;
/* End Variable Declaration */

/* Bit Pattern */
unsigned char bitPattern[8] = {
	0x01, 0x02, 0x04, 0x08,			// 10000000, ........
	0x10, 0x20, 0x40, 0x80			// ........, 00000001
};
/* End Bit Pattern*/

/* Setting Value */
int ROBOT_AXIS = 4;
int CARTESIAN_AXIS = 6;
/* End Setting Value */

/* Buffer Declaration */
int8_t* msgRecvBuffer;
int8_t* sendDataBuffer;
int8_t* recvDataBuffer;
/* End Buffer Declaration */

/* Function Declaration */
void MsgStateInit(MsgState* _msgStatePtr);
void MsgStateRelease(MsgState* _msgStatePtr);
bool ServerSystemDataInit(ServerSystemData* _msgDataPtr);
bool SeverSystemDataRelease(ServerSystemData* _msgDataPtr);
bool JointParameterSettingStructInit(JointParameterSettingStruct* _msgDataPtr);
bool JointParameterSettingStructRelease(JointParameterSettingStruct* _msgDataPtr);
bool JointTrajectorySetStructInit(JointTrajectorySetStruct* _msgDataPtr);
bool JointTrajectorySetStructRelease(JointTrajectorySetStruct* _msgDataPtr);
bool CartesianParameterSettingStructInit(CartesianParameterSettingStruct* _msgDataPtr);
bool CartesianParameterSettingStructRelease(CartesianParameterSettingStruct* _msgDataPtr);
bool CartesianTrajectorySetStructInit(CartesianTrajectorySetStruct* _msgDataPtr);
bool CartesianTrajectorySetStructRelease(CartesianTrajectorySetStruct* _msgDataPtr);
bool JointTargetStructInit(JointTargetStruct* _msgDataPtr);
bool JointTargetStructRelease(JointTargetStruct* _msgDataPtr);
void CartesianTargetStructInit(CartesianTargetStruct* _msgDataPtr);
void CartesianTargetStructRelease(CartesianTargetStruct* _msgDataPtr);

bool EtherNetStructure_Init();
bool MsgStateToBuffer(MsgState* _msgStatePtr, int8_t* buff);
bool ServerSystemDataToBuffer(ServerSystemData* _msgDataPtr, int8_t* buff);
bool JointParameterSettingStructToBuffer(JointParameterSettingStruct* _msgDataPtr, int8_t* buff);
bool JointTrajectorySetStructToBuffer(JointTrajectorySetStruct* _msgDataPtr, int8_t* buff);
bool CartesianParameterSettingStructToBuffer(CartesianParameterSettingStruct* _msgDataPtr, int8_t* buff);
bool CartesianTrajectorySetStructToBuffer(CartesianTrajectorySetStruct* _msgDataPtr, int8_t* buff);
bool JointTargetStructToBuffer(JointTargetStruct* _msgDataPtr, int8_t* buff);
bool CartesianTargetStructToBuffer(CartesianTargetStruct* _msgDataPtr, int8_t* buff);
bool BufferInit();

bool DataGethering2
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buffOut
);
bool DataGethering3
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buffOut
);
bool DataGethering4
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buff4,
	int8_t* buffOut
);
bool DataGethering5
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buff4,
	int8_t* buff5,
	int8_t* buffOut
);
bool DataGethering6
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buff4,
	int8_t* buff5,
	int8_t* buff6,
	int8_t* buffOut
);
bool DataGethering7
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buff4,
	int8_t* buff5,
	int8_t* buff6,
	int8_t* buff7,
	int8_t* buffOut
);
bool DataGethering8
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buff4,
	int8_t* buff5,
	int8_t* buff6,
	int8_t* buff7,
	int8_t* buff8,
	int8_t* buffOut
);

bool DataDivideMsgState
(
	int8_t* inputBuff,
	MsgState* outputStruct
);
bool DataDivideJointParamSettingStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	JointParameterSettingStruct* outputStruct
);
bool DataDivideJointTrajectorySetStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	JointTrajectorySetStruct* outputStruct
);
bool DataDivideCartesianParameterSettingStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	CartesianParameterSettingStruct* outputStruct
);
bool DataDivideCartesianTrajectorySetStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	CartesianTrajectorySetStruct* outputStruct
);
bool DataDivideJointTaregetStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	JointTargetStruct* outputStruct
);
bool DataDivideJointCartesianTargetStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	CartesianTargetStruct* outputStruct
);
bool DataDivideJointServerSystemData
(
	int8_t* inputBuff,
	MsgState* msg,
	ServerSystemData* outputStruct
);

/* End Function Declaration */



/* Initialize & Release Structure  */
void MsgStateInit(MsgState* _msgStatePtr)
{
	_msgStatePtr->packetType[0] = 0;
	_msgStatePtr->packetType[1] = 0;
	_msgStatePtr->commState = REGISTRATION;
	_msgStatePtr->payloadSize = 0;
	_msgStatePtr->controlMode = NONE_MODE;
	MsgStateSize = _msize(_msgStatePtr);
}

void MsgStateRelease(MsgState* _msgStatePtr)
{
	free(_msgStatePtr);
}

bool ServerSystemDataInit(ServerSystemData* _msgDataPtr)
{
	ServerSystemDataSize = 0;
	_msgDataPtr->cnt = 0;
	ServerSystemDataSize += sizeof(_msgDataPtr->cnt);
	_msgDataPtr->logCnt = 0;
	ServerSystemDataSize += sizeof(_msgDataPtr->logCnt);
	_msgDataPtr->gravityMode = 0;
	ServerSystemDataSize += sizeof(_msgDataPtr->gravityMode);
	_msgDataPtr->targetReached = 0;
	ServerSystemDataSize += sizeof(_msgDataPtr->targetReached);
	_msgDataPtr->controlMode = NONE_MODE;
	ServerSystemDataSize += sizeof(_msgDataPtr->controlMode);

	// Cartesian Position Info;
	_msgDataPtr->cartesianTargetPose = (float*)calloc(CARTESIAN_AXIS, sizeof(float));
	if (_msgDataPtr->cartesianTargetPose == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->cartesianTargetPose);
	_msgDataPtr->cartesianCurrentPose = (float*)calloc(CARTESIAN_AXIS, sizeof(float));
	if (_msgDataPtr->cartesianCurrentPose == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->cartesianCurrentPose);

	// Cartesian Trajectory Info
	_msgDataPtr->targetTrajectoryTime = (float*)calloc(CARTESIAN_AXIS, sizeof(float));
	if (_msgDataPtr->targetTrajectoryTime == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->targetTrajectoryTime);
	_msgDataPtr->targetTrajectoryAcc = (float*)calloc(CARTESIAN_AXIS, sizeof(float));
	if (_msgDataPtr->targetTrajectoryAcc == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->targetTrajectoryAcc);

	// Module Data (Motor Driver)
	_msgDataPtr->moduleData = (Axis*)calloc(1, sizeof(Axis));
	if (_msgDataPtr->moduleData == NULL) {
		return false;
	}
	//ServerSystemDataSize += _msize(_msgDataPtr->moduleData);
	_msgDataPtr->moduleData->actualMotorPosition = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->moduleData->actualMotorPosition == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->moduleData->actualMotorPosition);
	_msgDataPtr->moduleData->actualLinkPosition = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->moduleData->actualLinkPosition == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->moduleData->actualLinkPosition);
	_msgDataPtr->moduleData->actualMotorVelocity = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->moduleData->actualMotorVelocity == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->moduleData->actualMotorVelocity);
	_msgDataPtr->moduleData->actualLinkVelocity = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->moduleData->actualLinkVelocity == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->moduleData->actualLinkVelocity);
	_msgDataPtr->moduleData->actualCurrent = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->moduleData->actualCurrent == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->moduleData->actualCurrent);
	_msgDataPtr->moduleData->targetPosition = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->moduleData->targetPosition == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->moduleData->targetPosition);
	_msgDataPtr->moduleData->targetCurrent = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->moduleData->targetCurrent == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->moduleData->targetCurrent);
	_msgDataPtr->moduleData->modeOfOperation = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->moduleData->modeOfOperation == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->moduleData->modeOfOperation);
	_msgDataPtr->moduleData->statusword = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->moduleData->statusword == NULL) {
		return false;
	}
	ServerSystemDataSize += _msize(_msgDataPtr->moduleData->statusword);

	return true;
}

bool SeverSystemDataRelease(ServerSystemData* _msgDataPtr)
{
	free(_msgDataPtr);
	return true;
}

bool JointParameterSettingStructInit(JointParameterSettingStruct* _msgDataPtr)
{
	JointParamSetStructSize = 0;
	_msgDataPtr->jointPositionPgain = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointPositionPgain == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointPositionPgain);
	_msgDataPtr->jointPositionIgain = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointPositionIgain == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointPositionIgain);
	_msgDataPtr->jointPositionDgain = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointPositionDgain == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointPositionDgain);

	_msgDataPtr->jointTorquePgain = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointTorquePgain == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointTorquePgain);
	_msgDataPtr->jointTorqueIgain = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointTorqueIgain == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointTorqueIgain);
	_msgDataPtr->jointTorqueDgain = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointTorqueDgain == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointTorqueDgain);

	_msgDataPtr->jointConstantEfficiency = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointConstantEfficiency == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointConstantEfficiency);
	_msgDataPtr->jointConstantTorque = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointConstantTorque == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointConstantTorque);
	_msgDataPtr->jointConstantSpring = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointConstantSpring == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointConstantSpring);

	_msgDataPtr->jointGravityGain = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointGravityGain == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointGravityGain);
	_msgDataPtr->jointCurrentGain = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointCurrentGain == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointCurrentGain);
	_msgDataPtr->jointFrictionGain = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointFrictionGain == NULL) {
		return false;
	}
	JointParamSetStructSize += _msize(_msgDataPtr->jointFrictionGain);

	return true;
}

bool JointParameterSettingStructRelease(JointParameterSettingStruct* _msgDataPtr)
{
	free(_msgDataPtr);
	return true;
}


bool JointTrajectorySetStructInit(JointTrajectorySetStruct* _msgDataPtr)
{
	JointTrajSetStructSize = 0;
	_msgDataPtr->JointTrajecotryTime = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->JointTrajecotryTime == NULL) {
		return false;
	}
	JointTrajSetStructSize += _msize(_msgDataPtr->JointTrajecotryTime);
	_msgDataPtr->JointTrajectoryAcc = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->JointTrajectoryAcc == NULL) {
		return false;
	}
	JointTrajSetStructSize += _msize(_msgDataPtr->JointTrajectoryAcc);

	return true;
}

bool JointTrajectorySetStructRelease(JointTrajectorySetStruct* _msgDataPtr)
{
	free(_msgDataPtr);
	return true;
}

bool CartesianParameterSettingStructInit(CartesianParameterSettingStruct* _msgDataPtr)
{
	CartesianParamSetStructSize = 0;
	_msgDataPtr->cartesianPositionPgain = (float*)calloc(CARTESIAN_AXIS, sizeof(float));
	if (_msgDataPtr->cartesianPositionPgain == NULL) {
		return false;
	}
	CartesianParamSetStructSize += _msize(_msgDataPtr->cartesianPositionPgain);
	_msgDataPtr->cartesianPositionIgain = (float*)calloc(CARTESIAN_AXIS, sizeof(float));
	if (_msgDataPtr->cartesianPositionIgain == NULL) {
		return false;
	}
	CartesianParamSetStructSize += _msize(_msgDataPtr->cartesianPositionIgain);
	_msgDataPtr->cartesianPositionDgain = (float*)calloc(CARTESIAN_AXIS, sizeof(float));
	if (_msgDataPtr->cartesianPositionDgain == NULL) {
		return false;
	}
	CartesianParamSetStructSize += _msize(_msgDataPtr->cartesianPositionDgain);
	return true;
}

bool CartesianParameterSettingStructRelease(CartesianParameterSettingStruct* _msgDataPtr)
{
	free(_msgDataPtr);
	return true;
}

bool CartesianTrajectorySetStructInit(CartesianTrajectorySetStruct* _msgDataPtr)
{
	CartesianTrajSetStructSize = 0;
	_msgDataPtr->cartesianTrajectoryTime = (float*)calloc(CARTESIAN_AXIS, sizeof(float));
	if (_msgDataPtr->cartesianTrajectoryTime == NULL) {
		return false;
	}
	CartesianTrajSetStructSize += _msize(_msgDataPtr->cartesianTrajectoryTime);
	_msgDataPtr->cartesianTrajectoryAcc = (float*)calloc(CARTESIAN_AXIS, sizeof(float));
	if (_msgDataPtr->cartesianTrajectoryAcc == NULL) {
		return false;
	}
	CartesianTrajSetStructSize += _msize(_msgDataPtr->cartesianTrajectoryAcc);

	return true;
}

bool CartesianTrajectorySetStructRelease(CartesianTrajectorySetStruct* _msgDataPtr)
{
	free(_msgDataPtr);
	return true;
}

bool JointTargetStructInit(JointTargetStruct* _msgDataPtr)
{
	JointTargetStructSize = 0;
	_msgDataPtr->jointTarget = (float*)calloc(ROBOT_AXIS, sizeof(float));
	if (_msgDataPtr->jointTarget == NULL) {
		return false;
	}
	JointTargetStructSize += _msize(_msgDataPtr->jointTarget);
}

bool JointTargetStructRelease(JointTargetStruct* _msgDataPtr)
{
	free(_msgDataPtr);
	return true;
}

void CartesianTargetStructInit(CartesianTargetStruct* _msgDataPtr)
{
	_msgDataPtr->pX = 0.0f;
	_msgDataPtr->pY = 0.0f;
	_msgDataPtr->pZ = 0.0f;
	_msgDataPtr->rX = 0.0f;
	_msgDataPtr->rY = 0.0f;
	_msgDataPtr->rZ = 0.0f;
	CartesianTargetStructSize = sizeof(CartesianTargetStruct);
}

void CartesianTargetStructRelease(CartesianTargetStruct* _msgDataPtr)
{
	free(_msgDataPtr);
}
/* Initialize & Release Structure End */

/* All Variable Initialize */
bool EtherNetStructure_Init()
{
	/* Send EtherNetStructure Init */
	MsgStateSend = (MsgState*)malloc(sizeof(MsgState));
	jParamSet = (JointParameterSettingStruct*)malloc(sizeof(JointParameterSettingStruct));
	jTrajSet = (JointTrajectorySetStruct*)malloc(sizeof(JointTrajectorySetStruct));
	cParamSet = (CartesianParameterSettingStruct*)malloc(sizeof(CartesianParameterSettingStruct));
	cTrajSet = (CartesianTrajectorySetStruct*)malloc(sizeof(CartesianTrajectorySetStruct));
	jTargetSet = (JointTargetStruct*)malloc(sizeof(JointTargetStruct));
	cTargetSet = (CartesianTargetStruct*)malloc(sizeof(CartesianTargetStruct));

	MsgStateInit(MsgStateSend);
	if (!JointParameterSettingStructInit(jParamSet)) return false;
	if (!JointTrajectorySetStructInit(jTrajSet)) return false;
	if (!CartesianParameterSettingStructInit(cParamSet)) return false;
	if (!CartesianTrajectorySetStructInit(cTrajSet)) return false;
	if (!JointTargetStructInit(jTargetSet)) return false;
	CartesianTargetStructInit(cTargetSet);
	/* End Send EtherNetStructure Init */

	/* Recv EtherNetStructure Init */
	MsgStateRecv = (MsgState*)malloc(sizeof(MsgState));
	ServerData = (ServerSystemData*)malloc(sizeof(ServerSystemData));
	jParamGet = (JointParameterSettingStruct*)malloc(sizeof(JointParameterSettingStruct));
	jTrajGet = (JointTrajectorySetStruct*)malloc(sizeof(JointTrajectorySetStruct));
	cParamGet = (CartesianParameterSettingStruct*)malloc(sizeof(CartesianParameterSettingStruct));
	cTrajGet = (CartesianTrajectorySetStruct*)malloc(sizeof(CartesianTrajectorySetStruct));
	jTargetGet = (JointTargetStruct*)malloc(sizeof(JointTargetStruct));
	cTargetGet = (CartesianTargetStruct*)malloc(sizeof(CartesianTargetStruct));

	MsgStateInit(MsgStateRecv);
	if (!ServerSystemDataInit(ServerData)) return false;
	if (!JointParameterSettingStructInit(jParamGet)) return false;
	if (!JointTrajectorySetStructInit(jTrajGet)) return false;
	if (!CartesianParameterSettingStructInit(cParamGet)) return false;
	if (!CartesianTrajectorySetStructInit(cTrajGet)) return false;
	if (!JointTargetStructInit(jTargetGet)) return false;
	CartesianTargetStructInit(cTargetGet);
	/* End Recv EtherNetStructure Init */
	return true;
}
/* End All Variable Initialize */

/* Convert to Buffer */
bool MsgStateToBuffer(MsgState* _msgStatePtr, int8_t* buff)
{
	if (buff == NULL)
	{
		buff = (int8_t*)calloc(MsgStateSize, sizeof(int8_t));
		if (buff == NULL) {
			return false;
		}
	}
	else {
		buff = (int8_t*)realloc(buff, MsgStateSize);
		if (buff == NULL) {
			return false;
		}
	}
	memcpy(buff, _msgStatePtr, MsgStateSize);
	return true;
}

bool ServerSystemDataToBuffer(ServerSystemData* _msgDataPtr, int8_t* buff)
{
	if (buff == NULL)
	{
		buff = (int8_t*)calloc(ServerSystemDataSize, sizeof(int8_t));
		if (buff == NULL) {
			return false;
		}
	}
	else {
		buff = (int8_t*)realloc(buff, ServerSystemDataSize);
		if (buff == NULL) {
			return false;
		}
	}
	memcpy(buff, _msgDataPtr, ServerSystemDataSize);
	return true;
}

bool JointParameterSettingStructToBuffer(JointParameterSettingStruct* _msgDataPtr, int8_t* buff)
{
	if (buff == NULL)
	{
		buff = (int8_t*)calloc(JointParamSetStructSize, sizeof(int8_t));
		if (buff == NULL) {
			return false;
		}
	}
	else {
		buff = (int8_t*)realloc(buff, JointParamSetStructSize);
		if (buff == NULL) {
			return false;
		}
	}
	memcpy(buff, _msgDataPtr, JointParamSetStructSize);
	return true;
}

bool JointTrajectorySetStructToBuffer(JointTrajectorySetStruct* _msgDataPtr, int8_t* buff)
{
	if (buff == NULL)
	{
		buff = (int8_t*)calloc(JointTrajSetStructSize, sizeof(int8_t));
		if (buff == NULL) {
			return false;
		}
	}
	else {
		buff = (int8_t*)realloc(buff, JointTrajSetStructSize);
		if (buff == NULL) {
			return false;
		}
	}
	memcpy(buff, _msgDataPtr, JointTrajSetStructSize);
	return true;
}

bool CartesianParameterSettingStructToBuffer(CartesianParameterSettingStruct* _msgDataPtr, int8_t* buff)
{
	if (buff == NULL)
	{
		buff = (int8_t*)calloc(CartesianParamSetStructSize, sizeof(int8_t));
		if (buff == NULL) {
			return false;
		}
	}
	else {
		buff = (int8_t*)realloc(buff, CartesianParamSetStructSize);
		if (buff == NULL) {
			return false;
		}
	}
	memcpy(buff, _msgDataPtr, CartesianParamSetStructSize);
	return true;
}

bool CartesianTrajectorySetStructToBuffer(CartesianTrajectorySetStruct* _msgDataPtr, int8_t* buff)
{
	if (buff == NULL)
	{
		buff = (int8_t*)calloc(CartesianTrajSetStructSize, sizeof(int8_t));
		if (buff == NULL) {
			return false;
		}
	}
	else {
		buff = (int8_t*)realloc(buff, CartesianTrajSetStructSize);
		if (buff == NULL) {
			return false;
		}
	}
	memcpy(buff, _msgDataPtr, CartesianTrajSetStructSize);
	return true;
}

bool JointTargetStructToBuffer(JointTargetStruct* _msgDataPtr, int8_t* buff)
{
	if (buff == NULL)
	{
		buff = (int8_t*)calloc(JointTargetStructSize, sizeof(int8_t));
		if (buff == NULL) {
			return false;
		}
	}
	else {
		buff = (int8_t*)realloc(buff, JointTargetStructSize);
		if (buff == NULL) {
			return false;
		}
	}
	memcpy(buff, _msgDataPtr, JointTargetStructSize);
	return true;
}

bool CartesianTargetStructToBuffer(CartesianTargetStruct* _msgDataPtr, int8_t* buff)
{
	if (buff == NULL)
	{
		buff = (int8_t*)calloc(CartesianTargetStructSize, sizeof(int8_t));
		if (buff == NULL) {
			return false;
		}
	}
	else {
		buff = (int8_t*)realloc(buff, CartesianTargetStructSize);
		if (buff == NULL) {
			return false;
		}
	}
	memcpy(buff, _msgDataPtr, CartesianTargetStructSize);
	return true;
}
/* End Convert To Buffer*/

/* Buffer Initialize */
bool BufferInit()
{
	if (msgRecvBuffer == NULL) {
		msgRecvBuffer = (int8_t*)calloc(MsgStateSize, sizeof(int8_t));
		if (msgRecvBuffer == NULL) {
			return false;
		}
	}
	else {
		msgRecvBuffer = (int8_t*)realloc(msgRecvBuffer, MsgStateSize);
		if (msgRecvBuffer == NULL) {
			return false;
		}
	}

	if (sendDataBuffer == NULL) {
		sendDataBuffer = (int8_t*)calloc(1, sizeof(int8_t));
		if (sendDataBuffer == NULL) {
			return false;
		}
	}
	else {
		sendDataBuffer = (int8_t*)realloc(sendDataBuffer, sizeof(int8_t));
		if (sendDataBuffer == NULL) {
			return false;
		}
	}

	if (recvDataBuffer == NULL) {
		recvDataBuffer = (int8_t*)calloc(MsgStateSize, sizeof(int8_t));
		if (recvDataBuffer == NULL) {
			return false;
		}
	}
	else {
		recvDataBuffer = (int8_t*)realloc(recvDataBuffer, MsgStateSize);
		if (recvDataBuffer == NULL) {
			return false;
		}
	}

	return true;
}
/* End Buffer Initialize */

/* Function for Data Gethering */
bool DataGethering2
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buffOut
)
{
	if (buffOut == NULL) {
		int size = _msize(buff1) + _msize(buff2);
		buffOut = (int8_t*)calloc(size, sizeof(int8_t));
		if (buffOut == NULL) {
			return false;
		}
	}
	else {
		int size = _msize(buff1) + _msize(buff2);
		buffOut = (int8_t*)realloc(buffOut, size);
		if (buffOut == NULL) {
			return false;
		}
	}

	memcpy(buffOut, buff1, _msize(buff1));
	memcpy(buffOut + _msize(buff1), buff2, _msize(buff2));
	return true;
}

bool DataGethering3
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buffOut
)
{
	if (buffOut == NULL) {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3);
		buffOut = (int8_t*)calloc(size, sizeof(int8_t));
		if (buffOut == NULL) {
			return false;
		}
	}
	else {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3);
		buffOut = (int8_t*)realloc(buffOut, size);
		if (buffOut == NULL) {
			return false;
		}
	}

	memcpy(buffOut, buff1, _msize(buff1));
	memcpy(buffOut + _msize(buff1), buff2, _msize(buff2));
	memcpy(buffOut + _msize(buff1) + _msize(buff2), buff3, _msize(buff3));

	return true;
}

bool DataGethering4
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buff4,
	int8_t* buffOut
)
{
	if (buffOut == NULL) {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4);
		buffOut = (int8_t*)calloc(size, sizeof(int8_t));
		if (buffOut == NULL) {
			return false;
		}
	}
	else {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4);
		buffOut = (int8_t*)realloc(buffOut, size);
		if (buffOut == NULL) {
			return false;
		}
	}

	memcpy(buffOut, buff1, _msize(buff1));
	memcpy(buffOut + _msize(buff1), buff2, _msize(buff2));
	memcpy(buffOut + _msize(buff1) + _msize(buff2), buff3, _msize(buff3));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3), buff4, _msize(buff4));
	return true;
}

bool DataGethering5
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buff4,
	int8_t* buff5,
	int8_t* buffOut
)
{
	if (buffOut == NULL) {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5);
		buffOut = (int8_t*)calloc(size, sizeof(int8_t));
		if (buffOut == NULL) {
			return false;
		}
	}
	else {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5);
		buffOut = (int8_t*)realloc(buffOut, size);
		if (buffOut == NULL) {
			return false;
		}
	}

	memcpy(buffOut, buff1, _msize(buff1));
	memcpy(buffOut + _msize(buff1), buff2, _msize(buff2));
	memcpy(buffOut + _msize(buff1) + _msize(buff2), buff3, _msize(buff3));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3), buff4, _msize(buff4));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4), buff5, _msize(buff5));
	return true;
}

bool DataGethering6
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buff4,
	int8_t* buff5,
	int8_t* buff6,
	int8_t* buffOut
)
{
	if (buffOut == NULL) {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5) + _msize(buff6);
		buffOut = (int8_t*)calloc(size, sizeof(int8_t));
		if (buffOut == NULL) {
			return false;
		}
	}
	else {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5) + _msize(buff6);
		buffOut = (int8_t*)realloc(buffOut, size);
		if (buffOut == NULL) {
			return false;
		}
	}

	memcpy(buffOut, buff1, _msize(buff1));
	memcpy(buffOut + _msize(buff1), buff2, _msize(buff2));
	memcpy(buffOut + _msize(buff1) + _msize(buff2), buff3, _msize(buff3));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3), buff4, _msize(buff4));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4), buff5, _msize(buff5));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5), buff6, _msize(buff6));
	return true;
}

bool DataGethering7
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buff4,
	int8_t* buff5,
	int8_t* buff6,
	int8_t* buff7,
	int8_t* buffOut
)
{
	if (buffOut == NULL) {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5) + _msize(buff6) + _msize(buff7);
		buffOut = (int8_t*)calloc(size, sizeof(int8_t));
		if (buffOut == NULL) {
			return false;
		}
	}
	else {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5) + _msize(buff6) + _msize(buff7);
		buffOut = (int8_t*)realloc(buffOut, size);
		if (buffOut == NULL) {
			return false;
		}
	}

	memcpy(buffOut, buff1, _msize(buff1));
	memcpy(buffOut + _msize(buff1), buff2, _msize(buff2));
	memcpy(buffOut + _msize(buff1) + _msize(buff2), buff3, _msize(buff3));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3), buff4, _msize(buff4));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4), buff5, _msize(buff5));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5), buff6, _msize(buff6));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5) + _msize(buff6), buff7, _msize(buff7));
	return true;
}

bool DataGethering8
(
	int8_t* buff1,
	int8_t* buff2,
	int8_t* buff3,
	int8_t* buff4,
	int8_t* buff5,
	int8_t* buff6,
	int8_t* buff7,
	int8_t* buff8,
	int8_t* buffOut
)
{
	if (buffOut == NULL) {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5) + _msize(buff6) + _msize(buff7) + _msize(buff8);
		buffOut = (int8_t*)calloc(size, sizeof(int8_t));
		if (buffOut == NULL) {
			return false;
		}
	}
	else {
		int size = _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5) + _msize(buff6) + _msize(buff7) + _msize(buff8);
		buffOut = (int8_t*)realloc(buffOut, size);
		if (buffOut == NULL) {
			return false;
		}
	}

	memcpy(buffOut, buff1, _msize(buff1));
	memcpy(buffOut + _msize(buff1), buff2, _msize(buff2));
	memcpy(buffOut + _msize(buff1) + _msize(buff2), buff3, _msize(buff3));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3), buff4, _msize(buff4));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4), buff5, _msize(buff5));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5), buff6, _msize(buff6));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5) + _msize(buff6), buff7, _msize(buff7));
	memcpy(buffOut + _msize(buff1) + _msize(buff2) + _msize(buff3) + _msize(buff4) + _msize(buff5) + _msize(buff6) + _msize(buff7), buff8, _msize(buff8));
	return true;
}
/* End Function for Data Gethering */

/* Function for Data Divide */
bool DataDivideMsgState
(
	int8_t* inputBuff,
	MsgState* outputStruct
)
{
	if (inputBuff == NULL) {
		return false;
	}
	memcpy(outputStruct, inputBuff, MsgStateSize);
	return true;
}

bool DataDivideJointParamSettingStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	JointParameterSettingStruct* outputStruct
)
{
	if (inputBuff == NULL) {
		return false;
	}

	if (msg->packetType[0] & bitPattern[0]) {
		memcpy(outputStruct, inputBuff + MsgStateSize, JointParamSetStructSize);
	}

	return true;
}

bool DataDivideJointTrajectorySetStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	JointTrajectorySetStruct* outputStruct
)
{
	if (inputBuff == NULL) {
		return false;
	}
	int pointer = 0;

	if (msg->packetType[0] & bitPattern[0]) {
		pointer += JointParamSetStructSize;
	}

	if (pointer > 0) {
		memcpy(outputStruct, inputBuff + MsgStateSize + pointer, JointTrajSetStructSize);
	}
	return true;
}

bool DataDivideCartesianParameterSettingStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	CartesianParameterSettingStruct* outputStruct
)
{
	if (inputBuff == NULL) {
		return false;
	}

	int pointer = 0;
	for (int i = 0; i < 2; i++) {
		if (msg->packetType[0] & bitPattern[0]) {
			pointer += JointParamSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[1]) {
			pointer += JointTrajSetStructSize;
		}
	}

	memcpy(outputStruct, inputBuff + MsgStateSize + pointer, CartesianParamSetStructSize);
	return true;
}

bool DataDivideCartesianTrajectorySetStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	CartesianTrajectorySetStruct* outputStruct
)
{
	if (inputBuff == NULL) {
		return false;
	}

	int pointer = 0;
	for (int i = 0; i < 2; i++) {
		if (msg->packetType[0] & bitPattern[0]) {
			pointer += JointParamSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[1]) {
			pointer += JointTrajSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[2]) {
			pointer += CartesianParamSetStructSize;
		}
	}

	memcpy(outputStruct, inputBuff + MsgStateSize + pointer, CartesianTrajSetStructSize);
	return true;
}

bool DataDivideJointTaregetStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	JointTargetStruct* outputStruct
)
{
	if (inputBuff == NULL) {
		return false;
	}

	int pointer = 0;
	for (int i = 0; i < 2; i++) {
		if (msg->packetType[0] & bitPattern[0]) {
			pointer += JointParamSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[1]) {
			pointer += JointTrajSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[2]) {
			pointer += CartesianParamSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[3]) {
			pointer += CartesianTrajSetStructSize;
		}
	}

	memcpy(outputStruct, inputBuff + MsgStateSize + pointer, JointTargetStructSize);

	return true;
}

bool DataDivideJointCartesianTargetStruct
(
	int8_t* inputBuff,
	MsgState* msg,
	CartesianTargetStruct* outputStruct
)
{
	if (inputBuff == NULL) {
		return false;
	}

	int pointer = 0;
	for (int i = 0; i < 2; i++) {
		if (msg->packetType[0] & bitPattern[0]) {
			pointer += JointParamSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[1]) {
			pointer += JointTrajSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[2]) {
			pointer += CartesianParamSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[3]) {
			pointer += CartesianTrajSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[4]) {
			pointer += JointTargetStructSize;
		}
	}

	memcpy(outputStruct, inputBuff + MsgStateSize + pointer, CartesianTargetStructSize);

	return true;
}

bool DataDivideJointServerSystemData
(
	int8_t* inputBuff,
	MsgState* msg,
	ServerSystemData* outputStruct
)
{
	if (inputBuff == NULL) {
		return false;
	}

	int pointer = 0;
	for (int i = 0; i < 2; i++) {
		if (msg->packetType[0] & bitPattern[0]) {
			pointer += JointParamSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[1]) {
			pointer += JointTrajSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[2]) {
			pointer += CartesianParamSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[3]) {
			pointer += CartesianTrajSetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[4]) {
			pointer += JointTargetStructSize;
		}
		else if (msg->packetType[0] & bitPattern[5]) {
			pointer += CartesianTargetStructSize;
		}
	}

	memcpy(outputStruct, inputBuff + MsgStateSize + pointer, ServerSystemDataSize);

	return true;
}
/* End Function for Data Divide */