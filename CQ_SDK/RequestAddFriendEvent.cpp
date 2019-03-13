#include "RequestAddFriendEvent.h"

#include "API.h"

RequestAddFriendEvent::RequestAddFriendEvent(int subType, int sendTime, long long fromQQ, const char* msg,
											 const char* responseFlag)
	:
	RequestBasicEvent(sendTime, fromQQ, msg, responseFlag),
	subType(subType) {}

void RequestAddFriendEvent::pass(std::string msg) {
	setFriendAddRequest(responseFlag, ����_ͨ��, msg.c_str());
	message_block();
}

void RequestAddFriendEvent::fail(std::string msg) {
	setFriendAddRequest(responseFlag, ����_�ܾ�, msg.c_str());
	message_block();
}
