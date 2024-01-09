#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "custom/global.h"
#include "device/devicelamp.h"
#include "device/devicefan.h"
#include "device/deviceac.h"
#include "device/devicecurtain.h"

#include <QPalette>
#include <QTime>
#include <QPixmap>
#include <QPainter>
#include <QImageReader>


QPixmap MainWindow::pixmapToRound(const QPixmap &src, int radius)
{
  if (src.isNull()) {
    return QPixmap();
  }
  QSize size(2*radius, 2*radius);
  QBitmap mask(size);
  QPainter painter(&mask);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
  painter.setBrush(QColor(0, 0, 0));
  painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);
  QPixmap image = src.scaled(size);
  image.setMask(mask);
  return image;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpServer=new TcpServer(this);
    tcpServer->listen(QHostAddress::Any,6666);//开始监听

    timer =new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::timeout);
    timer->start(1000);

    deviceAc=new DeviceAC(LIVINGROOM,this);
    deviceAc->setStyleSheet("background-color: #f4fcff;"\
                             "border-radius: 15px");
    deviceAc->move(660,220);
    connect(deviceAc,&DeviceAC::doSendData,tcpServer,&TcpServer::deviceSendData);
    //
    deviceFan=new DeviceFan(LIVINGROOM,this);
    deviceFan->setStyleSheet("background-color: #f4fcff;"\
                             "border-radius: 15px");
    deviceFan->move(330,530);
    connect(deviceFan,&DeviceFan::doSendData,tcpServer,&TcpServer::deviceSendData);

    deviceLamp=new DeviceLamp(LIVINGROOM,this);
    deviceLamp->setStyleSheet("background-color: #f4fcff;border-radius: 15px");
    deviceLamp->move(330,220);
    connect(deviceLamp,&DeviceLamp::doSendData,tcpServer,&TcpServer::deviceSendData);
    //
    deviceCurtain=new DeviceCurtain(LIVINGROOM,this);
    deviceCurtain->setStyleSheet("background-color: #f4fcff;border-radius: 15px");
    deviceCurtain->move(1050,220);
    connect(deviceCurtain,&DeviceCurtain::doSendData,tcpServer,&TcpServer::deviceSendData);




    QPalette pal=this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/icons/png/background")));
    setPalette(pal);


    //ui->label_headpic->setStyleSheet("border-image:url(:/icons/png/header.png)");;
    ui->label_headpic->setText("");

    ui->frame_left->setStyleSheet("#frame_left{background-color:rgba(0,0,0,70%);}");
    ui->label_keting->setStyleSheet("color:#ffffff");
    ui->label_time_1->setStyleSheet("color:#ffffff");
    ui->label_time_2->setStyleSheet("color:#ffffff");
    ui->label_status->setStyleSheet("color:#ffffff");

    ui->label_fenge->setFixedWidth(3);
    ui->label_fenge->setText("");
    ui->label_fenge->setStyleSheet("background-color:#ffffff");
    //ui->label_info->setStyleSheet("color:rgba(225,225,225,200)");
    ui->label_time_1->setText(QTime::currentTime().toString("hh:mm"));
    ui->label_time_2->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));

    QPixmap header(":/icons/png/header2.png");
    QPixmap pixMap= header.scaled(ui->label_headpic->width(),ui->label_headpic->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //50为圆形的半径
    pixMap =  pixmapToRound(pixMap, 50);
    ui->label_headpic->setPixmap(pixMap);
}



void MainWindow::timeout()
{
    ui->label_time_1->setText(QTime::currentTime().toString("hh:mm"));
    ui->label_time_2->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    if(livingRoomStatus==CONNECT){
      ui->label_status->setText("状态:在线");
    }else{
      ui->label_status->setText("状态:离线");
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

