#include "DBUS_RC.h"
#include <iostream>
const char* get_switch_state_string(RC::RCSwitchState_e state)
{
    switch (state)
    {
    case RC::UP:
        return "UP";
    case RC::DOWN:
        return "DOWN";
    case RC::MID:
        return "MID";
    default:
        return "UNKNOWN";
    }

}
const char* get_mouse_press_state_string(RC::MousePressState_e state)
{
    switch (state)
    {
    case RC::PRESS_MOUSE:
        return "PRESSED";
    case RC::NON_PRESS_MOUSE:
        return "RELEASED";
    default:
        return "UNKNOWN";
    }
}
const char* get_key_press_state_string(RC::KeyPressState_e state)
{
    switch (state)
    {
    case RC::PRESS_KEY:
        return "PRESSED";
    case RC::N0N_PRESS_KEY:
        return "RELEASED";
    default:
        return "UNKNOWN";
    }
}

float linearmap(float x, float in_min, float in_max, float out_min, float out_max)
{
    if(in_min!=in_max)
        return (static_cast<float>(x) - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    else{
        std::cout<<"Linear map error: in_min=in_max"<<std::endl;
        return out_max+1;
    }

}
float limit_1(float var1,float max1,float min1)
{
    //超范围返回最值
    if(var1>max1)
    {
        return max1;
    }
    else if(var1<min1)
    {
        return min1;
    }
    else
    {
        return var1;
    }
}
float limit_2(float var2,float max2,float min2)
{
    //超范围返回0
    if(var2>max2 || var2<min2)
    {
        return 0;
    }
    else
    {
        return var2;
    }

}