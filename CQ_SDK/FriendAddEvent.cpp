#include "FriendAddEvent.h"

FriendAddEvent::FriendAddEvent(int subType, int sendTime, long long fromQQ)
	:
	sendTime(sendTime),
	fromQQ(fromQQ),
	subType(subType) {}
