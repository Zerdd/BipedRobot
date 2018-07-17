#ifndef DIALOGDISPLAY_H
#define DIALOGDISPLAY_H

#include <QDialog>
#include <QLCDNumber>
namespace Ui {
    class DialogDisplay;
}

class DialogDisplay : public QDialog {
    Q_OBJECT
public:
    DialogDisplay(QWidget *parent = 0);
    ~DialogDisplay();
    void setAngle(int ID,double Angle);
    void setSpeed(int ID,double Speed);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogDisplay *ui;
};

#endif // DIALOGDISPLAY_H
