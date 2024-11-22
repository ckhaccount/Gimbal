#include "Motor.h"
#include "Basic_Func.h"
M3508_Motor motor;
#include <array>
M3508_Motor::M3508_Motor()
{
    ratio_=3591.0/187;
    angle_=0;
    delta_angle_=0;
    ecd_angle_=0;
    last_ecd_angle_=0;
    delta_ecd_angle_=0;
    rotate_speed_=0;
    current_=0;
    temp_=25;
}
void M3508_Motor::canRxMsgCallback(uint8_t rx_data[8])
{
    this->last_ecd_angle_=ecd_angle_;
    this->ecd_angle_=linearmap((rx_data[0]<<8)|rx_data[1],0,8191,0,360);
    this->rotate_speed_=(rx_data[2]<<8)|rx_data[3];
    this->current_=linearmap((rx_data[4]<<8)|rx_data[5]-16384,
    -16384,16384,-20,20);
    this->temp_=rx_data[6];
    if(ecd_angle_-last_ecd_angle_>180){
        this->delta_ecd_angle_=ecd_angle_-last_ecd_angle_-360;
    }
    else if(ecd_angle_-last_ecd_angle_<-180){
        this->delta_ecd_angle_=360+ecd_angle_-last_ecd_angle_;
    }
    else{
        delta_ecd_angle_=ecd_angle_-last_ecd_angle_;
    }
    this->delta_angle_=this->delta_ecd_angle_/this->ratio_;
    this->angle_+=this->delta_angle_;
}


std::array<float, 7> M3508_Motor::Get_motor_message() const
{
    std::array<float, 7> motor_message{};
    motor_message[0] = this->ratio_;
    motor_message[1] = this->delta_angle_;
    motor_message[2] = this->delta_ecd_angle_;
    motor_message[3] = this->rotate_speed_;
    motor_message[4] = this->current_;
    motor_message[5] = this->temp_;
    motor_message[6] = this->angle_;
    return motor_message;
}
