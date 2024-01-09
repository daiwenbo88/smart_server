#ifndef DEVICEAC_H
#define DEVICEAC_H

#include "../custom/digitalscroller.h"
#include "../custom/sliderbutton.h"
#include <QWidget>

namespace Ui {
class DeviceAC;
}

class DeviceAC : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceAC(int room,QWidget *parent = nullptr);
    ~DeviceAC();
    SliderButton *sliderButton;
    DigitalScroller *digitalScroller;
    int roomName;
private slots:
    void doSliderOff();
    void doSliderOn();
    void doValueChange(int);
    void doButtonClick();
signals:
    void doSendData(int sockId,QString sendData);

private:
    Ui::DeviceAC *ui;
};

#endif // DEVICEAC_H
