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
    yaw_motor.Motor_Speed_PID.Set_Fed(yaw_motor.Get_motor_message()[3]);
    pitch_motor.Motor_Speed_PID.Set_Fed(pitch_motor.Get_motor_message()[3]);
    yaw_motor.Motor_Speed_PID.Set_Ref(yaw_motor.Motor_Angle_PID.Expect_Speed(yaw_motor.Get_motor_message()[6]));
    pitch_motor.Motor_Speed_PID.Set_Ref(pitch_motor.Motor_Angle_PID.Expect_Speed(pitch_motor.Get_motor_message()[6]));
    yaw_motor.Motor_Speed_PID.Uint16_Current(yaw_motor.Get_motor_message()[3],yaw_motor.motortype_, Yaw_Motor_TxData);
    pitch_motor.Motor_Speed_PID.Uint16_Current(pitch_motor.Get_motor_message()[3],pitch_motor.motortype_, Pitch_Motor_TxData);
    HAL_CAN_AddTxMessage(&hcan1, &Yaw_Motor_TxHeader, Yaw_Motor_TxData, &Motor_TxMailbox);
    HAL_CAN_AddTxMessage(&hcan1, &Pitch_Motor_TxHeader, Pitch_Motor_TxData, &Motor_TxMailbox);
    //     flag=1;

}
