#include "main.h"
#include "DBUS_RC.h"
#include <iostream>
#include "Basic_Func.h"

RC::RC(float yaw_max_angle, float pitch_max_angle)
    : yaw_max_angle_(yaw_max_angle), pitch_max_angle_(pitch_max_angle),RCswitch_{MID, MID},
      RCChannel_{1024, 1024, 1024, 1024},
      MousePos_{0, 0, 0},
      MousePre_{NON_PRESS_MOUSE, NON_PRESS_MOUSE},
      KeyPre_{N0N_PRESS_KEY, N0N_PRESS_KEY, N0N_PRESS_KEY, N0N_PRESS_KEY,
              N0N_PRESS_KEY, N0N_PRESS_KEY, N0N_PRESS_KEY, N0N_PRESS_KEY}
{
    for (auto& byte : rx_buf_) {
        byte = 0;
    }
    for (auto& byte : rx_data_) {
        byte = 0;
    }
}

uint8_t* RC::Get_buffer()
{
    return this->rx_buf_;
}
uint8_t* RC::Get_data()
{
    return this->rx_data_;
}
float RC::Get_CH0_r_row()
{
    uint16_t origin_data_CH0= ((this->rx_data_[0])|(this->rx_data_[1]<<8))&0x07ff;
    return linearmap(static_cast<int16_t>(origin_data_CH0),RC_CH_VALUE_MIN,RC_CH_VALUE_MAX,-1,1);
}
float RC::Get_CH1_r_col()
{
    uint16_t origin_data_CH1 = (((this->rx_data_[1])>>3)|((this->rx_data_[2]))<<5)&0x07ff;
    return linearmap(static_cast<int16_t>(origin_data_CH1),RC_CH_VALUE_MIN,RC_CH_VALUE_MAX,-1,1);
}

float RC::Get_CH2_l_row()
{
    uint16_t origin_data_CH2=(((this->rx_data_[2]>>6)|(this->rx_data_[3]<<2))|(this->Get_data()[4]<<10))&0x07ff;
    return linearmap(static_cast<int16_t>(origin_data_CH2),RC_CH_VALUE_MIN,RC_CH_VALUE_MAX,-1,1);
}
float RC::Get_CH3_l_col()
{
    uint16_t origin_data_CH3=((this->rx_data_[4]>>1)|(this->rx_data_[5]<<7))&0x07ff;
    return linearmap(static_cast<int16_t>(origin_data_CH3),RC_CH_VALUE_MIN,RC_CH_VALUE_MAX,-1,1);;
}
RC::RCSwitchState_e RC::Get_RCSwitch_l()
{
    uint8_t origin_data_Switch_l=(this->rx_data_[5]>>4)&0x0003;
    return static_cast<RCSwitchState_e>(origin_data_Switch_l);;
}
RC::RCSwitchState_e RC::Get_RCSwitch_r()
{
    uint8_t origin_data_Switch_r=(this->rx_data_[5]>>6)&0x0003;
    return static_cast<RCSwitchState_e>(origin_data_Switch_r);

}
float RC::Get_MousePos_x()
{
    uint16_t origin_data_MousePos_x = static_cast<uint16_t>(this->rx_data_[6]) | (static_cast<uint16_t>(this->rx_data_[7]) << 8);
    return linearmap(static_cast<int16_t>(origin_data_MousePos_x),RC_MOUSE_VALUE_MIN,RC_MOUSE_VALUE_MAX,-1,1);
}
float RC::Get_MousePos_y()
{
    uint16_t origin_data_MousePos_y = static_cast<uint16_t>(this->rx_data_[8]) | (static_cast<uint16_t>(this->rx_data_[9]) << 8);
    return linearmap(static_cast<int16_t>(origin_data_MousePos_y),RC_MOUSE_VALUE_MIN,RC_MOUSE_VALUE_MAX,-1,1);
}
float RC::Get_MousePos_z()
{
    uint16_t origin_data_MousePos_z = static_cast<uint16_t>(this->rx_data_[10]) | (static_cast<uint16_t>(this->rx_data_[11]) << 8);
    return linearmap(static_cast<int16_t>(origin_data_MousePos_z),RC_MOUSE_VALUE_MIN,RC_MOUSE_VALUE_MAX,-1,1);
}
RC::MousePressState_e RC::Get_MousePre_L()
{
    uint8_t origin_data_MousePre_L = this->rx_data_[12];
    return static_cast<MousePressState_e>(origin_data_MousePre_L);
}
RC::MousePressState_e RC::Get_MousePre_R()
{
    uint8_t origin_data_MousePre_R = this->rx_data_[13];
    return static_cast<MousePressState_e>(origin_data_MousePre_R);
}
RC::KeyPressState_e RC::Get_Keypress_W()
{
    uint8_t origin_data_Keypress_W = this->rx_data_[14]&0x01;
    return static_cast<KeyPressState_e>(origin_data_Keypress_W);
}
RC::KeyPressState_e RC::Get_Keypress_S()
{
    uint8_t origin_data_Keypress_S = (this->rx_data_[14]&0x02)>>1;
    return static_cast<KeyPressState_e>(origin_data_Keypress_S);
}
RC::KeyPressState_e RC::Get_Keypress_A()
{
    uint8_t origin_data_Keypress_A = (this->rx_data_[14]&0x04)>>2;
    return static_cast<KeyPressState_e>(origin_data_Keypress_A);
}
RC::KeyPressState_e RC::Get_Keypress_D()
{
    uint8_t origin_data_Keypress_D = (this->rx_data_[14]&0x08)>>3;
    return static_cast<KeyPressState_e>(origin_data_Keypress_D);
}
RC::KeyPressState_e RC::Get_Keypress_Q()
{
    uint8_t origin_data_Keypress_Q = (this->rx_data_[14]&0x10)>>4;
    return static_cast<KeyPressState_e>(origin_data_Keypress_Q);
}
RC::KeyPressState_e RC::Get_Keypress_E()
{
    uint8_t origin_data_Keypress_E = (this->rx_data_[14]&0x20)>>5;
    return static_cast<KeyPressState_e>(origin_data_Keypress_E);
}
RC::KeyPressState_e RC::Get_Keypress_Shift()
{
    uint8_t origin_data_Keypress_Shift = (this->rx_data_[14]&0x40)>>6;
    return static_cast<KeyPressState_e>(origin_data_Keypress_Shift);
}
RC::KeyPressState_e RC::Get_Keypress_Ctrl()
{
    uint8_t origin_data_Keypress_Ctrl = (this->rx_data_[14]&0x80)>>7;
    return static_cast<KeyPressState_e>(origin_data_Keypress_Ctrl);
}
//this function returns the state of switch and mouse with string instead of enum


void RC::Store_Data()
{
    RCChannel_.r_row=Get_CH0_r_row();
    RCChannel_.r_col=Get_CH1_r_col();
    RCChannel_.l_row=Get_CH2_l_row();
    RCChannel_.l_col=Get_CH3_l_col();
    RCswitch_.l=Get_RCSwitch_l();
    RCswitch_.r=Get_RCSwitch_r();
    MousePos_.x=Get_MousePos_x();
    MousePos_.y=Get_MousePos_y();
    MousePos_.z=Get_MousePos_z();
    MousePre_.L=Get_MousePre_L();
    MousePre_.R=Get_MousePre_R();
    KeyPre_.W=Get_Keypress_W();
    KeyPre_.S=Get_Keypress_S();
    KeyPre_.A=Get_Keypress_A();
    KeyPre_.D=Get_Keypress_D();
    KeyPre_.Q=Get_Keypress_Q();
    KeyPre_.E=Get_Keypress_E();
    KeyPre_.Shift=Get_Keypress_Shift();
    KeyPre_.Ctrl=Get_Keypress_Ctrl();
}

// void RC::Transmit_Data()
// {
//     char buffer[50];
//     snprintf(buffer, sizeof(buffer), "The CH0_Position is: %.4f\r\n", RCChannel_.r_row);
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The CH1_Position is: %.4f\r\n", RCChannel_.r_col);
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The CH2_Position is: %.4f\r\n", RCChannel_.l_row);
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The CH3_Position is: %.4f\r\n", RCChannel_.l_col);
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The left switch is: %s\r\n", get_switch_state_string(RCswitch_.l));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The right switch is: %s\r\n", get_switch_state_string(RCswitch_.r));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The Mouse_x_Position is: %.4f\r\n", MousePos_.x);
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The Mouse_y_Position is: %.4f\r\n", MousePos_.y);
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The Mouse_z_Position is: %.4f\r\n", MousePos_.z);
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The mouse left press is: %s\r\n", get_mouse_press_state_string(MousePre_.L));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The mouse right press is: %s\r\n", get_mouse_press_state_string(MousePre_.R));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The key W is: %s\r\n", get_key_press_state_string(KeyPre_.W));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The key S is: %s\r\n", get_key_press_state_string(KeyPre_.S));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The key A is: %s\r\n", get_key_press_state_string(KeyPre_.A));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The key D is: %s\r\n", get_key_press_state_string(KeyPre_.D));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The key Q is: %s\r\n", get_key_press_state_string(KeyPre_.Q));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The key E is: %s\r\n", get_key_press_state_string(KeyPre_.E));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The key Shift is: %s\r\n", get_key_press_state_string(KeyPre_.Shift));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
//     snprintf(buffer, sizeof(buffer), "The key Ctrl is: %s\r\n", get_key_press_state_string(KeyPre_.Ctrl));
//     HAL_UART_Transmit(&huart6, reinterpret_cast<uint8_t*>(buffer), strlen(buffer),100);
// }
