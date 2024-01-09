#ifndef DEVICEFAN_H
#define DEVICEFAN_H

#include <QWidget>
#include "../custom/sliderbutton.h"
namespace Ui {
class DeviceFan;
}

class DeviceFan : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceFan(int room,QWidget *parent = nullptr);
    ~DeviceFan() override;
    SliderButton * sliderButton;
    int roomName;
private:
    Ui::DeviceFan *ui;
  public slots:
    void doSliderOff();
    void doSliderOn();
signals:
    void doSendData(int sockId,QString sendData);
};

#endif // DEVICEFAN_H
