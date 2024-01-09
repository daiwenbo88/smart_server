#include "digitalscroller.h"
#include "ui_digitalscroller.h"
#include <QTimer>
#include <QPropertyAnimation>
#include <QPainter>
#include <QMouseEvent>
/**
 * 温度刻
 * @param parent
 */
DigitalScroller::DigitalScroller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DigitalScroller)
{
    ui->setupUi(this);
    setFixedSize(50,200);
    setWindowFlag(Qt::FramelessWindowHint);//无边框窗体设置
    setAttribute(Qt::WA_TranslucentBackground);//背景半透明属性设置
    timerChangedValue=new QTimer(this);
    connect(timerChangedValue,&QTimer::timeout,this,&DigitalScroller::doChangeValue);

    mMinRange=16;//最低温度
    mMaxRange=31;//最高温度
    mCurrentValue=26;
    isDragging=0;
    mDeviation=0;
    msNumSize=8;
    isMiddle=false;
    mPrefix="";
    mSuffix="";

    homingAni=new QPropertyAnimation(this,"");
    homingAni->setDuration(500);
    homingAni->setEasingCurve(QEasingCurve::OutInQuad); //设置动画的缓动曲线，这里OutQuad是二次函数缓和曲线，减速到零速度

    connect(homingAni,&QPropertyAnimation::finished,this,&DigitalScroller::doChoseFinshed);
}

DigitalScroller::~DigitalScroller()
{
    delete ui;
}


void DigitalScroller::mouseMoveEvent(QMouseEvent *event)
{
    if(isDragging)
    {
      //数值到边界时，阻止继续往对应方向移动
      if((mCurrentValue == mMinRange && event->pos().y() >= mMouseSrcPos)||
          (mCurrentValue == mMaxRange && event->pos().y() <= mMouseSrcPos))
        return;

      mDeviation = event->pos().y() - mMouseSrcPos; //垂直偏移量 = 现在的坐标 - 开始的作标

      //若移动速度过快时进行限制
      if(mDeviation > (height()-1)/5)
      {
        mDeviation = (height()-1)/5;
      }

      else if(mDeviation < -(height()-1)/5)
      {
        mDeviation = -(height()-1)/5;
      }

      emit deviationChange((float)mDeviation/((height()-1)/5)); //发出偏移量改变的信号，随着偏移量改变，重绘数字，就变成数字滚动的效果
      update();
    }

    QWidget::mouseMoveEvent(event);
}

void DigitalScroller::mousePressEvent(QMouseEvent *event)
{
    isDragging=true;
    mMouseSrcPos = event->pos().y();
    QWidget::mousePressEvent(event);
}

void DigitalScroller::mouseReleaseEvent(QMouseEvent *event)
{
    if(isDragging) //如果鼠标松开了，那么还原一下鼠标按下标志位
    {
      homing();
      isDragging = false;
      update();
    }

    QWidget::mouseReleaseEvent(event);
}

void DigitalScroller::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); //创建画家类，指定绘图设备，也就是在哪画
    painter.setRenderHint(QPainter::Antialiasing, true); //反走样，就是抗锯齿

    int Width = width()-1; //设置宽高
    int Height = height()-1;

    if(mDeviation >= Height/5 && mCurrentValue > mMinRange) //偏移量大于1/5 高的时候，数字减一
    {
      mMouseSrcPos += Height/5; //鼠标起始位置重新设置，即加上1/5的高度
      mDeviation -= Height/5; //偏移量重新设置，即减去1/5的高度
      mCurrentValue--;
    }
    if(mDeviation <= -Height/5 && mCurrentValue < mMaxRange) //同理，数字加一
    {
      mMouseSrcPos -= Height/5;
      mDeviation += Height/5;
      mCurrentValue++;
    }

    //中间数字
    paintNum(painter,mCurrentValue,mDeviation,isMiddle=1); //将选中数字画到中间

    //两侧数字1
    if(mCurrentValue != mMinRange) //选中的数字不是最小，不是最大，那么就有两侧数字，然后画出两侧数字
      paintNum(painter,mCurrentValue-1,mDeviation-Height*2/10,isMiddle=0);
    if(mCurrentValue != mMaxRange)
      paintNum(painter,mCurrentValue+1,mDeviation+Height*2/10,isMiddle=0);

    //两侧数字2,超出则不显示
    if(mDeviation >= 0 && mCurrentValue-2 >= mMinRange)
      paintNum(painter,mCurrentValue-2,mDeviation-Height*4/10,isMiddle=0);
    if(mDeviation <= 0 && mCurrentValue+2 <= mMaxRange)
      paintNum(painter,mCurrentValue+2,mDeviation+Height*4/10,isMiddle=0);

    //画边框，中间数字两侧的边框
    painter.setPen(QPen(QColor(0,0,0,150),4));
    painter.drawLine(0,Height/8*3,Width,Height/8*3);
    painter.drawLine(0,Height/8*5,Width,Height/8*5);

    QWidget::paintEvent(event);
}

void DigitalScroller::doChoseFinshed()
{

}


void DigitalScroller::doChangeValue()
{

}
void DigitalScroller::paintNum(QPainter &painter,int num,int deviation,bool isMiddle){
    int Width = this->width()-1;
    int Height = this->height()-1;

    int size = (Height - qAbs(deviation))/msNumSize; //qAbs 返回输入参数对应类型的绝对值。
    int transparency = 255-510*qAbs(deviation)/Height; //设置透明度
    int height = Height/2-3*qAbs(deviation)/5;
    int y = Height/2+deviation-height/2;
    QFont font;
    font.setPixelSize(size); //设置像素大小
    painter.setFont(font); //设置字体
    if(isMiddle)
    {
      painter.setPen(QColor(36,110,202,transparency)); //设置画笔，中间颜色
    }
    else
    {
      painter.setPen(QColor(0,0,0,transparency)); //设置画笔，上下两侧数据颜色
    }
    QString str_date;
    if(num<=9)
    {
      str_date=QString("0")+QString::number(num);
    }
    else
    {
      str_date=QString::number(num);
    }
    str_date=mPrefix+str_date+mPrefix;
    painter.drawText(QRectF(0,y,Width,height), //画文本，参数：QRectF参数：位置xy，长宽大小；对齐方式，中间对齐；内容
                     Qt::AlignCenter,
                     str_date);
}

void DigitalScroller::setRange(int min,int max){
mMinRange=min;
mMaxRange=max;
if(mCurrentValue<min){
  mCurrentValue=min;
}
if(mCurrentValue>max){
  mCurrentValue=max;
}
msNumSize=3;
int temp=mMaxRange;
while (temp>0){
  temp/=10;
  msNumSize++;
}
update();
}
int DigitalScroller::readValue(){
    return  mCurrentValue;
}
QString DigitalScroller::getValueStr(){
    QString strValue;
    if(mCurrentValue<10){
      strValue="0";
    }
    strValue+=QString::number(mCurrentValue);
    return strValue;
}
void DigitalScroller::setFormat(QString prefix,QString suffix){
    mPrefix=prefix;
    mSuffix=suffix;
}
void DigitalScroller::setCurValue(int value){
  if(value>mMaxRange){
      value=mMaxRange;
  }else if(value<mMaxRange){
      value=mMinRange;
  }
  mCurrentValue=value;
  update();
}
void DigitalScroller::homing(){
    if(mDeviation>height()/20){
      homingAni->setStartValue((height()-1)/8-mDeviation);
      homingAni->setEndValue(0);
      mCurrentValue--;
    } else if(mDeviation>-(height())/20){
      homingAni->setStartValue(mDeviation);
      homingAni->setEndValue(0);

    }else if(mDeviation<-(height())/20){
      homingAni->setStartValue(-(height()-1)/8-mDeviation);
      homingAni->setEndValue(0);
      mCurrentValue++;
    }
    mDeviation=0;
    homingAni->start();
}
