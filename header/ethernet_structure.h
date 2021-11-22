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
	float actualMotorPosition[4];
	float actualMotorVelocity[4];
	float actualLinkPosition[4];
	float actualLinkVelocity[4];
	float actualCurrent[4];
	float targetPosition[4];
	float targetCurrent[4];
	int32_t modeOfOperation[4];
	int32_t statusword[4];
}Axis;

typedef struct ServerSystemData
{
	int32_t cnt;
	int32_t logCnt;
	int32_t gravityMode;
	int32_t targetReached;
	// Cartesian Position Info;
	float cartesianTargetPose[3];
	float cartesianCurrentPose[3];
	// Cartesian Trajectory Info
	float targetTrajectoryTime[3];
	float targetTrajectoryAcc[3];
	// Module Data (Motor Driver)
	Axis moduleData;
};

typedef struct JointParameterSettingStruct
{
	float jointPositionPgain[4];
	float jointPositionIgain[4];
	float jointPositionDgain[4];

	float jointTorquePgain[4];
	float jointTorqueIgain[4];
	float jointTorqueDgain[4];

	float jointConstantEfficiency[4];
	float jointConstantTorque[4];
	float jointConstantSpring[4];

	float jointGravityGain[4];
	float jointCurrentGain[4];
	float jointFrictionGain[4];
};

typedef struct JointTrajectorySetStruct
{
	float JointTrajecotryTime[4];
	float JointTrajectoryAcc[4];
};

typedef struct CartesianParameterSettingStruct
{
	float cartesianPositionPgain[3];
	float cartesianPositionIgain[3];
	float cartesianPositionDgain[3];
};

typedef struct CartesianTrajectorySetStruct
{
	float cartesianTrajectoryTime[3];
	float cartesianTrajectoryAcc[3];
};

typedef struct JointTargetStruct
{
	float jointTarget[4];
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
