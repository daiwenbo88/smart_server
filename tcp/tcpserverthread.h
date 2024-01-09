#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include "tcpsocket.h"
#include <QThread>

class TcpserverThread : public QThread
{
  Q_OBJECT
public:
    explicit TcpserverThread(int sockID,QObject *parent = nullptr);
    ~TcpserverThread();
  private:
    int sockedId;
    TcpSocket *tcpSocket;
  signals:
    void disconnetTCP(int socketId);
    void sendToClientData(int ,QByteArray);
  public slots:
    void disconnetToHost();
    void doSendToClientData(int sockID,QString sendData);
  protected:
    void run();
};

#endif // TCPSERVERTHREAD_H
