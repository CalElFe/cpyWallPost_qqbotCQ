#include "RequestAddFriendEvent.h"

#include "API.h"

RequestAddFriendEvent::RequestAddFriendEvent(int subType, int sendTime, long long fromQQ, const char* msg,
											 const char* responseFlag)
	:
	RequestBasicEvent(sendTime, fromQQ, msg, responseFlag),
	subType(subType) {}

void RequestAddFriendEvent::pass(std::string msg) {
	setFriendAddRequest(responseFlag, 请求_通过, msg.c_str());
	message_block();
}

void RequestAddFriendEvent::fail(std::string msg) {
	setFriendAddRequest(responseFlag, 请求_拒绝, msg.c_str());
	message_block();
}
