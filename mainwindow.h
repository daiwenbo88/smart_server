#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tcp/tcpserver.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class DeviceLamp;
class DeviceFan;
class DeviceCurtain;
class DeviceAC;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DeviceFan * deviceFan;
    DeviceLamp * deviceLamp;
    DeviceCurtain *deviceCurtain;
    DeviceAC *deviceAc;
    TcpServer *tcpServer;
    QTimer *timer;

    QPixmap pixmapToRound(const QPixmap &src, int radius);
  private slots:
    void timeout();
private:
    Ui::MainWindow *ui;
;
};
#endif // MAINWINDOW_H
