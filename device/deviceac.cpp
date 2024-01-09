#include "deviceac.h"
#include "../custom/global.h"
#include "ui_deviceac.h"

DeviceAC::DeviceAC(int room,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceAC)
{
    ui->setupUi(this);
    roomName=room;
    digitalScroller=new DigitalScroller(this);
    connect(digitalScroller,&DigitalScroller::currentValueChanged,this,&DeviceAC::doValueChange);
    digitalScroller->move(275,100);
    digitalScroller->hide();

    sliderButton=new SliderButton(this);
    sliderButton->setButtonColor(QColor(36,110,202),QColor(188,188,188),QColor(255,255,255));
    sliderButton->setBaseSize(30,40);
    sliderButton->move(230,20);
    connect(sliderButton,&SliderButton::doSwitchOff,this,&DeviceAC::doSliderOff);
    connect(sliderButton,&SliderButton::doSwitchOn,this,&DeviceAC::doSliderOn);
    //setStyleSheet("#frame{background-color:#f4fcff;border_radius:15px}");

    connect(ui->btn_mode,&QPushButton::clicked,this,&DeviceAC::doButtonClick);
    connect(ui->btn_wind,&QPushButton::clicked,this,&DeviceAC::doButtonClick);
    connect(ui->btn_auto,&QPushButton::clicked,this,&DeviceAC::doButtonClick);
    connect(ui->btn_high,&QPushButton::clicked,this,&DeviceAC::doButtonClick);
    connect(ui->btn_low,&QPushButton::clicked,this,&DeviceAC::doButtonClick);
    connect(ui->btn_mid,&QPushButton::clicked,this,&DeviceAC::doButtonClick);
    connect(ui->btn_speed,&QPushButton::clicked,this,&DeviceAC::doButtonClick);
    connect(ui->btn_cold,&QPushButton::clicked,this,&DeviceAC::doButtonClick);
    connect(ui->btn_dry,&QPushButton::clicked,this,&DeviceAC::doButtonClick);
    connect(ui->btn_xiao,&QPushButton::clicked,this,&DeviceAC::doButtonClick);
    ui->label_ac->setStyleSheet("border-image:url(:/icons/png/ac_off.png)");
    ui->label_ac->setText("");

    ui->label_fenge->setFixedHeight(2);
    ui->label_fenge->setStyleSheet("border-image:url(:/icons/png/ac_line_off.png)");
    ui->label_fenge->setText("");

    ui->btn_mode->setStyleSheet("border-image:url(:/icons/png/ac_mode_off.png)");
    ui->btn_speed->setStyleSheet("QPushButton{border-image:url(:/icons/png/ac_speed_off.png)}");

    ui->btn_auto->setStyleSheet("QPushButton:checked{border-image:url(:/icons/png/ac_auto_checked.png)}"
                                "QPushButton:!checked{border-image:url(:/icons/png/ac_auto_unchecked.png)}");

    ui->btn_dry->setStyleSheet("QPushButton:checked{border-image:url(:/icons/png/ac_dry_checked.png)}"
                                "QPushButton:!checked{border-image:url(:/icons/png/ac_dry_unchecked.png)}");

    ui->btn_cold->setStyleSheet("QPushButton:checked{border-image:url(:/icons/png/ac_cold_checked.png)}"
                                "QPushButton:!checked{border-image:url(:/icons/png/ac_cold_unchecked.png)}");

    ui->btn_wind->setStyleSheet("QPushButton:checked{border-image:url(:/icons/png/ac_wind_checked.png)}"
                                "QPushButton:!checked{border-image:url(:/icons/png/ac_wind_unchecked.png)}");

    ui->btn_xiao->setStyleSheet("QPushButton:checked{border-image:url(:/icons/png/ac_xiao_checked.png)}"
                                "QPushButton:!checked{border-image:url(:/icons/png/ac_xiao_unchecked.png)}");
    ui->btn_low->setStyleSheet("QPushButton:checked{border-image:url(:/icons/png/ac_low_checked.png)}"
                                "QPushButton:!checked{border-image:url(:/icons/png/ac_low_unchecked.png)}");
    ui->btn_mid->setStyleSheet("QPushButton:checked{border-image:url(:/icons/png/ac_mid_checked.png)}"
                                "QPushButton:!checked{border-image:url(:/icons/png/ac_mid_unchecked.png)}");
    ui->btn_high->setStyleSheet("QPushButton:checked{border-image:url(:/icons/png/ac_high_checked.png)}"
                                "QPushButton:!checked{border-image:url(:/icons/png/ac_high_unchecked.png)}");

}

DeviceAC::~DeviceAC()
{
    delete ui;
}

void DeviceAC::doSliderOff()
{
    emit doSendData(socketMap.value(roomName),"<*06,102,00*>");


    ui->btn_auto->setCheckable(false);
    ui->btn_dry->setCheckable(false);
    ui->btn_cold->setCheckable(false);
    ui->btn_wind->setCheckable(false);
    ui->btn_xiao->setCheckable(false);
    ui->btn_low->setCheckable(false);
    ui->btn_mid->setCheckable(false);
    ui->btn_high->setCheckable(false);

    ui->btn_auto->setEnabled(false);
    ui->btn_dry->setEnabled(false);
    ui->btn_cold->setEnabled(false);
    ui->btn_wind->setEnabled(false);
    ui->btn_xiao->setEnabled(false);
    ui->btn_low->setEnabled(false);
    ui->btn_mid->setEnabled(false);
    ui->btn_high->setEnabled(false);

    ui->btn_auto->setChecked(false);
    ui->btn_xiao->setChecked(false);

    ui->label_ac->setStyleSheet("border-image:url(:/icons/png/ac_off.png)");
    ui->label_fenge->setStyleSheet("border-image:url(:/icons/png/ac_line_off.png)");

    ui->btn_mode->setStyleSheet("border-image:url(:/icons/png/ac_mode_off.png)");
    ui->btn_speed->setStyleSheet("QPushButton{border-image:url(:/icons/png/ac_speed_off.png)}");

    ui->label_onoff->setStyleSheet("color:rgb(40,40,40)");
    ui->label_onoff->setText("OFF");

    digitalScroller->hide();
}

void DeviceAC::doSliderOn()
{
    emit doSendData(socketMap.value(roomName),"<*06,102,01*>");


    ui->btn_auto->setCheckable(true);
    ui->btn_dry->setCheckable(true);
    ui->btn_cold->setCheckable(true);
    ui->btn_wind->setCheckable(true);
    ui->btn_xiao->setCheckable(true);
    ui->btn_low->setCheckable(true);
    ui->btn_mid->setCheckable(true);
    ui->btn_high->setCheckable(true);

    ui->btn_auto->setEnabled(true);
    ui->btn_dry->setEnabled(true);
    ui->btn_cold->setEnabled(true);
    ui->btn_wind->setEnabled(true);
    ui->btn_xiao->setEnabled(true);
    ui->btn_low->setEnabled(true);
    ui->btn_mid->setEnabled(true);
    ui->btn_high->setEnabled(true);

    ui->btn_auto->setChecked(true);
    ui->btn_xiao->setChecked(true);

    ui->label_ac->setStyleSheet("border-image:url(:/icons/png/ac_on.png)");
    ui->label_fenge->setStyleSheet("border-image:url(:/icons/png/ac_line_on.png)");

    ui->btn_mode->setStyleSheet("border-image:url(:/icons/png/ac_mode_on.png)");
    ui->btn_speed->setStyleSheet("QPushButton{border-image:url(:/icons/png/ac_speed_on.png)}");

    ui->label_onoff->setStyleSheet("color:rgb(36,110,202)");
    ui->label_onoff->setText("ON");

    digitalScroller->show();
}

void DeviceAC::doValueChange(int value)
{
  QString sendData="<*06,103,"+QString::number(value)+"*>";
  emit doSendData(socketMap.value(roomName),sendData);
}

void DeviceAC::doButtonClick()
{
  QPushButton *btn= qobject_cast<QPushButton*>(sender());

  QString btnName= btn->objectName();

  if(btnName=="btn_auto"||btnName=="btn_dry"||btnName=="btn_wind"||btnName=="btn_cold"){
    ui->btn_auto->setChecked(false);
    ui->btn_dry->setChecked(false);
    ui->btn_wind->setChecked(false);
    ui->btn_cold->setChecked(false);

  }else if(btnName=="btn_xiao"||btnName=="btn_low"||btnName=="btn_mid"||btnName=="btn_high"){
    ui->btn_xiao->setChecked(false);
    ui->btn_low->setChecked(false);
    ui->btn_mid->setChecked(false);
    ui->btn_high->setChecked(false);
  }
  btn->setChecked(true);
  if(btnName == "btn_auto")//自动
  {
    emit doSendData(socketMap.value(roomName),"<*06,104,00*>");
  }else if(btnName == "btn_dry")//除湿
  {
    emit doSendData(socketMap.value(roomName),"<*06,104,01*>");
  }else if(btnName == "btn_cold")//制冷
  {
    emit doSendData(socketMap.value(roomName),"<*06,104,02*>");
  }else if(btnName == "btn_wind")//送风
  {
    emit doSendData(socketMap.value(roomName),"<*06,104,03*>");
  }else if(btnName == "btn_xiao")//小风
  {

    emit doSendData(socketMap.value(roomName),"<*06,105,00*>");
  }else if(btnName == "btn_low")//微风
  {
    emit doSendData(socketMap.value(roomName),"<*06,105,01*>");
  }else if(btnName == "btn_mid")//大风
  {
    emit doSendData(socketMap.value(roomName),"<*06,105,02*>");
  }else if(btnName == "btn_high")//猛风
  {
    emit doSendData(socketMap.value(roomName),"<*06,105,03*>");
  }
}
