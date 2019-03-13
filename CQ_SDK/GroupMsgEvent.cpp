#include "GroupMsgEvent.h"

#include "API.h"

GroupMsgEvent::GroupMsgEvent(int subType, int msgId, long long fromGroup, long long fromQQ, const char* fromAnonymous,
							 const char* msg, int font)
	:
	MsgEvent(subType, msgId, fromQQ, msg, font),
	fromAnonymousInfo(),
	fromGroup(fromGroup),
	fromAnonymousToken(fromAnonymous) {}

GroupMsgEvent::~GroupMsgEvent() {
	if (fromAnonymousInfo != nullptr)
		delete fromAnonymousInfo;
}

bool GroupMsgEvent::isAnonymous() const { return fromQQ == 80000000; }

AnonymousInfo& GroupMsgEvent::getFromAnonymousInfo() //throw(std::exception_ptr)
{
	if (isAnonymous())
		return
				fromAnonymousInfo != nullptr
					? *fromAnonymousInfo
					: *(fromAnonymousInfo = new AnonymousInfo(fromAnonymousToken));
	throw std::exception_ptr();
}

bool GroupMsgEvent::setGroupKick(bool refusedAddAgain) {
	return !CQ::setGroupKick(fromGroup, fromQQ, refusedAddAgain);
}

bool GroupMsgEvent::setGroupBan(long long banTime) {
	if (isAnonymous()) {
		return !setGroupAnonymousBan(fromGroup, fromAnonymousToken, banTime);
	}
	return !CQ::setGroupBan(fromGroup, fromQQ, banTime);
}

bool GroupMsgEvent::setGroupAdmin(bool isAdmin) {
	return !CQ::setGroupAdmin(fromGroup, fromQQ, isAdmin);
}

bool GroupMsgEvent::setGroupSpecialTitle(std::string 专属头衔, long long 过期时间) {
	return !CQ::setGroupSpecialTitle(fromGroup, fromQQ, 专属头衔, 过期时间);
}

bool GroupMsgEvent::setGroupWholeBan(bool 开启禁言) {
	return CQ::setGroupWholeBan(fromGroup, 开启禁言);
}

bool GroupMsgEvent::setGroupAnonymous(bool 开启匿名) {
	return CQ::setGroupAnonymous(fromGroup, 开启匿名);
}

bool GroupMsgEvent::setGroupCard(std::string 新名片_昵称) {
	return CQ::setGroupCard(fromGroup, fromQQ, 新名片_昵称);
}

bool GroupMsgEvent::setGroupLeave(bool 是否解散) {
	return CQ::setGroupLeave(fromGroup, 是否解散);
}

GroupMemberInfo GroupMsgEvent::getGroupMemberInfo(bool 不使用缓存) {
	return CQ::getGroupMemberInfo(fromGroup, fromQQ, 不使用缓存);
}

std::vector<GroupMemberInfo> GroupMsgEvent::getGroupMemberList() {
	return CQ::getGroupMemberList(fromGroup);
}

int GroupMsgEvent::sendMsg(const char* msg) const { return sendGroupMsg(fromGroup, msg); }
int GroupMsgEvent::sendMsg(std::string msg) const { return sendGroupMsg(fromGroup, msg); }
MsgSend GroupMsgEvent::sendMsg() const { return MsgSend(fromGroup, 群); }
