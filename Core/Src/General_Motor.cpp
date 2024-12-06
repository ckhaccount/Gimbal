#include "General_Motor.h"
#include "Basic_Func.h"
#include "PID.h"
#include <array>
extern float YawForward(float angle);
extern float PitchForward(float angle);
Motor::Motor(const MotorType& motortype, float angle_kp, float angle_ki, float angle_kd, float angle_i_max, float angle_out_max, float angle_err_max,
    float speed_kp, float speed_ki, float speed_kd, float speed_i_max, float speed_err_max, float(*AngleForward)(float),float(*SpeedForward)(float angle))://float speed_out_max即为out_current_max
    motortype_(motortype),
    Motor_Angle_PID(angle_kp, angle_ki, angle_kd, angle_i_max, angle_out_max, angle_err_max, AngleForward),
    Motor_Speed_PID(speed_kp, speed_ki, speed_kd, speed_i_max, motortype.out_current_max_, speed_err_max, SpeedForward)
{
    angle_=0;
    delta_angle_=0;
    ecd_angle_=0;
    last_ecd_angle_=0;
    delta_ecd_angle_=0;
    rotate_speed_=0;
    current_=0;
    temp_=0;
}
void Motor::canRxMsgCallback(const uint8_t rx_data[8])
{
    this->last_ecd_angle_=ecd_angle_;
    this->ecd_angle_=linearmap(static_cast<int16_t>((rx_data[0]<<8)|rx_data[1]),0,8191,0,360);
    this->rotate_speed_=static_cast<int16_t>((rx_data[2]<<8)|rx_data[3]);
    this->current_=linearmap(static_cast<int16_t>((rx_data[4]<<8)|rx_data[5]),
    -motortype_.in_current_max_,motortype_.in_current_max_,-motortype_.out_current_max_,motortype_.out_current_max_);
    if(motortype_.has_tem_) this->temp_=static_cast<int16_t>(rx_data[6]);
    if(ecd_angle_-last_ecd_angle_>180){
        this->delta_ecd_angle_=ecd_angle_-last_ecd_angle_-360;
    }
    else if(ecd_angle_-last_ecd_angle_<-180){
        this->delta_ecd_angle_=360+ecd_angle_-last_ecd_angle_;
    }
    else{
        delta_ecd_angle_=ecd_angle_-last_ecd_angle_;
    }
    this->delta_angle_=this->delta_ecd_angle_/this->motortype_.ratio_;
    this->angle_+=this->delta_angle_;
}


std::array<float, 10> Motor::Get_motor_message() const
{
    std::array<float, 10> motor_message{};
    motor_message[0] = this->motortype_.ratio_;
    motor_message[1] = this->delta_angle_;
    motor_message[2] = this->ecd_angle_;
    motor_message[3] = this->rotate_speed_;
    motor_message[4] = this->current_;
    motor_message[5] = this->temp_;
    motor_message[6] = this->angle_;
    motor_message[7] = this->motortype_.in_current_max_;
    motor_message[8] = this->motortype_.out_current_max_;
    motor_message[9] = this->motortype_.ID_;
    return motor_message;
}
extern M3508_Motor_Type yaw_motor_type;
extern M3508_Motor_Type pitch_motor_type;
