#include "StrangerInfo.h"

#include "tool.h"
#include "Unpack.h"

StrangerInfo::StrangerInfo(const char* msg) {
	if (msg == nullptr || msg[0] == '\0') {
		QQID = 0;
		sex = 255;
		age = -1;
		nick = "";
	} else {
		Unpack p(base64_decode(msg));
		QQID = p.getLong();
		nick = p.getString();
		sex = p.getInt();
		age = p.getInt();
	}
}

string StrangerInfo::tostring() const {
	return string("{")
	       + "QQ:" + to_string(QQID)
	       + " ,�ǳ�:" + nick
	       + " ,�Ա�:" + (sex == 255 ? "δ֪" : sex == 1 ? "��" : "Ů")
	       + " ,����:" + to_string(age)
	       + "}";
}
