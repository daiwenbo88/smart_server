#ifndef DIGITALSCROLLER_H
#define DIGITALSCROLLER_H

#include <QWidget>

class QMouseEvent;
class QPainter;
namespace Ui {
class DigitalScroller;
}
class QPropertyAnimation;
class DigitalScroller : public QWidget
{
    Q_OBJECT

public:
    explicit DigitalScroller(QWidget *parent = nullptr);
    ~DigitalScroller();


    void setRange(int min,int max);
    int readValue();
    QString getValueStr();
    void setFormat(QString prefix,QString suffix);
    void setCurValue(int value);
    void homing();
    void paintNum(QPainter &painter,int num,int deviation,bool isMiddle); //绘制数字

private:
    Ui::DigitalScroller *ui;
private:
    int mMinRange;
    int mMaxRange;
    int mCurrentValue;
    bool  isDragging;
    int mDeviation;
    int mMouseSrcPos;
    int msNumSize;
    bool isMiddle;
    QString mPrefix;
    QString mSuffix;
    QPropertyAnimation *homingAni;
    QTimer *timerChangedValue;



signals:
    void currentValueChanged(int value);
    void deviationChange(float deviation);

private slots:

    void doChoseFinshed();

    void doChangeValue();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

};



#endif // DIGITALSCROLLER_H
