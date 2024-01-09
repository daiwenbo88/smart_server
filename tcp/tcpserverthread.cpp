#include "tcpserverthread.h"
#include "../custom/global.h"

TcpserverThread::TcpserverThread(int sockID,QObject *parent)
    : QThread{parent}
{
    sockedId=sockID;
}

TcpserverThread::~TcpserverThread()
{
    
}

void TcpserverThread::disconnetToHost()
{
    emit disconnetTCP(sockedId);
    if(socketMap.value(sockedId)==LIVINGROOM){
      livingRoomStatus=ERROR;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->destroyed();
    this->quit();
}

void TcpserverThread::doSendToClientData(int sockID, QString sendData)
{
    emit sendToClientData(sockID,sendData.toUtf8());
}

void TcpserverThread::run()
{
    tcpSocket=new TcpSocket(sockedId);
    Global::curr_socket=sockedId;
    if(!tcpSocket->setSocketDescriptor(sockedId)){
      return;
    }

    connect(tcpSocket,&TcpSocket::disconnected,this,&TcpserverThread::disconnetToHost);;//断开连接监听
    connect(this,&TcpserverThread::sendToClientData,tcpSocket,&TcpSocket::sendData);

    emit sendToClientData(sockedId,"<*03,00,01*>");
    this->exec();
}
