#pragma once
#include "Base.h"
#include <string>

using std::string;
using std::to_string;

inline namespace CQ
{
	// 陌生人信息
	class StrangerInfo {
	public:
		长整数型 QQID;
		std::string nick; //昵称
		整数型 sex;          //0/男性 1/女性 255/未知
		整数型 age;          //年龄

		StrangerInfo(const char* msg);
		StrangerInfo() = default;

		std::string tostring() const;
	};
}
