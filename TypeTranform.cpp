#include"TypeTransform.h"
char ConvertHexChar(char ch)
{
       if((ch >= '0') && (ch <= '9'))
           return ch-0x30;
       else if((ch >= 'A') && (ch <= 'F'))
           return ch-'A'+10;
       else if((ch >= 'a') && (ch <= 'f'))
           return ch-'a'+10;
       else return (-1);
}
QByteArray QString2HexQByteArray(QString str)
{
       QByteArray senddata;
       int hexdata,lowhexdata;
       int hexdatalen = 0;
       int len = str.length();
       senddata.resize(len/2);
       char lstr,hstr;
       for(int i=0; i<len; )
       {
           hstr=str[i].toAscii();
           if(hstr == ' ')
           {
               i++;
               continue;
           }
           i++;
           if(i >= len)
               break;
           lstr = str[i].toAscii();
           hexdata = ConvertHexChar(hstr);
           lowhexdata = ConvertHexChar(lstr);
           if((hexdata == 16) || (lowhexdata == 16))
               break;
           else
               hexdata = hexdata*16+lowhexdata;
           i++;
           senddata[hexdatalen] = (char)hexdata;
           hexdatalen++;
       }
       senddata.resize(hexdatalen);
       return senddata;
}
QString QByteArray2HexQString(QByteArray temp)
{
    QString showStr;
    int len;
    len = temp.size ();
    for (int i=0;i<=len-1;i++)
    {
        char s[20];
        sprintf(s,"%02X",(unsigned char)temp[i]);
        showStr = showStr + QString(s) + " ";
    }
  //  showStr = showStr + QString::number ((unsigned char)temp[len-1],16) + "\n";
    return showStr;
}


void TwoBytesbreak(short twobyte,unsigned char&low_byte,unsigned char&high_byte)
{
    low_byte=twobyte&0x00ff;
    high_byte=(twobyte>>8)&0x00ff;
}


QString Short2QString(short registerValue)
{
    QString str;
    char str_low_byte[CHARSIZE];
    char str_high_byte[CHARSIZE];
    unsigned char low_byte=registerValue&0x00ff;
    unsigned char high_byte=((registerValue>>8)&0x00ff);
   // TwoBytesbreak(registerValue,low_byte,high_byte);
    sprintf(str_low_byte ,"%02X",low_byte);
    sprintf(str_high_byte,"%02X",high_byte);
    str=QString(str_high_byte)+" "+QString(str_low_byte);
    return str;
}
void Small2Big(short&data)
{
    unsigned char low_byte;
    unsigned char high_byte;
    low_byte=data&0xff;
    high_byte=(data>>8)&0xff;
    data=(low_byte<<8)|high_byte;
}


QString uchar2hexQString(unsigned char data)
{
    char str_data[CHARSIZE];
    sprintf(str_data,"%02X",data);
    return QString(str_data);
}

unsigned char CountChecksum(QString str)
{
    QByteArray temp=QString2HexQByteArray(str);
    char checksum=0;
    int i;
    for(i=2;i<temp.length();i++)
    {
        checksum+=(unsigned char)temp[i];
    }
    return ~checksum;
}

double Degree2RPM(double degree)
{
    return degree / 6.0;
}

double RPM2Degree(double RPM)
{
    return RPM*6.0;
}

void Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void chars_to_up(char s[])
{
    for(int i = 0 ; s[i];i++)
    {
        if(s[i] >= 'a' && s[i] <= 'z')
        {
            s[i]-=32;
        }
    }
}

short Extract2RGValue(QByteArray temp,int Index_LowByte,int Index_HighByte)
{
    int  RG_Value;
    char highByte_str[CHARSIZE];
    char lowByte_str[CHARSIZE];
    sprintf(lowByte_str,"%02X",(unsigned char)temp[Index_LowByte]);
    sprintf(highByte_str, "%02X",(unsigned char)temp[Index_HighByte]);
    QString TempStr=QString(highByte_str)+QString(lowByte_str);
    sscanf(TempStr.toAscii(),"%X",&RG_Value);
    return RG_Value;
}
