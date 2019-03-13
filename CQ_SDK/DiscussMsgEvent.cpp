#include "DiscussMsgEvent.h"

#include "API.h"

MsgSend DiscussMsgEvent::sendMsg() const { return MsgSend(fromQQ, ÌÖÂÛ×é); }

int DiscussMsgEvent::sendMsg(const char* msg) const { return sendDiscussMsg(fromDiscuss, msg); }
int DiscussMsgEvent::sendMsg(std::string msg) const { return sendDiscussMsg(fromDiscuss, msg); }

DiscussMsgEvent::DiscussMsgEvent(int subType, int msgId, long long fromDiscuss, long long fromQQ, const char* msg,
								 int font)
	:
	MsgEvent(subType, msgId, fromQQ, msg, font),
	fromDiscuss(fromDiscuss) {}

bool DiscussMsgEvent::leave() const { return !setDiscussLeave(fromDiscuss); }
