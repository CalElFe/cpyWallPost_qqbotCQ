#pragma once

#include "Base.h"

#include <string>

using std::string;

inline namespace CQ
{
	// Ⱥ������Ϣ
	struct AnonymousInfo {
		�������� AID;
		string ����;
		//std::vector<unsigned char> Token;

		AnonymousInfo(const char* fromAnonymousToken);
		AnonymousInfo() = default;
	};
}
