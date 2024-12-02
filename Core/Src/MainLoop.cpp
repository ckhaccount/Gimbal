#include "can.h"
#include "Mainloop.h"
#include "General_Motor.h"
extern Motor yaw_motor;
extern Motor pitch_motor;
extern CAN_RxHeaderTypeDef Yaw_Motor_RxHeader;
extern CAN_TxHeaderTypeDef Yaw_Motor_TxHeader;
extern CAN_TxHeaderTypeDef Pitch_Motor_TxHeader;
extern CAN_TxHeaderTypeDef Pitch_Motor_RxHeader;
extern uint8_t Yaw_Motor_RxData[8];
extern uint8_t Yaw_Motor_TxData[8];
extern uint8_t Pitch_Motor_TxData[8];
extern uint32_t Motor_TxMailbox;
extern int mainloop_flag;
int flag=0;
void MainLoop(){
    mainloop_flag=0;
    yaw_motor.Motor_Speed_PID.Set_Fed_Speed(yaw_motor);
    pitch_motor.Motor_Speed_PID.Set_Fed_Speed(pitch_motor);
    yaw_motor.Motor_Speed_PID.Set_Ref_Speed(yaw_motor);
    pitch_motor.Motor_Speed_PID.Set_Ref_Speed(pitch_motor);
    yaw_motor.Motor_Speed_PID.Uint16_Current(yaw_motor,Yaw_Motor_TxData);
    pitch_motor.Motor_Speed_PID.Uint16_Current(pitch_motor,Pitch_Motor_TxData);
    if (HAL_CAN_AddTxMessage(&hcan1, &Yaw_Motor_TxHeader, Yaw_Motor_TxData, &Motor_TxMailbox)==HAL_OK)
    {
        flag=1;
    }
    HAL_CAN_AddTxMessage(&hcan1, &Pitch_Motor_TxHeader, Pitch_Motor_TxData, &Motor_TxMailbox);
    //     flag=1;

}
