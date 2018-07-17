#ifndef MOTOR_H
#define MOTOR_H
#include "TypeTransform.h"

#define     STOP_CONDITION    0
#define     ACTIVED_CONDITION  1
class TimerContinousSnd
{
public:

    int condition;
    int CurrentRow;
    void active();
    void stop();
    void count_zero();
    bool IsActived();
};


class FeedBackSnd
{
public:

    int FeedBackSndFlag;
    int CurrentRow;
    int condition;
    void active();
    void stop();
    void count_zero();
    bool IsActived();
};



class PackFeedback_AngleSpeed
{
public:
    PackFeedback_AngleSpeed(QByteArray temp);

    short Register_AngleValue;
    short Register_SpeedValue;

    double FeedBackAngle;
    double FeedBackSpeed_degree;
    double FeedBackSpeed_RPM;
    unsigned char MotorID;
    bool IsCorrect;

    void display();
};

#endif // MOTOR_H
