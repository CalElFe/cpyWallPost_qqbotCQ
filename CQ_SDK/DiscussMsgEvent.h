#pragma once

#include "MsgEvent.h"

inline namespace CQ
{
	struct DiscussMsgEvent : public MsgEvent {
		long long fromDiscuss; //�������

		DiscussMsgEvent(int subType, int msgId, long long fromDiscuss, long long fromQQ, const char* msg, int font);

		//�˳�������
		bool leave() const;

		// ͨ�� MsgEvent �̳�
		MsgSend sendMsg() const override;
		int sendMsg(const char*) const override;
		int sendMsg(std::string) const override;
	};
}
