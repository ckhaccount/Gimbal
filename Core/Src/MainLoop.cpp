#include "can.h"
#include "Mainloop.h"
#include "General_Motor.h"
#include "BMI088.h"
extern Motor yaw_motor;
extern Motor pitch_motor;
extern BMI088 bmi088;
extern CAN_RxHeaderTypeDef Yaw_Motor_RxHeader;
extern CAN_TxHeaderTypeDef Yaw_Motor_TxHeader;
extern CAN_TxHeaderTypeDef Pitch_Motor_TxHeader;
extern CAN_TxHeaderTypeDef Pitch_Motor_RxHeader;
extern CAN_TxHeaderTypeDef Motor_RxHeader;
extern uint8_t Yaw_Motor_RxData[8];
extern uint8_t Pitch_Motor_TxData[8];
extern uint8_t Motor_TxData[8];
extern uint32_t Motor_TxMailbox;
extern uint8_t return_acc_data[7];
extern uint8_t return_gyro_data[6];
extern uint8_t range_acc_receive;
extern uint8_t range_gyro;
extern float acc_x, acc_y, acc_z;
extern float gyro_x, gyro_y, gyro_z;
extern int mainloop_flag;
int flag=0;
void MainLoop(){
    mainloop_flag=0;
    bmi088.Set_All_Angle();
    yaw_motor.Motor_Speed_PID.Set_Fed_Speed(yaw_motor);
    pitch_motor.Motor_Speed_PID.Set_Fed_Speed(pitch_motor);
    yaw_motor.Motor_Speed_PID.Set_Ref_Speed(yaw_motor,bmi088.Get_All_Angle()[2]);
    pitch_motor.Motor_Speed_PID.Set_Ref_Speed(pitch_motor,bmi088.Get_All_Angle()[0]);
    yaw_motor.Motor_Speed_PID.Uint16_Current(yaw_motor,Motor_TxData);
    pitch_motor.Motor_Speed_PID.Uint16_Current(pitch_motor,Motor_TxData);
    HAL_CAN_AddTxMessage(&hcan1,&Pitch_Motor_TxHeader, Motor_TxData, &Motor_TxMailbox);
    //HAL_CAN_AddTxMessage(&hcan1, &Yaw_Motor_TxHeader, Motor_TxData, &Motor_TxMailbox);
}
