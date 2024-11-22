#pragma once
#include "MotorType.h"
#include "cstdint"
#ifndef PID_H
#define PID_H
class PID
{
public:
    PID(float kp, float ki, float kd, float i_max, float out_max, float err_max);
    float calc(float ref, float fdb);
    float Expect_Speed(float real_angle);
    void Uint16_Current(float real_speed, MotorType& motortype, uint8_t *TxData);
    void Set_Ref(float ref);
    void Set_Fed(const float fed);
private:
    uint16_t current_message;
    float kp_, ki_, kd_;
    float i_max_,out_max_;
    float output_;
    float ref_,fdb_;
    float err_,err_sum_,err_max_,last_err_;
    float pout_,iout_,dout_;
};
#endif //PID_H
