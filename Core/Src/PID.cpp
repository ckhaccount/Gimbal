#include "PID.h"

#include <functional>

#include "Basic_Func.h"
#include "General_Motor.h"
PID::PID(float kp, float ki, float kd, float i_max, float out_max, float err_max):
    kp_(kp),ki_(ki),kd_(kd),
    i_max_(i_max),out_max_(out_max),err_max_(err_max)

{
    this->current_message=0;
    this->output_=0;
    this->ref_=0;
    this->fdb_=0;
    this->err_=ref_-fdb_;
    this->last_err_=0;
    this->err_sum_=0;
    this->pout_=0;
    this->iout_=0;
    this->dout_=0;
}
float PID::calc(float ref,float fdb)
{
    last_err_=err_;
    err_=ref-fdb;
    err_sum_+=limit_2(err_,err_max_,-err_max_);
    err_sum_=limit_1(err_sum_,err_max_,err_max_);
    pout_=kp_*err_;
    iout_=limit_1(ki_*err_sum_,i_max_,-i_max_);
    dout_=kd_*(err_-last_err_);
    output_=limit_1(pout_+iout_+dout_,out_max_,-out_max_);
    return output_;
}
float PID::Expect_Speed(const Motor &motor)
{
    fdb_=motor.angle_;
    return limit_1(calc(ref_,fdb_),100,-100);
}
void PID::Set_Fed_Speed(const Motor &motor)
{
    this->fdb_=motor.rotate_speed_;
}
void PID::Set_Ref_Speed(Motor &motor)
{
    this->ref_=motor.Motor_Angle_PID.Expect_Speed(motor);
;
}
void PID::Set_Ref_Angle(float ref)
{
    ref_=ref;
}

void PID::Uint16_Current(Motor &motor, uint8_t *TxData)
{
    /*
     * this function gets the real speed of motor and
     * transform it to current transmitting to the motor with PID.
     */
    fdb_=motor.rotate_speed_;
    output_=limit_1(calc(ref_,fdb_),out_max_,-out_max_);
    current_message=static_cast<uint16_t>(linearmap(output_,-motor.motortype_.out_current_max_,motor.motortype_.out_current_max_,-motor.motortype_.in_current_max_,motor.motortype_.in_current_max_));
    if(motor.motortype_.ID_<=4)
    {
        TxData[2*static_cast<int>(motor.motortype_.ID_)-2]=current_message>>8 & 0xFF;
        TxData[2*static_cast<int>(motor.motortype_.ID_)-1]=current_message & 0xFF;
    }
    else
    {
        TxData[2*static_cast<int>(motor.motortype_.ID_)-10]=current_message>>8 & 0xFF;
        TxData[2*static_cast<int>(motor.motortype_.ID_)-9]=current_message & 0xFF;
    }
}
