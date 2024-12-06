#pragma once
#include "main.h"
#include "General_Motor.h"
#ifndef BMI088_H
#define BMI088_H
#define g 9.81
#define PI 3.14159265
class BMI088
{
    float acc_x_, acc_y_, acc_z_;
    float gyro_x_, gyro_y_, gyro_z_;
    float yaw,pitch,roll,init_pitch;
    float yaw_gyro_, pitch_gyro_, roll_gyro_;
    float yaw_acc_, pitch_acc_, roll_acc_;
    float k_error_;
    float ki_,kp_;
    float ax,ay,az;//normalized acc
    float vx,vy,vz;//normalized 算出来的加速度
    float ex,ey,ez;
    float int_ex,int_ey,int_ez;
    float time_interval_;
    uint8_t range_acc_,range_gyro_;
    uint8_t acc_reg_,acc_range_reg_,gyro_reg_,gyro_range_reg_;
    uint8_t receive_acc_data_[7];
    uint8_t receive_gyro_data_[6];
public:
    BMI088(float k_error, float kp, float ki, float time_interval);
    void BMI088_ACCEL_NS_L(void);
    void BMI088_ACCEL_NS_H(void);
    void BMI088_GYRO_NS_L(void);
    void BMI088_GYRO_NS_H(void);
    void BMI088_ReadReg_ACCEL(uint8_t reg, uint8_t *return_data, uint8_t length);
    void BMI088_ReadReg_GYRO(uint8_t reg, uint8_t *return_data, uint8_t length);
    void BMI088_WriteReg(uint8_t reg, uint8_t write_data);
    void BMI088_Init(void);
    void GetAccelData(void);
    void GetGyroData(void);
    float Accel_GetPitch(void);
    float Accel_GetRoll(void);
    float Gyro_GetPitch(void);
    float Gyro_GetRoll(void);
    float Gyro_GetYaw(void);
    void Set_All_Angle(void);
    std::array<float, 3>Get_All_Angle(void);
    void Mahony_Get_Angle(void);
    void Pitch_Init(void);
};


#endif //BMI088_H
