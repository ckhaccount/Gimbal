#include "main.h"
#include "DBUS_RC.h"
#include "usart.h"
#include "init.h"
#include "can.h"
#include "tim.h"
#include "MotorType.h"
#include "General_Motor.h"
uint32_t M3508_ID_1=0x01;
uint32_t M3508_ID_2=0x02;
uint32_t M2006_ID_1=0x01;
uint32_t M2006_ID_2=0x02;
uint32_t GM6020_ID_1=0x01;
uint32_t GM6020_ID_2=0x02;
M2006_Motor_Type yaw_motor_type(M2006_ID_1);
GM6020_Motor_Type pitch_motor_type(GM6020_ID_1,0);
Motor yaw_motor(yaw_motor_type,46,1.6,400,100,100,30,0.04,0.001,0.000,2,1.5);
Motor pitch_motor(pitch_motor_type,40,0,0,100,100,30,0.06,0.001,0.000,1.5,1.5);
CAN_RxHeaderTypeDef Motor_RxHeader;
CAN_TxHeaderTypeDef Yaw_Motor_TxHeader={yaw_motor_type.Tran_Identifier_,yaw_motor_type.ID_,CAN_ID_STD,CAN_RTR_DATA, 8, DISABLE};
CAN_TxHeaderTypeDef Pitch_Motor_TxHeader={pitch_motor_type.Tran_Identifier_,0,CAN_ID_STD,CAN_RTR_DATA, 8, DISABLE};
uint8_t Yaw_Motor_RxData[8]={0x00};
uint8_t Yaw_Motor_TxData[8]={0x00};
uint8_t Pitch_Motor_RxData[8]={0x00};
uint8_t Pitch_Motor_TxData[8]={0x00};
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
extern int flag2;
int mainloop_flag=0;
extern RC rc;
void Init()
{
    HAL_UART_Receive_DMA(&huart3,rc.Get_buffer(),RC_RX_BUF_SIZE);
    HAL_CAN_ConfigFilter(&hcan1,&FilterConfig);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_TIM_Base_Start_IT(&htim1);
}
// void Output_All(control_data &data, float feed_back_, float target_, float feed_forward_, float output_){
//     data.feedback = feed_back_;
//     data.target = target_;
//     data.feedforward = feed_forward_;
//     data.output = output_;
// }
