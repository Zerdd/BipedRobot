#include "xmlParse.h"

void doc_load_xml(QDomDocument&doc,QString filename)
{
    if(filename.length() == 0)
    {
        return;
    }
    
    QFile file(filename);

    if(!file.open(QIODevice::ReadWrite))
    {
        return;
    }

    if(!doc.setContent(&file))
    {
        file.close();
        return ;
    }

    file.close();
}

void parse_xmlDoc(QDomDocument doc,QStandardItemModel*&model)
{
     QDomElement element=doc.documentElement();
     //qDebug()<<element.tagName()+".\n";
     QDomNode node=element.firstChild();
     QList<QStandardItem *>rowList;

     while(node.isNull()==false)
     {
         if(node.isElement())
         {
             QDomElement e=node.toElement();
             // qDebug() << e.tagName() + ".\n";
             QDomNodeList list=e.childNodes();

             for(int i=0; i<list.count(); i++)
             {
                 QDomNode Node = list.at(i);
                 if(Node.isElement())
                 {
                     //qDebug() << Node.toElement().tagName()<<".\n"<<Node.toElement().text()<<"\n";
                     QStringList lst = Node.toElement().text().split(' ');
                     
                       for(int j=0;j<lst.length();j++)
                       {
                         QStandardItem*Item=new QStandardItem(lst.at(j));
                         Item->setTextAlignment(Qt::AlignCenter);
                         rowList << Item;
                       }
                 }
             }

             model->appendRow(rowList);
             rowList.clear();
             qDebug() << "\n";
         }
         node=node.nextSibling();
     }
}

void save_xml(QStandardItemModel *model,QString fileName)
{
    if(fileName.length() == 0)
    {
        return;
    }

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file.write("<Root>\n");

    for( int i = 0; i < model->rowCount() ; i++)
    {
        file.write("  <Action>\n");

        file.write("    <Num>");
        file.write(model->item(i,0)->text().toAscii());
        file.write("</Num>\n");

        file.write("    <DestAngle>");
        QString StrDestAngle;
        for(int j=1;j<model->columnCount()-1;j++)
        {
            StrDestAngle += model->item(i,j)->text();
            if(j != model->columnCount()-2)
                StrDestAngle += " ";
        }
        file.write(StrDestAngle.toAscii());
        file.write("</DestAngle>\n");

        file.write("    <Duration>");
        file.write(model->item(i,model->columnCount()-1)->text().toAscii());
        file.write("</Duration>\n");

        file.write("  </Action>\n\n");
    }

    file.write("</Root>");
    file.close();
}
