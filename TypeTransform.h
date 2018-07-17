#include<QString>
#include<QByteArray>
#include<QTime>
#include<QCoreApplication>
#include<QEventLoop>
#include<QDebug>
#include<stdio.h>
#include<math.h>

#define INIT_ANGLE 180
#define NUM_MOTORS        17
#define NUM_RIGHT_MOTORS  5
#define NUM_LEFT_MOTORS  5
#define EXP 0.5
#define FLOAT_EXP 1e-6

#define CUSTOMRG_MX_64AT      2048.0
#define CUSTOMRG_MX_28        2048.0
#define CUSTOMRG_AX_12A       512.0

#define CUSTOMANGLE_MX_64AT   180
#define CUSTOMANGLE_MX_28     180
#define CUSTOMANGLE_AX_12A    150

#define CUSTOMRG_SPEED        512.0   //默认的角速度时寄存器的值
#define CUSTOMSPEED           58         //默认角速度为58RPM
#define CUSTOMSPEED_AX12      57

#define MODSNDANGLE           6
#define MODGETANGLE           8
#define MODGETANGLE_SPEED     10


#define OPERATE_READ          0x02
#define OPERATE_WRITE         0x03
#define OPERATE_SYNWR         0x83

#define PACKHEAD             "FF FF"


#define LEN_SetANGLESPEED     0x07
#define LEN_READANGLESPEED    0x04
#define LEN_WRANGLESPEED      0x04
#define LEN_SndFiveANGLESPEED 0x1D
#define LEN_SND_SEVEN_ANGLESPEED 0X27

#define ADDRESS_RGSETANGLE    0x1E
#define ADDRESS_RGGETANGLE    0x24


#define BOARDCASTID           0xFE


#define CHARSIZE 20


#define INDEX_ANGLELOWBYTE    5
#define INDEX_ANGLEHIGHBYTE   6
#define INDEX_SPEEDLOWBYTE    7
#define INDEX_SPEEDHIGHBYTE   8

char ConvertHexChar(char ch);
QByteArray QString2HexQByteArray(QString str);
QString QByteArray2HexQString(QByteArray temp);
void TwoBytesbreak(short twobyte,unsigned char&LOWBYTE,unsigned char&HIGHBYTE);
QString Short2QString(short registerValue);
void Small2Big(short&data);
QString uchar2hexQString(unsigned char data);
unsigned char CountChecksum(QString str);
double Degree2RPM(double degree);
double RPM2Degree(double RPM);
void Delay_MSec(unsigned int msec);
void chars_to_up(char s[]);
short Extract2RGValue(QByteArray temp,int Index_LowByte,int Index_HighByte);
