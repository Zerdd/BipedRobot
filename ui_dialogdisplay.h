/********************************************************************************
** Form generated from reading UI file 'dialogdisplay.ui'
**
** Created: Fri Jul 6 20:27:40 2018
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDISPLAY_H
#define UI_DIALOGDISPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DialogDisplay
{
public:
    QLabel *label;
    QLCDNumber *angle0;
    QLabel *label_2;
    QLCDNumber *speed0;
    QLCDNumber *speed1;
    QLCDNumber *angle1;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLCDNumber *angle2;
    QLabel *label_6;
    QLCDNumber *speed2;
    QLabel *label_7;
    QLabel *label_8;
    QLCDNumber *speed3;
    QLCDNumber *angle3;
    QLabel *label_9;
    QLCDNumber *angle4;
    QLabel *label_10;
    QLCDNumber *speed4;
    QLCDNumber *speed9;
    QLCDNumber *angle9;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLCDNumber *angle6;
    QLabel *label_16;
    QLabel *label_17;
    QLCDNumber *angle8;
    QLCDNumber *angle7;
    QLCDNumber *speed8;
    QLabel *label_18;
    QLCDNumber *angle5;
    QLabel *label_19;
    QLCDNumber *speed5;
    QLCDNumber *speed6;
    QLabel *label_20;
    QLCDNumber *speed7;

    void setupUi(QDialog *DialogDisplay)
    {
        if (DialogDisplay->objectName().isEmpty())
            DialogDisplay->setObjectName(QString::fromUtf8("DialogDisplay"));
        DialogDisplay->resize(1202, 754);
        label = new QLabel(DialogDisplay);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 201, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \345\256\213\344\275\223 Std L"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        angle0 = new QLCDNumber(DialogDisplay);
        angle0->setObjectName(QString::fromUtf8("angle0"));
        angle0->setGeometry(QRect(250, 10, 231, 51));
        angle0->setNumDigits(6);
        label_2 = new QLabel(DialogDisplay);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(530, 10, 121, 51));
        label_2->setFont(font);
        speed0 = new QLCDNumber(DialogDisplay);
        speed0->setObjectName(QString::fromUtf8("speed0"));
        speed0->setGeometry(QRect(610, 10, 231, 51));
        speed0->setNumDigits(6);
        speed1 = new QLCDNumber(DialogDisplay);
        speed1->setObjectName(QString::fromUtf8("speed1"));
        speed1->setGeometry(QRect(610, 70, 231, 51));
        speed1->setNumDigits(6);
        angle1 = new QLCDNumber(DialogDisplay);
        angle1->setObjectName(QString::fromUtf8("angle1"));
        angle1->setGeometry(QRect(250, 70, 231, 51));
        angle1->setNumDigits(6);
        label_3 = new QLabel(DialogDisplay);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 70, 201, 51));
        label_3->setFont(font);
        label_4 = new QLabel(DialogDisplay);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(530, 70, 121, 51));
        label_4->setFont(font);
        label_5 = new QLabel(DialogDisplay);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(530, 130, 121, 51));
        label_5->setFont(font);
        angle2 = new QLCDNumber(DialogDisplay);
        angle2->setObjectName(QString::fromUtf8("angle2"));
        angle2->setGeometry(QRect(250, 130, 231, 51));
        angle2->setNumDigits(6);
        label_6 = new QLabel(DialogDisplay);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 130, 201, 51));
        label_6->setFont(font);
        speed2 = new QLCDNumber(DialogDisplay);
        speed2->setObjectName(QString::fromUtf8("speed2"));
        speed2->setGeometry(QRect(610, 130, 231, 51));
        speed2->setNumDigits(6);
        label_7 = new QLabel(DialogDisplay);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 190, 201, 51));
        label_7->setFont(font);
        label_8 = new QLabel(DialogDisplay);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(530, 190, 121, 51));
        label_8->setFont(font);
        speed3 = new QLCDNumber(DialogDisplay);
        speed3->setObjectName(QString::fromUtf8("speed3"));
        speed3->setGeometry(QRect(610, 190, 231, 51));
        speed3->setNumDigits(6);
        angle3 = new QLCDNumber(DialogDisplay);
        angle3->setObjectName(QString::fromUtf8("angle3"));
        angle3->setGeometry(QRect(250, 190, 231, 51));
        angle3->setNumDigits(6);
        label_9 = new QLabel(DialogDisplay);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(530, 250, 121, 51));
        label_9->setFont(font);
        angle4 = new QLCDNumber(DialogDisplay);
        angle4->setObjectName(QString::fromUtf8("angle4"));
        angle4->setGeometry(QRect(250, 250, 231, 51));
        angle4->setNumDigits(6);
        label_10 = new QLabel(DialogDisplay);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 250, 201, 51));
        label_10->setFont(font);
        speed4 = new QLCDNumber(DialogDisplay);
        speed4->setObjectName(QString::fromUtf8("speed4"));
        speed4->setGeometry(QRect(610, 250, 231, 51));
        speed4->setNumDigits(6);
        speed9 = new QLCDNumber(DialogDisplay);
        speed9->setObjectName(QString::fromUtf8("speed9"));
        speed9->setGeometry(QRect(610, 630, 231, 51));
        speed9->setNumDigits(6);
        angle9 = new QLCDNumber(DialogDisplay);
        angle9->setObjectName(QString::fromUtf8("angle9"));
        angle9->setGeometry(QRect(250, 630, 231, 51));
        angle9->setNumDigits(6);
        label_11 = new QLabel(DialogDisplay);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(530, 390, 121, 51));
        label_11->setFont(font);
        label_12 = new QLabel(DialogDisplay);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 390, 201, 51));
        label_12->setFont(font);
        label_13 = new QLabel(DialogDisplay);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(530, 630, 121, 51));
        label_13->setFont(font);
        label_14 = new QLabel(DialogDisplay);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 510, 201, 51));
        label_14->setFont(font);
        label_15 = new QLabel(DialogDisplay);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(20, 630, 201, 51));
        label_15->setFont(font);
        angle6 = new QLCDNumber(DialogDisplay);
        angle6->setObjectName(QString::fromUtf8("angle6"));
        angle6->setGeometry(QRect(250, 450, 231, 51));
        angle6->setNumDigits(6);
        label_16 = new QLabel(DialogDisplay);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(20, 450, 201, 51));
        label_16->setFont(font);
        label_17 = new QLabel(DialogDisplay);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(530, 570, 121, 51));
        label_17->setFont(font);
        angle8 = new QLCDNumber(DialogDisplay);
        angle8->setObjectName(QString::fromUtf8("angle8"));
        angle8->setGeometry(QRect(250, 570, 231, 51));
        angle8->setNumDigits(6);
        angle7 = new QLCDNumber(DialogDisplay);
        angle7->setObjectName(QString::fromUtf8("angle7"));
        angle7->setGeometry(QRect(250, 510, 231, 51));
        angle7->setNumDigits(6);
        speed8 = new QLCDNumber(DialogDisplay);
        speed8->setObjectName(QString::fromUtf8("speed8"));
        speed8->setGeometry(QRect(610, 570, 231, 51));
        speed8->setNumDigits(6);
        label_18 = new QLabel(DialogDisplay);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(530, 510, 121, 51));
        label_18->setFont(font);
        angle5 = new QLCDNumber(DialogDisplay);
        angle5->setObjectName(QString::fromUtf8("angle5"));
        angle5->setGeometry(QRect(250, 390, 231, 51));
        angle5->setNumDigits(6);
        label_19 = new QLabel(DialogDisplay);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(20, 570, 201, 51));
        label_19->setFont(font);
        speed5 = new QLCDNumber(DialogDisplay);
        speed5->setObjectName(QString::fromUtf8("speed5"));
        speed5->setGeometry(QRect(610, 390, 231, 51));
        speed5->setNumDigits(6);
        speed6 = new QLCDNumber(DialogDisplay);
        speed6->setObjectName(QString::fromUtf8("speed6"));
        speed6->setGeometry(QRect(610, 450, 231, 51));
        speed6->setNumDigits(6);
        label_20 = new QLabel(DialogDisplay);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(530, 450, 121, 51));
        label_20->setFont(font);
        speed7 = new QLCDNumber(DialogDisplay);
        speed7->setObjectName(QString::fromUtf8("speed7"));
        speed7->setGeometry(QRect(610, 510, 231, 51));
        speed7->setNumDigits(6);

        retranslateUi(DialogDisplay);

        QMetaObject::connectSlotsByName(DialogDisplay);
    } // setupUi

    void retranslateUi(QDialog *DialogDisplay)
    {
        DialogDisplay->setWindowTitle(QApplication::translate("DialogDisplay", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogDisplay", "Motor0     Angle:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogDisplay", "Speed:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DialogDisplay", "Motor1     Angle:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("DialogDisplay", "Speed:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("DialogDisplay", "Speed:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("DialogDisplay", "Motor2     Angle:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("DialogDisplay", "Motor3     Angle:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("DialogDisplay", "Speed:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("DialogDisplay", "Speed:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("DialogDisplay", "Motor4     Angle:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("DialogDisplay", "Speed:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("DialogDisplay", "Motor5     Angle:", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("DialogDisplay", "Speed:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("DialogDisplay", "Motor7     Angle:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("DialogDisplay", "Motor9     Angle:", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("DialogDisplay", "Motor6     Angle:", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("DialogDisplay", "Speed:", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("DialogDisplay", "Speed:", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("DialogDisplay", "Motor8     Angle:", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("DialogDisplay", "Speed:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogDisplay: public Ui_DialogDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDISPLAY_H
