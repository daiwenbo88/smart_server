#include "devicefan.h"
#include "../custom/global.h"
#include "ui_devicefan.h"

DeviceFan::DeviceFan(int room,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceFan)
{
    ui->setupUi(this);
    roomName=room;
    sliderButton=new SliderButton(this);
    sliderButton->setButtonColor(QColor(36,110,202),QColor(188,188,188),QColor(255,255,255));
    sliderButton->setBaseSize(30,40);
    sliderButton->move(170,20);
    connect(sliderButton,&SliderButton::doSwitchOff,this,&DeviceFan::doSliderOff);
    connect(sliderButton,&SliderButton::doSwitchOn,this,&DeviceFan::doSliderOn);
    //setStyleSheet("#frame{background-color:#f4fcff;border_radius:15px}");
    ui->labFan->setStyleSheet("border-image:url(:/icons/png/fan_off.png)");
    ui->labFan->setText("");
    ui->labSwitcn->setStyleSheet("color:rgb(40,40,40)");
    ui->labSwitcn->setText("OFF");
}

DeviceFan::~DeviceFan()
{
    delete ui;
}

void DeviceFan::doSliderOff()
{
    emit doSendData(socketMap.value(roomName),"<*06,101,00*>");
    ui->labFan->setStyleSheet("border-image:url(:/icons/png/fan_off.png)");
    ui->labSwitcn->setStyleSheet("color:rgb(40,40,40)");
    ui->labSwitcn->setText("OFF");
}

void DeviceFan::doSliderOn()
{
    emit doSendData(socketMap.value(roomName),"<*06,101,01*>");
    ui->labFan->setStyleSheet("border-image:url(:/icons/png/fan_on.png)");
    ui->labSwitcn->setStyleSheet("color:rgb(36,110,202)");
    ui->labSwitcn->setText("ON");
}
