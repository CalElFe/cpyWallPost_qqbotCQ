#pragma once

#include "Base.h"

#include <string>

using std::string;

inline namespace CQ
{
	// 群匿名信息
	struct AnonymousInfo {
		长整数型 AID;
		string 代号;
		//std::vector<unsigned char> Token;

		AnonymousInfo(const char* fromAnonymousToken);
		AnonymousInfo() = default;
	};
}
