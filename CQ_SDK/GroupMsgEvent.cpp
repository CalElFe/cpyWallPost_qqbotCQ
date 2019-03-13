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

bool GroupMsgEvent::setGroupSpecialTitle(std::string ר��ͷ��, long long ����ʱ��) {
	return !CQ::setGroupSpecialTitle(fromGroup, fromQQ, ר��ͷ��, ����ʱ��);
}

bool GroupMsgEvent::setGroupWholeBan(bool ��������) {
	return CQ::setGroupWholeBan(fromGroup, ��������);
}

bool GroupMsgEvent::setGroupAnonymous(bool ��������) {
	return CQ::setGroupAnonymous(fromGroup, ��������);
}

bool GroupMsgEvent::setGroupCard(std::string ����Ƭ_�ǳ�) {
	return CQ::setGroupCard(fromGroup, fromQQ, ����Ƭ_�ǳ�);
}

bool GroupMsgEvent::setGroupLeave(bool �Ƿ��ɢ) {
	return CQ::setGroupLeave(fromGroup, �Ƿ��ɢ);
}

GroupMemberInfo GroupMsgEvent::getGroupMemberInfo(bool ��ʹ�û���) {
	return CQ::getGroupMemberInfo(fromGroup, fromQQ, ��ʹ�û���);
}

std::vector<GroupMemberInfo> GroupMsgEvent::getGroupMemberList() {
	return CQ::getGroupMemberList(fromGroup);
}

int GroupMsgEvent::sendMsg(const char* msg) const { return sendGroupMsg(fromGroup, msg); }
int GroupMsgEvent::sendMsg(std::string msg) const { return sendGroupMsg(fromGroup, msg); }
MsgSend GroupMsgEvent::sendMsg() const { return MsgSend(fromGroup, Ⱥ); }
