#ifndef FILEOPERATE_H
#define FILEOPERATE_H
#include<QFile>
#include<QString>
#include<QTextStream>
void ClearFile(QString filename);
void RecordData(QFile&file,int cnt,double data);
void AppendData(QFile&file,QString s);
#endif // FILEOPERATE_H
