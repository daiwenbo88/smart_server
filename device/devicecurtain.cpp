#include "devicecurtain.h"
#include "../custom/global.h"
#include "ui_devicecurtain.h"

DeviceCurtain::DeviceCurtain(int room,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceCurtain)
{
    ui->setupUi(this);
    roomName=room;
    sliderButton=new SliderButton(this);
    sliderButton->setButtonColor(QColor(36,110,202),QColor(188,188,188),QColor(255,255,255));
    sliderButton->setBaseSize(30,40);
    sliderButton->move(230,20);
    connect(sliderButton,&SliderButton::doSwitchOff,this,&DeviceCurtain::doSliderOff);
    connect(sliderButton,&SliderButton::doSwitchOn,this,&DeviceCurtain::doSliderOn);
    //setStyleSheet("#frame{background-color:#f4fcff;border_radius:15px}");
   //ui->lab->setStyleSheet("border-image:url(:/icons/png/fan_off.png)");
   //ui->labFan->setText("");
    ui->labCurtain->setFixedSize(ui->widget_pic->size());
    ui->labCurtain->move(0,0);

    animationUp=new QPropertyAnimation(ui->labCurtain,"pos");
    animationDown=new QPropertyAnimation(ui->labCurtain,"pos");
    dataTimer= new QTimer(this);
    connect(dataTimer,&QTimer::timeout,this,&DeviceCurtain::doDataChanged);

    ui->labCurtain->setStyleSheet("border-image:url(:/icons/png/louvers_leaf_off.png)");
    ui->labCurtain->setText("");

    ui->labelLan->setFixedHeight(15);
    ui->labelLan->setStyleSheet("border-image:url(:/icons/png/louvers_fence_off.png)");
    ui->labelLan->setText("");

    ui->btnUp->setStyleSheet("border-image:url(:/icons/png/up_off.png)");
    ui->btnDown->setStyleSheet("border-image:url(:/icons/png/down_off.png)");
    ui->labSwitch->setStyleSheet("color:rgb(40,40,40)");
    ui->labSwitch->setText("OFF");

}

DeviceCurtain::~DeviceCurtain()
{
    delete ui;
}

void DeviceCurtain::doSliderOff()
{
    emit doSendData(socketMap.value(roomName),"<*06,106,00*>");
    ui->labCurtain->setStyleSheet("border-image:url(:/icons/png/louvers_leaf_off.png)");
    ui->labelLan->setStyleSheet("border-image:url(:/icons/png/louvers_fence_off.png)");
    ui->btnUp->setStyleSheet("border-image:url(:/icons/png/up_off.png)");
    ui->btnDown->setStyleSheet("border-image:url(:/icons/png/down_off.png)");
    ui->labSwitch->setStyleSheet("color:rgb(40,40,40)");
    ui->labSwitch->setText("OFF");
}

void DeviceCurtain::doSliderOn()
{
    emit doSendData(socketMap.value(roomName),"<*06,106,01*>");
    ui->labCurtain->setStyleSheet("border-image:url(:/icons/png/louvers_leaf_on.png)");
    ui->labelLan->setStyleSheet("border-image:url(:/icons/png/louvers_fence_on.png)");
    ui->btnUp->setStyleSheet("border-image:url(:/icons/png/up_on.png)");
    ui->btnDown->setStyleSheet("border-image:url(:/icons/png/down_on.png)");
    ui->labSwitch->setStyleSheet("color:rgb(36,110,202)");
    ui->labSwitch->setText("NO");
}

void DeviceCurtain::doDataChanged()
{
  int scale=abs(ui->labCurtain->pos().y())*1.0/ui->labCurtain->height()*100;
  qDebug()<<"startY="+QString::number(ui->labCurtain->pos().y())+"height="+QString::number(ui->labCurtain->height());
  ui->lblData->setText(QString::number(scale)+"%");
}


void DeviceCurtain::on_btnDown_pressed()
{
    int startX=ui->labCurtain->pos().x();
    int startY=ui->labCurtain->pos().y();
    //qDebug()<<"startY="+startY;
    int endX=ui->labCurtain->pos().x();
    int endY=0;
    int runTime=abs(startY)/5.0*200;

    animationUp->setStartValue(QPoint(startX,startY));
    animationUp->setEndValue(QPoint(endX,endY));
    animationUp->setDuration(runTime);
    animationUp->start();

    dataTimer->start(100);
}


void DeviceCurtain::on_btnDown_released()
{
    animationUp->stop();
    dataTimer->stop();
    QString data=ui->lblData->text().replace("%","");
    qDebug()<<"data="+data;
    QString sendData="<*06,107,"+data+"*>";
    emit doSendData(socketMap.value(roomName),sendData);
}


void DeviceCurtain::on_btnUp_pressed()
{
  int startX=ui->labCurtain->pos().x();
  int startY=ui->labCurtain->pos().y();
  int endX=ui->labCurtain->pos().x();
  int endY=0-ui->labCurtain->height();
  int runTime=(ui->labCurtain->height()-abs(ui->labCurtain->pos().y()))/5.0*200;

  animationUp->setStartValue(QPoint(startX,startY));
  animationUp->setEndValue(QPoint(endX,endY));
  animationUp->setDuration(runTime);
  animationUp->start();

  dataTimer->start(100);

}


void DeviceCurtain::on_btnUp_released()
{
  animationUp->stop();
  dataTimer->stop();
  QString data=ui->lblData->text().replace("%","");
  qDebug()<<"data="+data;
  QString sendData="<*06,107,"+data+"*>";
  emit doSendData(socketMap.value(roomName),sendData);
}

