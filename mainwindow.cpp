#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial_init();
    parameter_init();
    Motor_Reset();
    table_init();
    timer_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::serial_init()
{
//COM right leg:
    QString comPortStr = "\\\\.\\COM" + QString::number (13, 10);
    ComRightLeg = new Win_QextSerialPort(comPortStr,QextSerialBase::EventDriven);
    ComRightLeg->open (QIODevice::ReadWrite);
     if (ComRightLeg->isOpen ())
     {
          qDebug() << "Serial right leg sucessfully open serial" <<endl;
          ComRightLeg->setDataBits (DATA_8);
          ComRightLeg->setBaudRate (BAUD2000000);
          ComRightLeg->setParity (PAR_NONE);
          ComRightLeg->setStopBits (STOP_1);
          ComRightLeg->setFlowControl (FLOW_OFF);     //设置无数据流控制，
          ComRightLeg->setTimeout (500);              //设置延时
     }
     else
     {
          qDebug() << "Serial right leg open fail" <<endl;
     }
     connect(ComRightLeg,SIGNAL(readyRead()),this,SLOT(rightleg_feedback()));


//COM left leg:
     comPortStr = "\\\\.\\COM" + QString::number (15, 10);
     ComLeftLeg = new Win_QextSerialPort(comPortStr,QextSerialBase::EventDriven);
     ComLeftLeg->open (QIODevice::ReadWrite);
     if (ComLeftLeg->isOpen ())
     {
          qDebug() << "Serial left leg sucessfully open serial" << endl;
          ComLeftLeg->setDataBits (DATA_8);
          ComLeftLeg->setBaudRate (BAUD2000000);
          ComLeftLeg->setParity (PAR_NONE);
          ComLeftLeg->setStopBits (STOP_1);
          ComLeftLeg->setFlowControl (FLOW_OFF);     //设置无数据流控制，
          ComLeftLeg->setTimeout (500);              //设置延时
     }
     else
     {
          qDebug() << "Serial left leg open fail" <<endl;
     }
          connect(ComLeftLeg,SIGNAL(readyRead()),this,SLOT(leftleg_feedback()));

//COM upper limb:
     comPortStr = "\\\\.\\COM" + QString::number (17, 10);
     ComUpperLimb = new Win_QextSerialPort(comPortStr,QextSerialBase::EventDriven);
     ComUpperLimb->open (QIODevice::ReadWrite);
     if (ComUpperLimb->isOpen ())
     {
          qDebug() << "Serial Upper Limb sucessfully open serial" << endl;
          ComUpperLimb->setDataBits (DATA_8);
          ComUpperLimb->setBaudRate (BAUD2000000);
          ComUpperLimb->setParity (PAR_NONE);
          ComUpperLimb->setStopBits (STOP_1);
          ComUpperLimb->setFlowControl (FLOW_OFF);     //设置无数据流控制，
          ComUpperLimb->setTimeout (500);              //设置延时
     }
     else
     {
          qDebug() << "Serial Upper Limb open fail" <<endl;
     }
          connect(ComUpperLimb,SIGNAL(readyRead()),this,SLOT(ComUpperLimb_feedback()));
 }


void MainWindow::parameter_init()
{
     MotorCntRight = 5;
     cnt = 0;
     DesireDuration = 1;
     TimerCounter = 0;
     TimerAddFlag = 0;
     TimerContinousSndModel.stop();
     TimerContinousSndModel.count_zero();
     FeedBackSndModel.stop();
     FeedBackSndModel.count_zero();
     ChangeStep = 1;
     QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
     FeedbackFlag = 0;
     FeedBackSndModel.FeedBackSndFlag = 0;
     this->Left_finished = 0;
     this->Right_finished = 0;


}

void MainWindow::send_right_leg_motors(double time)
{
    QLineEdit*lineEdits[] = { ui->Line0 , ui->Line1 , ui->Line2,
                              ui->Line3 , ui->Line4 , ui->Line5 ,
                              ui->Line6 , ui->Line7,
                              ui->Line8 , ui->Line9};

    QSlider*setAngleSliders[] = {ui->setAngleSilder0 , ui->setAngleSilder1,
                                 ui->setAngleSilder2 , ui->setAngleSilder3,
                                 ui->setAngleSilder4 , ui->setAngleSilder5,
                                 ui->setAngleSilder6 , ui->setAngleSilder7,
                                 ui->setAngleSilder8 , ui->setAngleSilder9};

    QString sndStr;
    QString Str_head,Str_ID,Str_Total_Len,Str_Operate,Str_Address,Str_WR_Len,Str_Checksum;
    unsigned char Checksum;
    QByteArray sendDataHex;
    int i;

    for(i = 0;i < NUM_RIGHT_MOTORS ;i++)
    {

        dest_angle[i] = lineEdits[i]->text().toDouble();
        desi_speed[i] = fabs ( ( dest_angle[i]- current_angle[i] ) / time );
        current_angle[i] = dest_angle[i];
    }


    Str_head = PACKHEAD;
    Str_ID = uchar2hexQString(BOARDCASTID);
    Str_Total_Len = uchar2hexQString(LEN_SndFiveANGLESPEED);
    Str_Operate = uchar2hexQString(OPERATE_SYNWR);
    Str_Address = uchar2hexQString( ADDRESS_RGSETANGLE);
    Str_WR_Len = uchar2hexQString(LEN_WRANGLESPEED);

    sndStr = Str_head + " " + Str_ID + " " + Str_Total_Len + " " + Str_Operate + " " + Str_Address + " " + Str_WR_Len;


    for(i = 0 ; i < NUM_RIGHT_MOTORS ; i++)
    {
        sndStr = sndStr + " " + CombineStr(i);
    }

    Checksum = CountChecksum(sndStr);
    Str_Checksum = uchar2hexQString(Checksum);

    sndStr=sndStr+" "+Str_Checksum;

    sendDataHex = QString2HexQByteArray(sndStr);

    ComRightLeg->write (sendDataHex);

    for(i = 0 ; i < NUM_RIGHT_MOTORS ; i++)
    {
        setAngleSliders[i]->setValue(dest_angle[i]);
    }
}

void MainWindow::send_left_leg_motors(double time)
{
    QLineEdit*lineEdits[] = { ui->Line0 , ui->Line1 , ui->Line2,
                              ui->Line3 , ui->Line4 , ui->Line5 ,
                              ui->Line6 , ui->Line7,
                              ui->Line8 , ui->Line9};

    QSlider*setAngleSliders[] = {ui->setAngleSilder0 , ui->setAngleSilder1,
                                 ui->setAngleSilder2 , ui->setAngleSilder3,
                                 ui->setAngleSilder4 , ui->setAngleSilder5,
                                 ui->setAngleSilder6 , ui->setAngleSilder7,
                                 ui->setAngleSilder8 , ui->setAngleSilder9};

    QString sndStr;
    QString Str_head,Str_ID,Str_Total_Len,Str_Operate,Str_Address,Str_WR_Len,Str_Checksum;
    unsigned char Checksum;
    QByteArray sendDataHex;
    int i;

    for(i = 5;i < 10 ;i++)
    {
        dest_angle[i] = lineEdits[i]->text().toDouble();
        desi_speed[i] = fabs ( ( dest_angle[i]- current_angle[i] ) / time );
        current_angle[i] = dest_angle[i];
    }


    Str_head = PACKHEAD;
    Str_ID = uchar2hexQString(BOARDCASTID);
    Str_Total_Len = uchar2hexQString(LEN_SndFiveANGLESPEED);
    Str_Operate = uchar2hexQString(OPERATE_SYNWR);
    Str_Address = uchar2hexQString( ADDRESS_RGSETANGLE);
    Str_WR_Len = uchar2hexQString(LEN_WRANGLESPEED);

    sndStr = Str_head + " " + Str_ID + " " + Str_Total_Len + " " + Str_Operate + " " + Str_Address + " " + Str_WR_Len;


    for(i = 5 ; i < 10 ; i++)
    {
        sndStr = sndStr + " " + CombineStr(i);
    }

    Checksum = CountChecksum(sndStr);
    Str_Checksum = uchar2hexQString(Checksum);

    sndStr=sndStr+" "+Str_Checksum;

    sendDataHex = QString2HexQByteArray(sndStr);

    ComLeftLeg->write (sendDataHex);

    for(i = 5 ; i < 10 ; i++)
    {
        setAngleSliders[i]->setValue(dest_angle[i]);
    }
}


void MainWindow::send_upper_limb_motors(double time)
{
    QLineEdit*lineEdits[] = { ui->Line0 , ui->Line1 , ui->Line2 ,
                              ui->Line3 , ui->Line4 , ui->Line5 ,
                              ui->Line6 , ui->Line7 , ui->Line8 ,
                              ui->Line9 , ui->Line10 , ui->Line11 ,
                              ui->Line12 , ui->Line13 , ui->Line14 ,
                              ui->Line15 , ui->Line16
                              };

    QSlider*setAngleSliders[] = {ui->setAngleSilder0 , ui->setAngleSilder1,
                                 ui->setAngleSilder2 , ui->setAngleSilder3,
                                 ui->setAngleSilder4 , ui->setAngleSilder5,
                                 ui->setAngleSilder6 , ui->setAngleSilder7,
                                 ui->setAngleSilder8 , ui->setAngleSilder9,
                                 ui->setAngleSilder10 , ui->setAngleSilder11,
                                 ui->setAngleSilder12 , ui->setAngleSilder13,
                                 ui->setAngleSilder14 , ui->setAngleSilder15,
                                 ui->setAngleSilder16
                                };

    QString sndStr;
    QString Str_head,Str_ID,Str_Total_Len,Str_Operate,Str_Address,Str_WR_Len,Str_Checksum;
    unsigned char Checksum;
    QByteArray sendDataHex;
    int i;

    for(i = 10;i < 17 ;i++)
    {

        dest_angle[i] = lineEdits[i]->text().toDouble();
        desi_speed[i] = fabs ( ( dest_angle[i]- current_angle[i] ) / time );
        current_angle[i] = dest_angle[i];
    }


    Str_head = PACKHEAD;
    Str_ID = uchar2hexQString(BOARDCASTID);
    Str_Total_Len = uchar2hexQString(LEN_SND_SEVEN_ANGLESPEED);
    Str_Operate = uchar2hexQString(OPERATE_SYNWR);
    Str_Address = uchar2hexQString( ADDRESS_RGSETANGLE);
    Str_WR_Len = uchar2hexQString(LEN_WRANGLESPEED);

    sndStr = Str_head + " " + Str_ID + " " + Str_Total_Len + " " + Str_Operate + " " + Str_Address + " " + Str_WR_Len;

    for(i = 10 ; i < 17 ; i++)
    {
        sndStr = sndStr + " " + CombineStr(i);
    }

    Checksum = CountChecksum(sndStr);
    Str_Checksum = uchar2hexQString(Checksum);

    sndStr=sndStr+" "+Str_Checksum;

    sendDataHex = QString2HexQByteArray(sndStr);

    ComUpperLimb->write (sendDataHex);

    for(i = 10 ; i < 17 ; i++)
    {
        setAngleSliders[i]->setValue(dest_angle[i]);
    }
}



QString MainWindow::CombineStr(unsigned char ID)
{
    QString Str_Combine;
    QString Str_ID;
    QString Str_Angle;
    QString Str_Speed;

    if(ID < 10 || ID == 11 || ID == 14)
    {
        Str_ID =  uchar2hexQString(ID);

        short R_Angle = ( dest_angle[ID] + INIT_ANGLE ) / CUSTOMANGLE_MX_64AT * CUSTOMRG_MX_64AT;
        Small2Big(R_Angle);
        Str_Angle = Short2QString(R_Angle);

        short R_Speed = Degree2RPM( desi_speed[ID]) / CUSTOMSPEED * CUSTOMRG_SPEED;
        Small2Big(R_Speed);
        Str_Speed = Short2QString(R_Speed);

        Str_Combine = Str_ID + " " + Str_Angle + " " + Str_Speed;
        return Str_Combine;
    }
    else
    {
        Str_ID =  uchar2hexQString(ID);

        short R_Angle = ( dest_angle[ID] + CUSTOMANGLE_AX_12A ) / CUSTOMANGLE_AX_12A * CUSTOMRG_AX_12A ;
        Small2Big(R_Angle);
        Str_Angle = Short2QString(R_Angle);

        short R_Speed = Degree2RPM( desi_speed[ID]) / CUSTOMSPEED_AX12  * CUSTOMRG_SPEED;
        Small2Big(R_Speed);
        Str_Speed = Short2QString(R_Speed);

        Str_Combine = Str_ID + " " + Str_Angle + " " + Str_Speed;
        return Str_Combine;
    }
}

void MainWindow::on_send_clicked()
{
    DesireDuration=ui->line_time->text().toDouble();
    send_right_leg_motors(DesireDuration);
    send_left_leg_motors(DesireDuration);
    send_upper_limb_motors(DesireDuration);
    Motor_ID_Right = 0;
    cnt = 0;
    start_time = QTime::currentTime();
  //  this->get_Motor_angle_speed(Motor_ID_Right);
}

void MainWindow::Motor_Reset()
{
    for(int i = 0 ;i < NUM_MOTORS ; i++)
    {
        this->current_angle[i] = 10;
    }
    this->current_angle[11] = -10;


    this->flag_motor_init=1;
    send_right_leg_motors(1);
    send_left_leg_motors(1);
    send_upper_limb_motors(1);
}


void MainWindow::get_Motor_angle_speed(int ID)
{
    QString sndStr;
    unsigned char checksum;
    QByteArray sendDataHex;
    QString Str_head,Str_ID,Str_Total_Len,Str_Operate,Str_Address,Str_WR_Len,Str_Checksum;

    Str_head = PACKHEAD;
    Str_ID = uchar2hexQString(ID);
    Str_Total_Len = uchar2hexQString(LEN_READANGLESPEED);
    Str_Operate = uchar2hexQString(OPERATE_READ);
    Str_Address = uchar2hexQString(ADDRESS_RGGETANGLE);
    Str_WR_Len = uchar2hexQString(LEN_READANGLESPEED);

    sndStr= Str_head + " " + Str_ID + " " + Str_Total_Len + " " + Str_Operate
            + " " + Str_Address + " " + Str_WR_Len + " ";

    checksum = CountChecksum(sndStr);
    Str_Checksum = uchar2hexQString(checksum);
    sndStr += Str_Checksum;


    sendDataHex = QString2HexQByteArray(sndStr);
    GetModel = MODGETANGLE_SPEED;

    if(ID<5)
    {
        ComRightLeg->write (sendDataHex);
    }
    else
    {
        ComLeftLeg->write (sendDataHex);
    }

}

bool MainWindow::MissionFinished()
{
    for( int i = 0; i < MotorCntRight ; i++)
    {
        if(fabs(feedback_angle[i] - dest_angle[i]) > EXP)
        {
          return false;
        }
    }
    return true;
}

bool MainWindow::MotorsQuit()
{
    for( int i = 0; i < 10 ; i++)
    {
        if(fabs(feedback_speed[i]) > FLOAT_EXP)
        {
          return false;
        }
    }
    return true;
}

void MainWindow::rightleg_feedback()
{

    temp_right += ComRightLeg->readAll();
    if(temp_right.length()%MODGETANGLE_SPEED == 0)
    {


        Motor_ID_Right++;
        if(Motor_ID_Right == MotorCntRight)
        {
            Motor_ID_Right = 0;
            cnt++;
            qDebug() << "cntRight:" <<cnt << endl;
            qDebug() << QByteArray2HexQString(temp_right) << endl;
        }


        PackFeedback_AngleSpeed Pack(temp_right);

        temp_right = "";
        dialog_display.setAngle(Pack.MotorID,Pack.FeedBackAngle);
        dialog_display.setSpeed(Pack.MotorID,Pack.FeedBackSpeed_degree);
        feedback_speed[Pack.MotorID] = Pack.FeedBackSpeed_degree;

        QFile file("Feedback_Right.txt");
        AppendData(file,QString::number(Pack.FeedBackAngle,'f',2)+QString(" "));

        if(Pack.MotorID == 4)
        {
            QFile file("Feedback_Right.txt");
            AppendData(file,QString::number(cnt,10)+QString("\n"));
        }

        if( Motor_ID_Right != 0 || MotorsQuit() == false || (- QTime::currentTime().msecsTo(start_time)) < 1000*DesireDuration)
        {
             get_Motor_angle_speed( Motor_ID_Right );
        }
        else
        {
             qDebug()<<"endtime - starttime = "<< - QTime::currentTime().msecsTo(start_time);
             this->Right_finished = 1;

        }

    }
}

void MainWindow::leftleg_feedback()
{
    temp_left += ComLeftLeg->readAll();
    if(temp_left.length()%MODGETANGLE_SPEED == 0)
    {


        Motor_ID_Left++;
        if(Motor_ID_Left == 10)
        {
            Motor_ID_Left = 5;
            cnt_left++;
            qDebug() << "cntLeft:" << cnt_left << endl;
            qDebug() << QByteArray2HexQString(temp_left) << endl;
        }


        PackFeedback_AngleSpeed Pack(temp_left);
        //qDebug() << QByteArray2HexQString(temp_right) << endl;
        //Pack.display();
        temp_left = "";
        dialog_display.setAngle(Pack.MotorID,Pack.FeedBackAngle);
        dialog_display.setSpeed(Pack.MotorID,Pack.FeedBackSpeed_degree);
        feedback_speed[Pack.MotorID] = Pack.FeedBackSpeed_degree;

        QFile file("Feedback_Left.txt");
        AppendData(file,QString::number(Pack.FeedBackAngle,'f',2)+QString(" "));

        if(Pack.MotorID == 9)
        {
            QFile file("Feedback_Left.txt");
            AppendData(file,QString::number(cnt,10)+QString("\n"));
        }


        if( Motor_ID_Left != 5 || MotorsQuit() == false || (- QTime::currentTime().msecsTo(start_time)) < 1000*DesireDuration)
        {
             get_Motor_angle_speed( Motor_ID_Left );
        }
        else
        {
             qDebug()<<"endtime - starttime = "<< - QTime::currentTime().msecsTo(start_time);
             this->Left_finished = 1;
        }

    }
}

void MainWindow::ComUpperLimb_feedback()
{

}

void MainWindow::on_ButtonChooseFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(0,"choose","","*xml");
    this->model->setRowCount(0);
    doc_load_xml(doc,filename);
    parse_xmlDoc(doc,model);
}

void MainWindow::on_SaveFile_clicked()
{
    QString  fileName  =  QFileDialog::getSaveFileName( this,"save file","",tr( "xml files (*.xml)" ) );
    save_xml(model,fileName);
}

void MainWindow::on_CleanTable_clicked()
{
    this->model->setRowCount(0);
}

void MainWindow::table_init()
{
    model =  new QStandardItemModel();
    char  colName[][10] = {"NUM"    , "Motor0" , "Motor1" , "Motor2" , "Motor3","Motor4",
                           "Motor5" , "Motor6" , "Motor7" , "Motor8" , "Motor9",
                           "Motor10", "Motor11", "Motor12", "Motor13", "Motor14",
                           "Motor15", "Motor16", "time"};

    int colCount = sizeof(colName) / sizeof(colName[0]);              /*列数*/

    int index = 0;                                               /*用于遍历*/

    model->setColumnCount(colCount);    /*设置列数*/

    while( colCount-- )
    {
        model->setHeaderData(index,Qt::Horizontal,colName[index]);         /*设置某一列的列名*/
        ui->table->setColumnWidth(index,50);                           /*设置某一列的宽度*/
        index++;
    }
    ui->table->setColumnWidth(index-1,100);                    /*设置最后一列的宽度(time)*/
    ui->table->setModel(model);

}

void MainWindow::send_row(int row)
{
    double time = model->item(row,model->columnCount()-1)->text().toDouble();
    QLineEdit*lineEdits[] = { ui->Line0 , ui->Line1 , ui->Line2 ,
                              ui->Line3 , ui->Line4 , ui->Line5 ,
                              ui->Line6 , ui->Line7 , ui->Line8 ,
                              ui->Line9 , ui->Line10 , ui->Line11 ,
                              ui->Line12 , ui->Line13 , ui->Line14 ,
                              ui->Line15 , ui->Line16
                              };
    for(int i = 1 ; i <= model->columnCount()-2;i++)
    {
        lineEdits[i-1]->setText( model->item(row,i)->text());

    }
    DesireDuration=time;
    send_right_leg_motors(time);
    send_left_leg_motors(time);
    send_upper_limb_motors(time);
}

void MainWindow::SndFeedBackRequest()
{
    Motor_ID_Right = 0;
    Motor_ID_Left = 5;
//    cnt = 0;
//    cnt_left = 0;
    start_time = QTime::currentTime();
    this->get_Motor_angle_speed(Motor_ID_Right);
    this->get_Motor_angle_speed(Motor_ID_Left);
}
void MainWindow::on_table_clicked(QModelIndex index)
{
    send_row(index.row());
    //SndFeedBackRequest();
}

void MainWindow::on_insert_clicked()
{
    QItemSelectionModel  *selections  =  ui->table->selectionModel();
    QModelIndexList       indexList   =  selections->selectedIndexes();

    int length = indexList.count();

    if(length==0&&model->rowCount())
    {
        return;
    }

    QList<QStandardItem *>  rowList;

    rowList<<new QStandardItem(QString::number(model->rowCount()+1,10));
    for(int i = 1;i <=model->columnCount() - 2; i++)
    {
        QStandardItem*Item=new QStandardItem(QString::number((int)dest_angle[i-1], 10));
        Item->setTextAlignment(Qt::AlignCenter);
        rowList << Item;
    }

    rowList << new QStandardItem("1");


    if(model->rowCount()==0)
    {
        model->insertRow(0,rowList);
    }
    else
    {
        model->insertRow(indexList.at(0).row(),rowList);
    }

    for(int i = 0; i < model->rowCount() ;i++)
    {
        model->item(i,0)->setText(QString::number(i+1,10));
    }
}

void MainWindow::on_dele_clicked()
{
    QItemSelectionModel  *selections  =  ui->table->selectionModel();
    QModelIndexList       indexList   =  selections->selectedIndexes();
    int                   length      =  indexList.count();
    if(length==0&&model->rowCount())
        return;

    if(model->rowCount()>0)
        model->removeRow(indexList.at(0).row());
    for(int i = 0; i < model->rowCount() ;i++)
    {
        model->item(i,0)->setText(QString::number(i+1,10));
    }
}

void MainWindow::on_feedback_clicked()
{
    FeedbackFlag=1-FeedbackFlag;

    if(FeedbackFlag)
    {
       dialog_display.show();
       ui->feedback->setText(tr("关闭反馈"));
    }
    else
    {
       dialog_display.hide();
       ui->feedback->setText(tr("打开反馈"));
    }
}

void MainWindow::sendMotor(int ID,double Angle)
{
    Angle=INIT_ANGLE;
    QString str="FF FF 0";
    str+=QString::number(ID,10);
    str+=" 07 03 1E ";
    int Angle_register=Angle*(CUSTOMRG_MX_64AT/CUSTOMANGLE_MX_64AT);
    int high_byte;
    int low_byte;

    low_byte=Angle_register&0x000000ff;
    char str_low_byte[20];
    itoa(low_byte,str_low_byte,16);


    high_byte=(Angle_register>>8)&0x000000ff;
    char str_high_byte[20];
    itoa(high_byte,str_high_byte,16);

    chars_to_up(str_high_byte);
    chars_to_up(str_low_byte);


    if(low_byte<16)
        str+="0";
    str+=QString(str_low_byte);

    str+=" ";

    if(high_byte<16)
        str+="0";
    str+=QString(str_high_byte);
    str+=" 00 02 ";

    int checksum=0;
    checksum=ID+07+03+(0x1E)+low_byte+high_byte+00+02;
    checksum=~(checksum);
    checksum&=0x000000ff;
    char str_checksum[20];
    itoa(checksum,str_checksum,16);
    chars_to_up(str_checksum);
    qDebug()<<str_checksum<<endl;

    if(checksum<16)
        str+="0";
    str+=QString(str_checksum);



    QByteArray sendDataHex;
    sendDataHex = QString2HexQByteArray (str);
    if(ID<5)
    this->ComRightLeg->write (sendDataHex);
    else
    this->ComLeftLeg->write(sendDataHex);
}

void MainWindow::on_setAngleSilder0_valueChanged(int value)
{
    ui->Line0->setText(QString::number(value, 10));
}



void MainWindow::on_setAngleSilder0_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    send_right_leg_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder1_valueChanged(int value)
{
    ui->Line1->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder1_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    send_right_leg_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder2_valueChanged(int value)
{
    ui->Line2->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder2_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    send_right_leg_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder3_valueChanged(int value)
{
    ui->Line3->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder3_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    send_right_leg_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder4_valueChanged(int value)
{
    ui->Line4->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder4_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    send_right_leg_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder5_valueChanged(int value)
{
    ui->Line5->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder5_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    send_left_leg_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder6_valueChanged(int value)
{
    ui->Line6->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder6_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    send_left_leg_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder7_valueChanged(int value)
{
    ui->Line7->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder7_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    send_left_leg_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder8_valueChanged(int value)
{
    ui->Line8->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder8_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    send_left_leg_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder9_valueChanged(int value)
{
    ui->Line9->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder9_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    send_left_leg_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder10_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    this->send_upper_limb_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder11_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    this->send_upper_limb_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder12_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    this->send_upper_limb_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder13_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    this->send_upper_limb_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder14_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    this->send_upper_limb_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder15_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    this->send_upper_limb_motors(DesireDuration);
}

void MainWindow::on_setAngleSilder16_sliderReleased()
{
    DesireDuration=ui->line_time->text().toDouble();
    this->send_upper_limb_motors(DesireDuration);
}

void MainWindow::timer_init()
{
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timeup()));
    timer->setInterval(100);
    timer->start();
    qDebug()<<"timer"<<endl;
}

void MainWindow::timeup()
{

    if(this->FeedbackFlag == 0)
    {
        if(TimerAddFlag)
        {
            TimerCounter++;
        }

        if(TimerCounter*100 >= DesireDuration*1000)
        {
            if(TimerContinousSndModel.IsActived())
            {
                TimerAddFlag = 1;
            }
            else
            {
                TimerAddFlag = 0;
            }

            TimerContinousSndModel.CurrentRow++;
            TimerCounter = 0;
            send_row(TimerContinousSndModel.CurrentRow);

            if(TimerContinousSndModel.CurrentRow == model->rowCount()-1)
            {
                ui->ButtonRunAll->setText("|>");
                TimerContinousSndModel.stop();
                TimerContinousSndModel.count_zero();
                ui->ButtonCountZero->setEnabled(true);
                TimerAddFlag = 0;
            }

         }
    }

    else if(this->FeedbackFlag == 1)
    {
        if((this->Left_finished&&this->Left_finished) && FeedBackSndModel.IsActived())
        {
            qDebug()<<"I can send now"<<this->Left_finished<<this->Left_finished<<endl;
            FeedBackSndModel.FeedBackSndFlag = 0;
            FeedBackSndModel.CurrentRow++;
            this->Left_finished = 0;
            this->Right_finished = 0;
            send_row(FeedBackSndModel.CurrentRow);
            SndFeedBackRequest();


            if(FeedBackSndModel.CurrentRow == model->rowCount()-1)
            {
                ui->ButtonRunAll->setText("|>");
                FeedBackSndModel.stop();
                FeedBackSndModel.count_zero();
                FeedBackSndModel.FeedBackSndFlag = 0;
                this->Left_finished = 0;
                this->Right_finished = 0;
                ui->ButtonCountZero->setEnabled(true);
            }
        }
    }

}


void MainWindow::on_ButtonRunAll_clicked()
{
    cnt = 0;
    cnt_left = 0;

    ClearFile("Feedback_Right.txt");
    ClearFile("Feedback_Left.txt");

    if(model->rowCount() == 0)
    {
        return;
    }

    if(this->FeedbackFlag == 0)
    {
        if(TimerContinousSndModel.condition==STOP_CONDITION)
        {
            ui->ButtonRunAll->setText("||");
            ui->ButtonCountZero->setEnabled(false);
            TimerContinousSndModel.active();
            TimerAddFlag = 1;

            if(TimerContinousSndModel.CurrentRow == 0)
            {
                send_row(0);
            }
        }
        else
        {
             ui->ButtonRunAll->setText("|>");
             TimerContinousSndModel.stop();
             ui->ButtonCountZero->setEnabled(true);
        }
    }
    else
    {
        if(FeedBackSndModel.condition == STOP_CONDITION)
        {
            ui->ButtonRunAll->setText("||");
            ui->ButtonCountZero->setEnabled(false);
            FeedBackSndModel.active();

            if(FeedBackSndModel.CurrentRow == 0)
            {
                this->Left_finished = 0;
                this->Right_finished = 0;
                send_row(0);
                SndFeedBackRequest();
            }
        }
        else
        {
             ui->ButtonRunAll->setText("|>");
             FeedBackSndModel.stop();
             ui->ButtonCountZero->setEnabled(true);
        }
    }


}

void MainWindow::on_ButtonCountZero_clicked()
{
    if(model->rowCount() == 0)
    {
        return;
    }

    ui->ButtonRunAll->setText("||");
    ui->ButtonCountZero->setEnabled(false);
    TimerContinousSndModel.count_zero();
    TimerContinousSndModel.active();
    TimerAddFlag = 1;
    send_row(0);

    if(this->FeedbackFlag)
    {
        FeedBackSndModel.FeedBackSndFlag = 0;
        SndFeedBackRequest();
    }
}

void MainWindow::on_ButtonAngle0Up_clicked()
{
    ui->Line0->setText(QString::number((int)dest_angle[0]+ChangeStep,10));
    send_right_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle0Down_clicked()
{
    ui->Line0->setText(QString::number((int)dest_angle[0]-ChangeStep,10));
    send_right_leg_motors(0.2);
}


void MainWindow::on_ButtonAngle1Up_clicked()
{
    ui->Line1->setText(QString::number((int)dest_angle[1]+ChangeStep,10));
    send_right_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle1Down_clicked()
{
    ui->Line1->setText(QString::number((int)dest_angle[1]-ChangeStep,10));
    send_right_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle2Up_clicked()
{
    ui->Line2->setText(QString::number((int)dest_angle[2]+ChangeStep,10));
    send_right_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle2Down_clicked()
{
    ui->Line2->setText(QString::number((int)dest_angle[2]-ChangeStep,10));
    send_right_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle3Up_clicked()
{
    ui->Line3->setText(QString::number((int)dest_angle[3]+ChangeStep,10));
    send_right_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle3Down_clicked()
{
    ui->Line3->setText(QString::number((int)dest_angle[3]-ChangeStep,10));
    send_right_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle4Up_clicked()
{
    ui->Line4->setText(QString::number((int)dest_angle[4]+ChangeStep,10));
    send_right_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle4Down_clicked()
{
    ui->Line4->setText(QString::number((int)dest_angle[4]-ChangeStep,10));
    send_right_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle5Up_clicked()
{
    ui->Line5->setText(QString::number((int)dest_angle[5]+ChangeStep,10));
    send_left_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle5Down_clicked()
{
    ui->Line5->setText(QString::number((int)dest_angle[5]-ChangeStep,10));
    send_left_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle6Up_clicked()
{
    ui->Line6->setText(QString::number((int)dest_angle[6]+ChangeStep,10));
    send_left_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle6Down_clicked()
{
    ui->Line6->setText(QString::number((int)dest_angle[6]-ChangeStep,10));
    send_left_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle7Up_clicked()
{
    ui->Line7->setText(QString::number((int)dest_angle[7]+ChangeStep,10));
    send_left_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle7Down_clicked()
{
    ui->Line7->setText(QString::number((int)dest_angle[7]-ChangeStep,10));
    send_left_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle8Up_clicked()
{
    ui->Line8->setText(QString::number((int)dest_angle[8]+ChangeStep,10));
    send_left_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle8Down_clicked()
{
    ui->Line8->setText(QString::number((int)dest_angle[8]-ChangeStep,10));
    send_left_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle9Up_clicked()
{
    ui->Line9->setText(QString::number((int)dest_angle[9]+ChangeStep,10));
    send_left_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle9Down_clicked()
{
    ui->Line9->setText(QString::number((int)dest_angle[9]-ChangeStep,10));
    send_left_leg_motors(0.2);
}

void MainWindow::on_ButtonAngle10Up_clicked()
{
    ui->Line10->setText(QString::number((int)dest_angle[10]+ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_pushButton_clicked()
{
    this->get_Motor_angle_speed(0);
}


void MainWindow::on_ButtonAngle10Down_clicked()
{
    ui->Line10->setText(QString::number((int)dest_angle[10]-ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle11Up_clicked()
{
    ui->Line11->setText(QString::number((int)dest_angle[11]+ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle11Down_clicked()
{
    ui->Line11->setText(QString::number((int)dest_angle[11]-ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle12Up_clicked()
{
    ui->Line12->setText(QString::number((int)dest_angle[12]+ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle12Down_clicked()
{
    ui->Line12->setText(QString::number((int)dest_angle[12]-ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle13Up_clicked()
{
    ui->Line13->setText(QString::number((int)dest_angle[13]+ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle13Down_clicked()
{
    ui->Line13->setText(QString::number((int)dest_angle[13]-ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle14Up_clicked()
{
    ui->Line14->setText(QString::number((int)dest_angle[14]+ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle14Down_clicked()
{
    ui->Line14->setText(QString::number((int)dest_angle[14]-ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle15Up_clicked()
{
    ui->Line15->setText(QString::number((int)dest_angle[15]+ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle15Down_clicked()
{
    ui->Line15->setText(QString::number((int)dest_angle[15]-ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle16Up_clicked()
{
    ui->Line16->setText(QString::number((int)dest_angle[16]+ChangeStep,10));
    send_upper_limb_motors(0.2);
}

void MainWindow::on_ButtonAngle16Down_clicked()
{
    ui->Line16->setText(QString::number((int)dest_angle[16]-ChangeStep,10));
    send_upper_limb_motors(0.2);
}


void MainWindow::on_setAngleSilder10_valueChanged(int value)
{
    ui->Line10->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder11_valueChanged(int value)
{
    ui->Line11->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder12_valueChanged(int value)
{
    ui->Line12->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder13_valueChanged(int value)
{
    ui->Line13->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder14_valueChanged(int value)
{
    ui->Line14->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder15_valueChanged(int value)
{
    ui->Line15->setText(QString::number(value, 10));
}

void MainWindow::on_setAngleSilder16_valueChanged(int value)
{
    ui->Line16->setText(QString::number(value, 10));
}
