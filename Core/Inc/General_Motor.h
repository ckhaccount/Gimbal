#pragma once
#include <array>
#include "PID.h"
#include "MotorType.h"
#ifndef GENERAL_MOTOR_H
#define GENERAL_MOTOR_H
// 通用电机基类



class Motor {
public:
    explicit Motor(const MotorType& motortype, float angle_kp, float angle_ki, float angle_kd, float angle_i_max, float angle_out_max, float angle_err_max,
    float speed_kp, float speed_ki, float speed_kd, float speed_i_max, float speed_err_max);//float speed_out_max即为out_current_max
    void canRxMsgCallback(const uint8_t rx_data[8]);
    [[nodiscard]] std::array<float, 10> Get_motor_message() const;

    PID Motor_Angle_PID;
    PID Motor_Speed_PID;
    MotorType motortype_;
private:
    friend class PID;
    float angle_; // deg 输出端累计转动角度
    float delta_angle_; // deg 输出端新转动的角度
    float ecd_angle_; // deg 当前电机编码器角度
    float last_ecd_angle_; // deg 上次电机编码器角度
    float delta_ecd_angle_; // deg 编码器端新转动的角度
    float rotate_speed_; // dps 反馈转子转速
    float current_; // A 反馈转矩电流
    float temp_; // °C 反馈电机温度

};

#endif //GENERAL_MOTOR_H

