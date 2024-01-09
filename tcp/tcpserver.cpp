#include "tcpserver.h"
#include "tcpserverthread.h"

TcpServer::TcpServer(QObject *parent)
    : QTcpServer{parent}
{

}

TcpServer::~TcpServer()
{

}

void TcpServer::incomingConnection(qintptr handle)
{
  //有新的连接 毁掉整个函数
  TcpserverThread *tcpserverThread=new TcpserverThread(handle);
  connect(this, &TcpServer::sendToClinet,tcpserverThread,&TcpserverThread::doSendToClientData);
  tcpserverThread->start();
}

void TcpServer::doClientDisconnected(int sockDesc)
{

}

void TcpServer::deviceSendData(int sockId, QString sendData)
{   //将数据发送给对应的客户端
    emit sendToClinet(sockId,sendData);
}
