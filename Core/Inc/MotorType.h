#pragma once
#include "cstdint"
#ifndef MOTORTYPE_H
#define MOTORTYPE_H
struct MotorType {
    uint32_t ID_;
    uint16_t Tran_Identifier_;
    uint16_t Rece_Identifier_;
    float in_current_max_;
    float out_current_max_;
    float ratio_;
    int has_tem_;
    explicit MotorType(const uint32_t id) : ID_(id), Tran_Identifier_(0), Rece_Identifier_(0),
                              in_current_max_(0), out_current_max_(0), ratio_(0), has_tem_(0) {}
    virtual ~MotorType() = default;
};

// M3508 电机子类
struct M3508_Motor_Type : public MotorType {
    explicit M3508_Motor_Type(const uint32_t id) : MotorType(id) {
        if (id<=4)
            Tran_Identifier_ = 0x200;
        else
            Tran_Identifier_ = 0x1FF;
        Rece_Identifier_ = 0x200+id;
        in_current_max_ = 16384;
        out_current_max_ = 20;
        ratio_ = 3591.0 / 187.0;
        has_tem_ = 1;
    }
};

// GM6020 电机子类
struct GM6020_Motor_Type : public MotorType {
    explicit GM6020_Motor_Type(const uint32_t id, int is_vol) : MotorType(id) {
        if (is_vol)
        {
            in_current_max_ = 25000;
            if (id<=4)
                Tran_Identifier_ = 0x1FF;
            else
                Tran_Identifier_ = 0x2FF;
        }
        else
        {
            in_current_max_ = 16384;
            if (id<=4)
                Tran_Identifier_ = 0x1FE;
            else
                Tran_Identifier_ = 0x2FE;
        }
        out_current_max_ = 3;
        Rece_Identifier_ = 0x204+id;
        ratio_ = 1;
        has_tem_ = 1;
    }
};

// M2006 电机子类
struct M2006_Motor_Type : public MotorType {
    explicit M2006_Motor_Type(uint32_t id) : MotorType(id) {
        if(id<=4)
            Tran_Identifier_ = 0x200;
        else
            Tran_Identifier_ = 0x1FF;
        Rece_Identifier_ = 0x200+id;
        in_current_max_ = 10000;
        out_current_max_ = 10;
        ratio_ = 36;
        has_tem_ = 0;
    }
};
#endif //MOTORTYPE_H
