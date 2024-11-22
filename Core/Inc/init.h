
#ifndef INIT_H
#define INIT_H
#ifdef __cplusplus
extern "C" {
#endif
void Init();
typedef struct
{
    float feedback;
    float target;
    float feedforward;
    float output;
}control_data;
void Output_All(control_data data, float feed_back_, float target_, float feed_forward_, float output_);
#ifdef __cplusplus
}
#endif
#endif //INIT_H
