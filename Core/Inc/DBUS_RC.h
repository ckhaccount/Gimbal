#ifndef DBUS_RC_H
#define DBUS_RC_H
#include "main.h"
#define RC_H
#define RC_CH_VALUE_MIN ((uint16_t)364 )
#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
#define RC_CH_VALUE_MAX ((uint16_t)1684)
#define RC_MOUSE_VALUE_MAX ((int32_t)32767)
#define RC_MOUSE_VALUE_OFFSET ((int32_t)0)
#define RC_MOUSE_VALUE_MIN ((int32_t)-32768)
#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)
#define MOUSE_RELEASE ((uint16_t)0)
#define MOUSE_PRESS ((uint16_t)1)
#define KEY_PRESSED_OFFSET_W ((uint16_t)0x01<<0)
#define KEY_PRESSED_OFFSET_S ((uint16_t)0x01<<1)
#define KEY_PRESSED_OFFSET_A ((uint16_t)0x01<<2)
#define KEY_PRESSED_OFFSET_D ((uint16_t)0x01<<3)
#define KEY_PRESSED_OFFSET_Q ((uint16_t)0x01<<4)
#define KEY_PRESSED_OFFSET_E ((uint16_t)0x01<<5)
#define KEY_PRESSED_OFFSET_SHIFT ((uint16_t)0x01<<6)
#define KEY_PRESSED_OFFSET_CTRL ((uint16_t)0x01<<7)
#define KEY_RELEASE ((uint16_t)0)
#define KEY_PRESS ((uint16_t)1)
#define RC_FRAME_LENGTH 18u
#define RC_RX_BUF_SIZE 18
#define RC_RX_DATA_SIZE 18

class RC{
private:

    uint8_t rx_buf_[RC_RX_BUF_SIZE]{};
    uint8_t rx_data_[RC_RX_DATA_SIZE]{};

public:
    float yaw_max_angle_;
    float pitch_max_angle_;
    typedef enum
    {
        UP=RC_SW_UP,
        MID=RC_SW_MID,
        DOWN=RC_SW_DOWN
      }RCSwitchState_e;
    struct RCSwitch
    {
        RCSwitchState_e l;
        RCSwitchState_e r;
    } RCswitch_{};

    struct RCChannel{
        float r_row;
        float r_col;
        float l_row;
        float l_col;
    } RCChannel_{};

    struct MousePos
    {
        float x;
        float y;
        float z;
    }MousePos_{};
    typedef enum
    {
        NON_PRESS_MOUSE=MOUSE_RELEASE,
        PRESS_MOUSE=MOUSE_PRESS
    }MousePressState_e;
    struct MousePre
    {
        MousePressState_e L;
        MousePressState_e R;
    }MousePre_{};
    typedef enum
    {
        PRESS_KEY=KEY_PRESS,
        N0N_PRESS_KEY=KEY_RELEASE
    }KeyPressState_e;
    struct Key
    {
        KeyPressState_e W;
        KeyPressState_e S;
        KeyPressState_e A;
        KeyPressState_e D;
        KeyPressState_e Q;
        KeyPressState_e E;
        KeyPressState_e Shift;
        KeyPressState_e Ctrl;
    }KeyPre_{};
    RC(float yaw_max_angle, float pitch_max_angle);
    uint8_t* Get_buffer();
    uint8_t* Get_data();
    float Get_CH0_r_row();
    float Get_CH1_r_col();
    float Get_CH2_l_row();
    float Get_CH3_l_col();
    RCSwitchState_e Get_RCSwitch_l();
    RCSwitchState_e Get_RCSwitch_r();
    float Get_MousePos_x();
    float Get_MousePos_y();
    float Get_MousePos_z();
    MousePressState_e Get_MousePre_L();
    MousePressState_e Get_MousePre_R();
    KeyPressState_e Get_Keypress_W();
    KeyPressState_e Get_Keypress_S();
    KeyPressState_e Get_Keypress_A();
    KeyPressState_e Get_Keypress_D();
    KeyPressState_e Get_Keypress_Q();
    KeyPressState_e Get_Keypress_E();
    KeyPressState_e Get_Keypress_Shift();
    KeyPressState_e Get_Keypress_Ctrl();
    void Store_Data();
    void Transmit_Data();
};

#endif //DBUS_RC_H
