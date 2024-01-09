#include "tcpsocket.h"
#include "../custom/global.h"

TcpSocket::TcpSocket(int sockID,QObject *parent)
    : QTcpSocket{parent}
{
  socketId=sockID;
  connect(this,&QTcpSocket::readyRead,this,&TcpSocket::recvData);//有数据 发送过来
}

void TcpSocket::setClientData(int reg, QString data)
{

}

void TcpSocket::readClientData(int reg, QString data)
{
  //获取当前客户端的名称，寄存器0的位置代表当前连接的客户端的名称。
  int temp = data.toInt();
  if(reg == 0)
  {
    if(temp == 0)//如果编号为0，则是客厅
    {
      socketMap.insert(LIVINGROOM,socketId);
      qDebug() << "当前连接的是客厅";
      livingRoomStatus = CONNECT;


    }else if(temp == 1)//如果编号为1，则是卧室
    {
      socketMap.insert(BEDROOM,socketId);
      qDebug() << "当前连接的是卧室";
    }
  }
}

void TcpSocket::recvData()
{
  QString ip= peerAddress().toString();
  QByteArray recData=readAll();
  qDebug()<<"recData="+recData;
  QString validData;
  QStringList listValidData;
  int func;
  int reg;
  QString data;
  if(recData.left(2)=="<*"&&recData.right(2)=="*>"&&recData.count(",")==2){
    validData=recData.replace("<*","");
    validData=recData.replace("*>","");
    listValidData=validData.split(",");
    func=listValidData.at(0).toInt();
    reg=listValidData.at(1).toInt();
    data=listValidData.at(2);
    if(func==03){
      readClientData(reg,data);
    } else if(func==06){

    }
  }
}

void TcpSocket::sendData(int id, const QByteArray &data)
{
    if(socketId==id&&!data.isEmpty()){
      write(data);//发送数据
    }
}
