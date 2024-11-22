#include "DBUS_RC.h"
#ifndef BASIC_FUNC_H
#define BASIC_FUNC_H
float linearmap(float x, float in_min, float in_max, float out_min, float out_max);
const char* get_switch_state_string(RC::RCSwitchState_e state);
const char* get_mouse_press_state_string(RC::MousePressState_e state);
const char* get_key_press_state_string(RC::KeyPressState_e state);
float limit_1(float var1,float max1,float min1);//超范围返回最值
float limit_2(float var2,float max2,float min2);//超范围返回0
#endif //BASIC_FUNC_H
