#include"FileOperate.h"
void ClearFile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadWrite| QIODevice::Text | QIODevice::Truncate);
    file.close();
}
void RecordData(QFile&file,int cnt,double data)
{
    QTextStream out(&file);
    file.open(QIODevice::ReadWrite| QIODevice::Text |QIODevice::Append);
    out<<cnt<<' '<<data<<endl;
    file.close();
}

void AppendData(QFile&file,QString s)
{
    QTextStream out(&file);
    file.open(QIODevice::ReadWrite| QIODevice::Text |QIODevice::Append);
    out << s ;
    file.close();
}
