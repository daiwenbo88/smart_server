#ifndef DEVICECURTAIN_H
#define DEVICECURTAIN_H

#include "../custom/sliderbutton.h"
#include <QPropertyAnimation>
#include <QWidget>

namespace Ui {
class DeviceCurtain;
}

class DeviceCurtain : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceCurtain(int room,QWidget *parent = nullptr);
    ~DeviceCurtain();
    SliderButton *sliderButton;
    QPropertyAnimation *animationUp;
    QPropertyAnimation *animationDown;
    QTimer *dataTimer;
    int roomName;
private:
    Ui::DeviceCurtain *ui;
private slots:
    void doSliderOff();
    void doSliderOn();
    void doDataChanged();
    void on_btnDown_pressed();
    void on_btnDown_released();
    void on_btnUp_pressed();
    void on_btnUp_released();

signals:
    void doSendData(int sockId,QString sendData);
};


#endif // DEVICECURTAIN_H
