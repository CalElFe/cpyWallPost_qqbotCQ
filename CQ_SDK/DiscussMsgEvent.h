#pragma once

#include "MsgEvent.h"

inline namespace CQ
{
	struct DiscussMsgEvent : public MsgEvent {
		long long fromDiscuss; //讨论组号

		DiscussMsgEvent(int subType, int msgId, long long fromDiscuss, long long fromQQ, const char* msg, int font);

		//退出讨论组
		bool leave() const;

		// 通过 MsgEvent 继承
		MsgSend sendMsg() const override;
		int sendMsg(const char*) const override;
		int sendMsg(std::string) const override;
	};
}
