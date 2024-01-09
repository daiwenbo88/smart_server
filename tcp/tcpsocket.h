#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket(int sockID,QObject *parent = nullptr);

    void setClientData(int reg,QString data);
    void readClientData(int reg,QString data);
signals:
    void dataReady(const QString &ip,const QByteArray&data);
public slots:
    void recvData();
    void sendData(int id, const QByteArray& data);
  private:
    int socketId;
};

#endif // TCPSOCKET_H
