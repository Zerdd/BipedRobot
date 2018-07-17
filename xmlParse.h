#ifndef XMLPARSE_H
#define XMLPARSE_H
#include <QDomDocument>
#include <QDomComment>
#include <QDomNode>
#include <QDomNodeList>
#include <QFile>
#include <QDebug>
#include <QStandardItem>
#include <QFileDialog>
void doc_load_xml(QDomDocument&doc,QString filename);
void parse_xmlDoc(QDomDocument doc,QStandardItemModel*&model);
void save_xml(QStandardItemModel *model,QString fileName);
#endif // XMLPARSE_H
