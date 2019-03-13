#include "MsgEvent.h"

MsgEvent::MsgEvent(int subType, int msgId, long long fromQQ, const char* message, int font)
	:
	msgId(msgId),
	fromQQ(fromQQ),
	message(message),
	messageRAW(const_cast<char*>(message)),
	subType(subType),
	font(font) {}

//真实用户
bool MsgEvent::isUser() const {
	switch (fromQQ) {
		case 1000000:  // 系统提示
		case 80000000: // 匿名
			return false;
		default:
			return true;
	}
}

bool MsgEvent::isSystem() const {
	return fromQQ == 1000000;
}
