//
// Created by Administrator on 2024/1/6.
//

#ifndef SAMPLE_SMART_SERVER_GLOBAL_H
#define SAMPLE_SMART_SERVER_GLOBAL_H
#include <QMap>
const int LIVINGROOM=0;
const int BEDROOM=1;
const int CONNECT=1;
const int ERROR=0;
extern QMap<int,int> socketMap;//客户端名称与端口号关联起来
extern int livingRoomStatus;
class Global
{
public:
  Global();
  static int curr_socket;

};
#endif // SAMPLE_SMART_SERVER_GLOBAL_H
