#include "main.h"
#include "gpio.h"
#include "spi.h"
#include "BMI088.h"
#include <math.h>
#include <cmath>
BMI088::BMI088(float k_error, float kp, float ki, float time_interval):k_error_(k_error), kp_(kp), ki_(ki), time_interval_(time_interval){
  acc_reg_=0x12;
  acc_range_reg_=0x41;
  gyro_reg_=0x02;
  gyro_range_reg_=0x0F;
  int_ex=0;
  int_ey=0;
  int_ez=0;
  yaw=0.0f;
  pitch=0.0f;
  init_pitch=0.0f;
  roll=0.0f;
}
void BMI088::BMI088_ACCEL_NS_L(void) {
    HAL_GPIO_WritePin(CS1_Accel_GPIO_Port, CS1_Accel_Pin, GPIO_PIN_RESET);
}
void BMI088::BMI088_ACCEL_NS_H(void) {
    HAL_GPIO_WritePin(CS1_Accel_GPIO_Port, CS1_Accel_Pin, GPIO_PIN_SET);
}
void BMI088::BMI088_GYRO_NS_L(void) {
    HAL_GPIO_WritePin(CS1_Gyro_GPIO_Port, CS1_Gyro_Pin, GPIO_PIN_RESET);
}
void BMI088::BMI088_GYRO_NS_H(void) {
    HAL_GPIO_WritePin(CS1_Gyro_GPIO_Port, CS1_Gyro_Pin, GPIO_PIN_SET);
}

void BMI088::BMI088_ReadReg_ACCEL(uint8_t reg, uint8_t *return_data, uint8_t length) {
    BMI088_ACCEL_NS_L();
    uint8_t rx_adress= reg | 0x80;
    HAL_SPI_Transmit(&hspi1, &rx_adress, 1, 1000);
    while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX);
    HAL_SPI_Receive(&hspi1, return_data, 1, 1000);
    while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_RX);
    HAL_SPI_Receive(&hspi1, return_data, length, 1000);
    while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_RX); // 等待SPI接收完成
    BMI088_ACCEL_NS_H();
}
void BMI088::BMI088_ReadReg_GYRO(uint8_t reg, uint8_t *return_data, uint8_t length) {
    BMI088_GYRO_NS_L();
    uint8_t rx_adress= reg | 0x80;
    HAL_SPI_Transmit(&hspi1, &rx_adress, 1, 1000);
    while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX);
    HAL_SPI_Receive(&hspi1, return_data, length, 1000);
    while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_RX); // 等待SPI接收完成
    BMI088_GYRO_NS_H();
}
void BMI088::BMI088_WriteReg(uint8_t reg, uint8_t write_data) {
    uint8_t tx_adress= reg & 0x7F;
    HAL_SPI_Transmit(&hspi1, &tx_adress, 1, 1000);
    while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX);
    HAL_SPI_Transmit(&hspi1,&write_data,1,1000);
    while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX); // 等待SPI接收完成
}

void BMI088::BMI088_Init(void) {
    // Soft Reset ACCEL
    BMI088_ACCEL_NS_L();
    BMI088_WriteReg(0x7E, 0xB6); // Write 0xB6 to ACC_SOFTRESET(0x7E)
    HAL_Delay(1);
    BMI088_ACCEL_NS_H();

    // Soft Reset GYRO
    BMI088_GYRO_NS_L();
    BMI088_WriteReg(0x14, 0xB6); // Write 0xB6 to GYRO_SOFTRESET(0x14)
    HAL_Delay(30);
    BMI088_GYRO_NS_H();

    // Switch ACCEL to Normal Mode
    BMI088_ACCEL_NS_L();
    HAL_Delay(1);
    BMI088_WriteReg(0x7D, 0x04); // Write 0x04 to ACC_PWR_CTRL(0x7D)
    HAL_Delay(1);
    BMI088_ACCEL_NS_H();
}
void BMI088::GetAccelData(void){
    int16_t Accel_X_int16=0, Accel_Y_int16=0, Accel_Z_int16=0;
    BMI088_ReadReg_ACCEL(acc_reg_,receive_acc_data_,6);
    BMI088_ReadReg_ACCEL(acc_range_reg_,&range_acc_,1);
    Accel_X_int16=receive_acc_data_[1]<<8 | receive_acc_data_[0];
    Accel_Y_int16=receive_acc_data_[3]<<8 | receive_acc_data_[2];
    Accel_Z_int16=(receive_acc_data_[5])<<8 | receive_acc_data_[4];
    acc_x_=Accel_X_int16*pow(2,range_acc_+1)*1.5/32768.*g;
    acc_y_=Accel_Y_int16*pow(2,range_acc_+1)*1.5/32768.*g;
    acc_z_=Accel_Z_int16*pow(2,range_acc_+1)*1.5/32768.*g;
}
void BMI088::GetGyroData(void)
{
    int16_t Rate_X_int16=0, Rate_Y_int16=0, Rate_Z_int16=0;
    BMI088_ReadReg_GYRO(gyro_reg_,receive_gyro_data_,6);
    BMI088_ReadReg_GYRO(gyro_range_reg_,&range_gyro_,1);
    Rate_X_int16=receive_gyro_data_[1]<<8 | receive_gyro_data_[0];
    Rate_Y_int16=receive_gyro_data_[3]<<8 | receive_gyro_data_[2];
    Rate_Z_int16=receive_gyro_data_[5]<<8 | receive_gyro_data_[4];
    gyro_x_=Rate_X_int16*1000.*pow(2,-range_gyro_+1)/32768.;
    gyro_y_=Rate_Y_int16*1000.*pow(2,-range_gyro_+1)/32768.;
    gyro_z_=Rate_Z_int16*1000.*pow(2,-range_gyro_+1)/32768.;
}
float BMI088::Accel_GetPitch(void){
    if(acc_z_==0 && acc_y_==0){
        return (acc_x_ > 0) ? -90 : 90;
    }
    else
        pitch_acc_=-atan2(acc_x_,acc_z_/abs(acc_z_)*sqrt(pow(acc_y_,2)+pow(acc_z_,2)))*180./PI;
        return pitch_acc_;
 }
float BMI088::Accel_GetRoll(void){
    if (acc_z_==0) {
        return (acc_y_ > 0) ? 90 : -90;
    }
    else
      roll_acc_=atan2(acc_y_,acc_z_)*180./PI;
        return atan2(acc_y_,acc_z_)*180./PI;
}
float BMI088::Gyro_GetPitch(){
    float new_pitch=pitch+(cos(roll*PI/180.)*gyro_y_-sin(roll*PI/180.)*gyro_z_)*time_interval_;
    pitch_gyro_=new_pitch;
    return new_pitch;
}
float BMI088::Gyro_GetRoll(){
    float new_roll=roll+(gyro_x_+sin(pitch*PI/180.)*sin(roll*PI/180.)/cos(pitch*PI/180.)*gyro_y_+cos(roll*PI/180.)*sin(pitch*PI/180.)/cos(pitch*PI/180.)*gyro_z_)*time_interval_;
    roll_gyro_=new_roll;
    return new_roll;
}
float BMI088::Gyro_GetYaw(){
    float new_yaw=yaw;
    if(abs((sin(roll*PI/180.)*gyro_y_/cos(pitch*PI/180.)+cos(roll*PI/180.)*gyro_z_/cos(pitch*PI/180.))*time_interval_)>360)
      new_yaw+=0;
    else
      new_yaw+=(sin(roll*PI/180.)*gyro_y_/cos(pitch*PI/180.)+cos(roll*PI/180.)*gyro_z_/cos(pitch*PI/180.))*time_interval_;
    yaw_gyro_=new_yaw;
    return new_yaw;
}
void BMI088::Set_All_Angle(){
    GetAccelData();
    GetGyroData();
    float Pitch=k_error_*Accel_GetPitch()+(1-k_error_)*Gyro_GetPitch();
    float Roll=k_error_*Accel_GetRoll()+(1-k_error_)*Gyro_GetRoll();
    float Yaw=Gyro_GetYaw();
    pitch=Pitch;
    roll=Roll;
    yaw=Yaw;
}
std::array<float, 3> BMI088::Get_All_Angle(){
    std::array<float, 3> angles{};
    angles[0]=pitch;
    angles[1]=roll;
    angles[2]=yaw;
    return angles;
}
void BMI088::Mahony_Get_Angle(void){
    GetGyroData();
    GetAccelData();
    float acc_recipnorm=sqrtf(acc_x_*acc_x_ + acc_y_*acc_y_ + acc_z_+acc_z_);
    ax=acc_x_*acc_recipnorm;
    ay=acc_y_*acc_recipnorm;
    az=acc_z_*acc_recipnorm;
    vx=-sin(pitch*PI/180);
    vy=cos(pitch*PI/180)*sin(roll*PI/180);
    vz=cos(pitch*PI/180)*cos(roll*PI/180);
    ex=(ay*vz-az*vy);
    ey=(az*vx-ax*vz);
    ez=(ax*vy-ay*vx);
    int_ex+=ex*time_interval_;
    int_ey+=ey*time_interval_;
    int_ez+=ez*time_interval_;
    gyro_x_=gyro_x_+kp_*ex+ki_*int_ex;
    gyro_y_=gyro_y_+kp_*ey+ki_*int_ey;
    gyro_z_=gyro_z_+kp_*ez+ki_*int_ez;
    pitch+=(cos(roll*PI/180)*gyro_y_-sin(roll*PI/180)*gyro_z_)*time_interval_;
    roll+=(gyro_x_+sin(pitch*PI/180)*sin(roll*PI/180)/cos(pitch*PI/180)*gyro_y_+cos(roll*PI/180)*sin(pitch*PI/180)/cos(pitch*PI/180)*gyro_z_)*time_interval_;
    yaw+=(sin(roll*PI/180)/cos(pitch*PI/180)*gyro_y_+cos(roll*PI/180)/cos(pitch*PI/180)*gyro_z_)*time_interval_;
}
void BMI088::Pitch_Init(void){
  GetAccelData();
  init_pitch=Accel_GetPitch();
  }