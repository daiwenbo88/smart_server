#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    ~TcpServer();
  protected:
    void incomingConnection(qintptr handle) override;
  public slots:
    void doClientDisconnected(int sockDesc);
    void deviceSendData(int sockId,QString sendData);
  signals:
    void sendToClinet(int sockId,QString sendData);
  private:
    QList<int> listSocket;
};

#endif // TCPSERVER_H
