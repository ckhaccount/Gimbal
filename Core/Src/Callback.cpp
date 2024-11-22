#include "main.h"
#include "DBUS_RC.h"
#include "usart.h"
#include "can.h"
#include "MotorType.h"
#include "General_Motor.h"
extern Motor yaw_motor;
extern Motor pitch_motor;
extern GM6020_Motor_Type yaw_motor_type;
extern GM6020_Motor_Type pitch_motor_type;
extern RC rc;
extern CAN_RxHeaderTypeDef Motor_RxHeader;
extern uint8_t Yaw_Motor_RxData[8];
extern uint8_t Pitch_Motor_RxData[8];
extern int mainloop_flag;
int flag2=0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    flag2=1;
    if(huart->Instance == USART3){
        //HAL_DMA_Abort(huart->hdmarx);
        HAL_UART_Receive_DMA(&huart3,rc.Get_buffer(), sizeof(rc.Get_buffer()));
        for(uint16_t i = 0; i < RC_RX_BUF_SIZE; i++){
            rc.Get_data()[i]=rc.Get_buffer()[i];
        }
        rc.Store_Data();
        pitch_motor.Motor_Angle_PID.Set_Ref(rc.pitch_max_angle_*rc.RCChannel_.l_col);// pitch_motor.Motor_Angle_PID.Set_Ref(30);
        yaw_motor.Motor_Angle_PID.Set_Ref(rc.yaw_max_angle_*rc.RCChannel_.l_row);//yaw_motor.Motor_Angle_PID.Set_Ref(30);
        //rc.Transmit_Data();

    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1){
        mainloop_flag = 1;
        pitch_motor.Motor_Angle_PID.Set_Ref(180);
        //rc.Transmit_Data();
    }
}
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if(hcan->Instance == CAN1){
        if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0,&Motor_RxHeader, Pitch_Motor_RxData)==HAL_OK){
            if(Motor_RxHeader.StdId==yaw_motor_type.Rece_Identifier_)
                yaw_motor.canRxMsgCallback(Yaw_Motor_RxData);
            else if(Motor_RxHeader.StdId==pitch_motor_type.Rece_Identifier_)
            {
                pitch_motor.canRxMsgCallback(Pitch_Motor_RxData);
            }
        }
    }
}
