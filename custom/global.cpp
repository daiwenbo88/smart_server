//
// Created by Administrator on 2024/1/6.
//

#include "global.h"
Global::Global()
{

}
QMap<int,int> socketMap;//客户端名称与端口号关联起来
int Global::curr_socket = 0;
int livingRoomStatus=ERROR;
