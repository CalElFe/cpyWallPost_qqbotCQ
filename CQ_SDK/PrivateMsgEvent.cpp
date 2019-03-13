#include "PrivateMsgEvent.h"
#include "API.h"

PrivateMsgEvent::PrivateMsgEvent(int subType, int msgId, long long fromQQ, const char* msg, int font)
	:
	MsgEvent(subType, msgId, fromQQ, msg, font) {}

//���Ժ���
bool PrivateMsgEvent::fromPrivate() const { return subType == 11; }

//��������״̬
bool PrivateMsgEvent::fromOnlineStatus() const { return subType == 1; }

//����Ⱥ��ʱ
bool PrivateMsgEvent::fromGroup() const { return subType == 2; }

//������������ʱ
bool PrivateMsgEvent::fromDiscuss() const { return subType == 3; }

MsgSend PrivateMsgEvent::sendMsg() const { return MsgSend(fromQQ, ����); }

int PrivateMsgEvent::sendMsg(const char* msg) const { return sendPrivateMsg(fromQQ, msg); }
int PrivateMsgEvent::sendMsg(std::string msg) const { return sendPrivateMsg(fromQQ, msg); }
