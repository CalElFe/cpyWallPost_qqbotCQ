#pragma once
#include "Base.h"
#include <string>

using std::string;
using std::to_string;

inline namespace CQ
{
	// İ������Ϣ
	class StrangerInfo {
	public:
		�������� QQID;
		std::string nick; //�ǳ�
		������ sex;          //0/���� 1/Ů�� 255/δ֪
		������ age;          //����

		StrangerInfo(const char* msg);
		StrangerInfo() = default;

		std::string tostring() const;
	};
}