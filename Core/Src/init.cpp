#include "main.h"
#include "DBUS_RC.h"
#include "usart.h"
#include "init.h"
#include "can.h"
#include "tim.h"
#include "MotorType.h"
#include "General_Motor.h"
#include <cmath>

#include "BMI088.h"
uint32_t M3508_ID_1=0x01;
uint32_t M3508_ID_2=0x02;
uint32_t M2006_ID_1=0x01;
uint32_t M2006_ID_2=0x02;
uint32_t GM6020_ID_1=0x01;
uint32_t GM6020_ID_2=0x02;
uint32_t GM6020_ID_3=0x03;
//M3508_Motor_Type motor_type(M3508_ID_1);
GM6020_Motor_Type yaw_motor_type(GM6020_ID_3,1);
GM6020_Motor_Type pitch_motor_type(GM6020_ID_1,1);
//Motor M3508_motor(motor_type,);
//Motor M2006_motor(motor_type,5,0.005,0,100,150,30,0.04,0.00008,0.01,1,60);
//Motor GM6020_motor_yaw_motor_based_on_IMU_feedback(70.89,0.00000,40,100,2500,60,0.0185,0,0.095,1,50,VirtualForward,VirtualForward);
//Motor GM6020_motor_pitch_motor_based_on_motor_feedback(100,1e-7,0,10,200,10,0.0127,0,2.4e-7,1,10,VirtualForward,RealForward);
//Motor GM6020_motor_pitch_motor_based_on_IMU_feedback(50,1e-7,0,10,200,10,0.017,0,0,1,10,VirtualForward,RealForward)
float VirtualForward(float angle) {return 0;}
float RealForward(float angle){return 0.4f*std::cos(angle);}
BMI088 bmi088(0.0005,0,0,0.001);
Motor yaw_motor(yaw_motor_type,70.89,0.00000,40,100,2500,60,0.0185,0,0.095,1,50,VirtualForward,VirtualForward);
Motor pitch_motor(pitch_motor_type,50,1e-7,0,10,200,10,0.017,0,0,1,10,VirtualForward,RealForward);
CAN_RxHeaderTypeDef Motor_RxHeader;
CAN_TxHeaderTypeDef Yaw_Motor_TxHeader={yaw_motor_type.Tran_Identifier_,0,CAN_ID_STD,CAN_RTR_DATA, 8, DISABLE};
CAN_TxHeaderTypeDef Pitch_Motor_TxHeader={pitch_motor_type.Tran_Identifier_,0,CAN_ID_STD,CAN_RTR_DATA, 8, DISABLE};
uint8_t Yaw_Motor_RxData[8]={0x00};
uint8_t Yaw_Motor_TxData[8];
uint8_t Pitch_Motor_RxData[8]={0x00};
uint8_t Pitch_Motor_TxData[8]={0x00};
uint8_t Motor_TxData[8]={0x00};
uint8_t Motor_RxData[8]={0x00};
uint32_t Motor_TxMailbox=CAN_TX_MAILBOX0;
CAN_FilterTypeDef FilterConfig =
          {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    CAN_FILTER_FIFO0,
    0,
  CAN_FILTERMODE_IDMASK,
   CAN_FILTERSCALE_32BIT,
    ENABLE
    };
uint8_t return_acc_data[7]={0x00};
uint8_t return_gyro_data[6]={0x00};
uint8_t range_acc_receive=0x00;
uint8_t range_gyro=0x00;
float acc_x=0,acc_y=0,acc_z=0;
float gyro_x=0,gyro_y=0,gyro_z=0;
extern int flag2;
int mainloop_flag=0;
RC rc(180,25);

void Init()
{
    HAL_UART_Receive_DMA(&huart3,rc.Get_buffer(),RC_RX_BUF_SIZE);
    HAL_CAN_ConfigFilter(&hcan1,&FilterConfig);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_TIM_Base_Start_IT(&htim1);
    bmi088.BMI088_Init();
    bmi088.Pitch_Init();
}

