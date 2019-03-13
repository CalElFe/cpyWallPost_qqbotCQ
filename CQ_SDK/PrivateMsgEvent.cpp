#include "PrivateMsgEvent.h"
#include "API.h"

PrivateMsgEvent::PrivateMsgEvent(int subType, int msgId, long long fromQQ, const char* msg, int font)
	:
	MsgEvent(subType, msgId, fromQQ, msg, font) {}

//来自好友
bool PrivateMsgEvent::fromPrivate() const { return subType == 11; }

//来自在线状态
bool PrivateMsgEvent::fromOnlineStatus() const { return subType == 1; }

//来自群临时
bool PrivateMsgEvent::fromGroup() const { return subType == 2; }

//来自讨论组临时
bool PrivateMsgEvent::fromDiscuss() const { return subType == 3; }

MsgSend PrivateMsgEvent::sendMsg() const { return MsgSend(fromQQ, 好友); }

int PrivateMsgEvent::sendMsg(const char* msg) const { return sendPrivateMsg(fromQQ, msg); }
int PrivateMsgEvent::sendMsg(std::string msg) const { return sendPrivateMsg(fromQQ, msg); }
