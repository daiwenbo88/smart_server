#include "devicelamp.h"
#include "../custom/global.h"
#include "ui_devicelamp.h"

DeviceLamp::DeviceLamp(int room,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceLamp)
{
    ui->setupUi(this);
    roomName=room;
    sliderButton=new SliderButton(this);
    sliderButton->setButtonColor(QColor(36,110,202),QColor(188,188,188),QColor(255,255,255));
    sliderButton->setBaseSize(30,40);
    sliderButton->move(170,20);
    connect(sliderButton,&SliderButton::doSwitchOff,this,&DeviceLamp::doSliderOff);
    connect(sliderButton,&SliderButton::doSwitchOn,this,&DeviceLamp::doSliderOn);
    //setStyleSheet("#frame{background-color:#f4fcff;border_radius:15px}");
    ui->labLamp->setStyleSheet("border-image:url(:/icons/png/lamp_off.png)");
    ui->labLamp->setText("");
    ui->labSwitch->setStyleSheet("color:rgb(40,40,40)");
    ui->labSwitch->setText("OFF");
}

DeviceLamp::~DeviceLamp()
{
    delete ui;
}

void DeviceLamp::doSliderOff()
{
    emit doSendData(socketMap.value(roomName),"<*06,100,00*>");

    ui->labLamp->setStyleSheet("border-image:url(:/icons/png/lamp_off.png)");
    ui->labSwitch->setStyleSheet("color:rgb(40,40,40)");
    ui->labSwitch->setText("ON");
}

void DeviceLamp::doSliderOn()
{
    emit doSendData(socketMap.value(roomName),"<*06,100,01*>");

    ui->labLamp->setStyleSheet("border-image:url(:/icons/png/lamp_on.png)");
    ui->labSwitch->setStyleSheet("color:rgb(36,110,202)");
    ui->labSwitch->setText("OFF");
}
