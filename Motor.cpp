#include"Motor.h"

void TimerContinousSnd::active()
{
    this->condition = ACTIVED_CONDITION;
}

void TimerContinousSnd::stop()
{
    this->condition = STOP_CONDITION;
}
void TimerContinousSnd::count_zero()
{
    this->CurrentRow=0;
}
bool TimerContinousSnd::IsActived()
{
    if(this->condition)
    {
        return true;
    }

    return false;
}



void FeedBackSnd::active()
{
    this->condition = ACTIVED_CONDITION;
}

void FeedBackSnd::stop()
{
    this->condition = STOP_CONDITION;
}
void FeedBackSnd::count_zero()
{
    this->CurrentRow=0;
}
bool FeedBackSnd::IsActived()
{
    if(this->condition)
    {
        return true;
    }

    return false;
}



PackFeedback_AngleSpeed::PackFeedback_AngleSpeed(QByteArray temp)
{
    /*-----------------------------
    Example Feeback:
    FF FF 01 06 00 FE 0B 00 02 ED

    FF FF : PackHead
    01    : ID
    06    : Rest PackLength
    00    : It means no wrong
    FE 0B : They mean FeedBack Value of Angle Register (0x0BFE)
    00 02 : They mean FeedBack Value of Speed Register (0x0200)
    ED    : CheckSum
    ---------------------------*/


    Register_AngleValue = Extract2RGValue(temp,INDEX_ANGLELOWBYTE,INDEX_ANGLEHIGHBYTE);
    FeedBackAngle  = (double)Register_AngleValue/(CUSTOMRG_MX_64AT)*CUSTOMANGLE_MX_64AT-INIT_ANGLE;



    Register_SpeedValue = Extract2RGValue(temp,INDEX_SPEEDLOWBYTE,INDEX_SPEEDHIGHBYTE);

    if(Register_SpeedValue>1024)
    {
        Register_SpeedValue=1024-Register_SpeedValue;
    }

    FeedBackSpeed_degree = RPM2Degree((double)Register_SpeedValue/CUSTOMRG_SPEED*CUSTOMSPEED);

    FeedBackSpeed_RPM = Degree2RPM(FeedBackSpeed_degree);

    MotorID = (unsigned char)temp[2];

    IsCorrect = ((unsigned char)temp[4] == 0);
}

void PackFeedback_AngleSpeed::display()
{
    qDebug() << "--------------------------------------------" <<endl;
    qDebug() << "ID                   :" << MotorID << endl;
    qDebug() << "Reigster Angle       :" << QString::number(this->Register_AngleValue,16).toUpper() << endl;
    qDebug() << "Register Speed       :" << QString::number(this->Register_SpeedValue,16).toUpper()<< endl;
    qDebug() << "FeedBack Angle       :" << this->FeedBackAngle << endl;
    qDebug() << "FeedBack Speed_Degree:" << this->FeedBackSpeed_degree << endl;
    qDebug() << "FeedBack Speed_RPM   :" << this->FeedBackSpeed_RPM << endl;
    qDebug() << "Is Correct           :" << (IsCorrect?"corrct":"incorrect") <<endl;
    qDebug() << "--------------------------------------------" <<endl;
}
