#ifndef DEVICELAMP_H
#define DEVICELAMP_H

#include "../custom/sliderbutton.h"
#include <QWidget>

namespace Ui {
class DeviceLamp;
}

class DeviceLamp : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceLamp(int room,QWidget *parent = nullptr);
    ~DeviceLamp();
    SliderButton * sliderButton;
    int roomName;
private:
    Ui::DeviceLamp *ui;
public slots:
    void doSliderOff();
    void doSliderOn();
signals:
    void doSendData(int sockId,QString sendData);
};

#endif // DEVICELAMP_H
