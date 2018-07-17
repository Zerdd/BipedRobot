#include "dialogdisplay.h"
#include "ui_dialogdisplay.h"

DialogDisplay::DialogDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDisplay)
{
    ui->setupUi(this);
}

DialogDisplay::~DialogDisplay()
{
    delete ui;
}

void DialogDisplay::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DialogDisplay::setAngle(int ID,double Angle)
{
    QLCDNumber*LcdAngle[] = { ui->angle0 , ui->angle1 ,ui->angle2,
                             ui->angle3 , ui->angle4 , ui->angle5,
                             ui->angle6 , ui->angle7 , ui->angle8,
                             ui->angle9};
    LcdAngle[ID]->display(Angle);

}

void DialogDisplay::setSpeed(int ID,double Speed)
{
    QLCDNumber*LcdSpeed[] = { ui->speed0 , ui->speed1 , ui->speed2,
                              ui->speed3 , ui->speed4 , ui->speed5,
                              ui->speed6 , ui->speed7 , ui->speed8,
                              ui->speed9};
    LcdSpeed[ID]->display(Speed);
}

