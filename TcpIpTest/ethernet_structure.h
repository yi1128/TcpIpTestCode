#include <stdint.h>

#pragma once
/* Define */
/* ROBOT SETTING STATUS */
#define JOINT_PARAMETER_SET 		0
#define JOINT_TRAJECTORY_SET 		1
#define CARTESIAN_PARAMETER_SET 	2
#define CARTESIAN_TRAJECTORY_SET 	3
#define JOINT_TARGET_SET 			4
#define CARTESIAN_TARGET_SET 		5
#define SERVER_SYSTEM_DAYA 			6
#define NONE 						7

/* COMMUNICATION STATUS */
#define REGISTRATION 				0
#define REGISTRATION_COMPLETE		1
#define SERVO_ON					2
#define SERVO_ON_COMPLETE			3
#define TUNING_STATE 				4
#define TUNING_STATE_COMPLETE		5
#define HOMING 						6
#define HOMING_COMPLETE 			7
#define FREE_STATE					8

/* CONTROL MODE */
#define NONE_MODE					0
#define GRAVITY_MODE 				1
#define JOINT_MODE 					2
#define CARTESIAN_MODE 				3
#define GRAVITY_WITH_JOINT_MODE		4
#define GRAVITY_WITH_CARTESIAN_MODE 5
/* End Define */

/* Structure */
/* COMMUNICATION STRUCTURE */
#pragma pack(push,1)
typedef struct MsgState
{
	uint8_t packetType[2];
	uint16_t commState;
	uint16_t payloadSize;
	uint8_t controlMode;
};

typedef struct AxisServerData
{
	float* actualMotorPosition;
	float* actualLinkPosition;
	float* actualMotorVelocity;
	float* actualLinkVelocity;
	float* actualCurrent;
	float* targetPosition;
	float* targetCurrent;
	float* modeOfOperation;
	float* statusword;
}Axis;

typedef struct ServerSystemData
{
	int32_t cnt;
	int32_t logCnt;
	int32_t gravityMode;
	int32_t targetReached;
	int32_t controlMode;
	// Cartesian Position Info;
	float* cartesianTargetPose;
	float* cartesianCurrentPose;
	// Cartesian Trajectory Info
	float* targetTrajectoryTime;
	float* targetTrajectoryAcc;
	// Module Data (Motor Driver)
	Axis* moduleData;
};

typedef struct JointParameterSettingStruct
{
	float* jointPositionPgain;
	float* jointPositionIgain;
	float* jointPositionDgain;

	float* jointTorquePgain;
	float* jointTorqueIgain;
	float* jointTorqueDgain;

	float* jointConstantEfficiency;
	float* jointConstantTorque;
	float* jointConstantSpring;

	float* jointGravityGain;
	float* jointCurrentGain;
	float* jointFrictionGain;
};

typedef struct JointTrajectorySetStruct
{
	float* JointTrajecotryTime;
	float* JointTrajectoryAcc;
};

typedef struct CartesianParameterSettingStruct
{
	float* cartesianPositionPgain;
	float* cartesianPositionIgain;
	float* cartesianPositionDgain;
};

typedef struct CartesianTrajectorySetStruct
{
	float* cartesianTrajectoryTime;
	float* cartesianTrajectoryAcc;
};

typedef struct JointTargetStruct
{
	float* jointTarget;
};

typedef struct CartesianTargetStruct
{
	float pX;
	float pY;
	float pZ;
	float rX;
	float rY;
	float rZ;
};
#pragma pack(pop)
/* End Structure */




