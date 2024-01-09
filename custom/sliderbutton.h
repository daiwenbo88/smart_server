#ifndef SLIDERBUTTON_H
#define SLIDERBUTTON_H

#include <QObject>
#include <QWidget>
#include <QTimer>
class QMouseEvent;
class SliderButton : public QWidget
{
    Q_OBJECT
public:
    explicit SliderButton(QWidget *parent = nullptr);
    void setButtonSize(const int w,const int h);
    void setButtonColor(const QColor&,const QColor &,const QColor &);

private:
    bool mButtonStatus;
    int mCircleWidth;
    int mButtonPos;
    int mMoveDistance;

    QColor mBackColorOn;
    QColor mBackColorOff;
    QColor mCircleColor;

    QTimer *mTimer;

public slots:
    void doUpdate();
signals:
    void doSwitchOn();
    void doSwitchOff();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
};



#endif // SLIDERBUTTON_H
