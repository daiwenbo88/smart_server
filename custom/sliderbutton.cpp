#include "sliderbutton.h"
#include <QPainter>
#include <QPainterPath>
SliderButton::SliderButton(QWidget *parent)
    : QWidget{parent},mButtonStatus(false)
      ,mCircleWidth(30),mButtonPos(0),mMoveDistance(20),
      mBackColorOn(Qt::red),mBackColorOff(Qt::blue), mCircleColor(Qt::black)
{
  setWindowFlag(Qt::FramelessWindowHint);//无边框窗体设置
  setAttribute(Qt::WA_TranslucentBackground);//背景半透明属性设置
  mTimer=new QTimer(this);
  connect(mTimer,&QTimer::timeout,this,&SliderButton::doUpdate);
  setFixedSize(100,60);
}

void SliderButton::setButtonSize(const int w, const int h)
{
  mCircleWidth=h;
  mMoveDistance=w;
}

void SliderButton::setButtonColor(const QColor &offColor, const QColor &onColor, const QColor &buttonColor)
{
  mBackColorOn=onColor;
  mBackColorOff=offColor;
  mCircleColor=buttonColor;
}

void SliderButton::doUpdate()
{
  if(mButtonStatus){
    mButtonPos+=1;
    if(mButtonPos==mMoveDistance+mCircleWidth/2){
      mTimer->stop();
    }
  } else{
    mButtonPos-=1;
    if(mButtonPos==0){
      mTimer->stop();
    }
  }
  update();
}
void SliderButton::mousePressEvent(QMouseEvent *event)
{
  if(!mButtonStatus){
    emit doSwitchOn();
  }else{
    emit doSwitchOff();
  }
  mButtonStatus=!mButtonStatus;
  mTimer->start(1);
}

void SliderButton::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing,true);

  if(mButtonStatus){
    painter.setBrush(mBackColorOff);
  } else{
    painter.setBrush(mBackColorOn);
  }
  QRect rect(0,0,mCircleWidth,mCircleWidth);
  int startX=rect.left()+rect.width()/2;
  int startY=rect.top();
  QPainterPath path;
  path.moveTo(startX,startY);
  path.arcTo(QRect(rect.left(),rect.top(),rect.width(),rect.height()),90,180);
  path.lineTo(rect.left()+mMoveDistance,rect.bottom()+1);
  path.arcTo(QRect(startX+mMoveDistance,rect.top(),rect.width(),rect.height()),270,180);
  path.lineTo(startX,startY);
  painter.drawPath(path);

  painter.setBrush(mCircleColor);
  painter.drawEllipse(mButtonPos,0,mCircleWidth,mCircleWidth);

}
