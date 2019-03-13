#pragma once

#include "MsgEvent.h"

inline namespace CQ
{
	struct PrivateMsgEvent : public MsgEvent {
		PrivateMsgEvent(int subType, int msgId, long long fromQQ, const char* msg, int Font);

		//���Ժ���
		bool fromPrivate() const;

		//��������״̬
		bool fromOnlineStatus() const;

		//����Ⱥ��ʱ
		bool fromGroup() const;

		//������������ʱ
		bool fromDiscuss() const;

		// ͨ�� MsgEvent �̳�
		MsgSend sendMsg() const override;

		int sendMsg(const char*) const override;

		int sendMsg(std::string) const override;
	};
}
