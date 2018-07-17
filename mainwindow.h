#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QDebug>
#include <QSpinBox>
#include <QSlider>
#include <QTimer>
#include <QTextCodec>
#include "TypeTransform.h"
#include "win_qextserialport.h"
#include "dialogdisplay.h"
#include "xmlParse.h"
#include "Motor.h"
#include "FileOperate.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
//members:
    Win_QextSerialPort * ComRightLeg;
    Win_QextSerialPort * ComLeftLeg;
    Win_QextSerialPort * ComUpperLimb;
    double current_angle[NUM_MOTORS];
    double dest_angle[NUM_MOTORS];
    double desi_speed[NUM_MOTORS];        //∂»√ø√Î
    double feedback_angle[NUM_MOTORS];
    double feedback_speed[NUM_MOTORS];
    QString showStr;
    QByteArray temp_right;
    QByteArray temp_left;
    int GetModel;
    int Motor_ID_Right;
    int Motor_ID_Left;
    int MotorCntLeft;
    int MotorCntRight;
    int cnt;
    int cnt_left;
    double DesireDuration;
    QTime current_time;
    QTime start_time;
    DialogDisplay dialog_display;
    QStandardItemModel *model;
    QDomDocument doc;
    QTimer*timer;
    int TimerCounter;
    int TimerAddFlag;
    int ChangeStep;
    int FeedbackFlag;
    TimerContinousSnd TimerContinousSndModel;
    FeedBackSnd FeedBackSndModel;
    int Left_finished;
    int Right_finished;
    int flag_motor_init;


//functions:
    void serial_init();
    void parameter_init();
    void Motor_Reset();
    void timer_init();
    void table_init();
    void sendMotor(int ID,double Angle);
    void SndFeedBackRequest();
    bool MissionFinished();
    bool MotorsQuit();
    void get_Motor_angle_speed(int ID);
    QString CombineStr(unsigned char ID);
    void send_right_leg_motors(double time);
    void send_left_leg_motors(double time);
    void send_upper_limb_motors(double time);
    void send_row(int row);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

private slots:
    void on_setAngleSilder16_valueChanged(int value);
    void on_setAngleSilder15_valueChanged(int value);
    void on_setAngleSilder14_valueChanged(int value);
    void on_setAngleSilder13_valueChanged(int value);
    void on_setAngleSilder12_valueChanged(int value);
    void on_setAngleSilder11_valueChanged(int value);
    void on_setAngleSilder10_valueChanged(int value);
    void on_setAngleSilder16_sliderReleased();
    void on_setAngleSilder15_sliderReleased();
    void on_setAngleSilder14_sliderReleased();
    void on_setAngleSilder13_sliderReleased();
    void on_setAngleSilder12_sliderReleased();
    void on_setAngleSilder11_sliderReleased();
    void on_setAngleSilder10_sliderReleased();
    void on_ButtonAngle16Down_clicked();
    void on_ButtonAngle16Up_clicked();
    void on_ButtonAngle15Down_clicked();
    void on_ButtonAngle15Up_clicked();
    void on_ButtonAngle14Down_clicked();
    void on_ButtonAngle14Up_clicked();
    void on_ButtonAngle13Down_clicked();
    void on_ButtonAngle13Up_clicked();
    void on_ButtonAngle12Down_clicked();
    void on_ButtonAngle12Up_clicked();
    void on_ButtonAngle11Down_clicked();
    void on_ButtonAngle11Up_clicked();
    void on_ButtonAngle10Down_clicked();
    void on_ButtonAngle10Up_clicked();
    void on_pushButton_clicked();
    void on_ButtonAngle9Down_clicked();
    void on_ButtonAngle9Up_clicked();
    void on_ButtonAngle8Down_clicked();
    void on_ButtonAngle8Up_clicked();
    void on_ButtonAngle7Down_clicked();
    void on_ButtonAngle7Up_clicked();
    void on_ButtonAngle6Down_clicked();
    void on_ButtonAngle6Up_clicked();
    void on_ButtonAngle5Down_clicked();
    void on_ButtonAngle5Up_clicked();
    void on_ButtonAngle4Down_clicked();
    void on_ButtonAngle4Up_clicked();
    void on_ButtonAngle3Down_clicked();
    void on_ButtonAngle3Up_clicked();
    void on_ButtonAngle2Down_clicked();
    void on_ButtonAngle2Up_clicked();
    void on_ButtonAngle1Down_clicked();
    void on_ButtonAngle1Up_clicked();
    void on_ButtonAngle0Down_clicked();
    void on_ButtonAngle0Up_clicked();
    void on_ButtonCountZero_clicked();
    void on_ButtonRunAll_clicked();
    void timeup();
    void on_setAngleSilder9_sliderReleased();
    void on_setAngleSilder9_valueChanged(int value);
    void on_setAngleSilder8_sliderReleased();
    void on_setAngleSilder8_valueChanged(int value);
    void on_setAngleSilder7_sliderReleased();
    void on_setAngleSilder7_valueChanged(int value);
    void on_setAngleSilder6_sliderReleased();
    void on_setAngleSilder6_valueChanged(int value);
    void on_setAngleSilder5_sliderReleased();
    void on_setAngleSilder5_valueChanged(int value);
    void on_setAngleSilder4_sliderReleased();
    void on_setAngleSilder4_valueChanged(int value);
    void on_setAngleSilder3_sliderReleased();
    void on_setAngleSilder3_valueChanged(int value);
    void on_setAngleSilder2_sliderReleased();
    void on_setAngleSilder2_valueChanged(int value);
    void on_setAngleSilder1_sliderReleased();
    void on_setAngleSilder1_valueChanged(int value);
    void on_setAngleSilder0_sliderReleased();
    void on_setAngleSilder0_valueChanged(int value);
    void on_feedback_clicked();
    void on_dele_clicked();
    void on_insert_clicked();
    void on_table_clicked(QModelIndex index);
    void on_CleanTable_clicked();
    void on_SaveFile_clicked();
    void on_ButtonChooseFile_clicked();
    void rightleg_feedback();
    void leftleg_feedback();
    void ComUpperLimb_feedback();
    void on_send_clicked();
};

#endif // MAINWINDOW_H
