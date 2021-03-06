#include "GroupMemberInfo.h"

#include "tool.h"

GroupMemberInfo::GroupMemberInfo(Unpack& msg) {
	setdata(msg);
}

GroupMemberInfo::GroupMemberInfo(const char* msg) {
	if (msg == nullptr || msg[0] == '\0') {
		Void();
	} else {
		Unpack u(base64_decode(msg));
		setdata(u);
		//setdata(Unpack(base64_decode(msg)));
	}
}

GroupMemberInfo::GroupMemberInfo(vector<unsigned char> data) {
	if (data.size() == 0) {
		Void();
	} else {
		Unpack u(data);
		setdata(u);
		//setdata(Unpack(base64_decode(msg)));
	}
}

void GroupMemberInfo::Void() {
	Group = 0;
	QQID = 0;
	昵称 = "";
	名片 = "";
	性别 = 0;
	年龄 = 0;
	地区 = "";
	加群时间 = 0;
	最后发言 = 0;
	等级_名称 = "";
	permissions = 0;
	不良记录成员 = 0;
	专属头衔 = "";
	专属头衔过期时间 = 0;
	允许修改名片 = 0;
}

void GroupMemberInfo::setdata(Unpack& u) {
	Group = u.getLong();
	QQID = u.getLong();
	昵称 = u.getString();
	名片 = u.getString();
	性别 = u.getInt();
	年龄 = u.getInt();
	地区 = u.getString();
	加群时间 = u.getInt();
	最后发言 = u.getInt();
	等级_名称 = u.getString();
	permissions = u.getInt();
	不良记录成员 = u.getInt() == 1;
	专属头衔 = u.getString();
	专属头衔过期时间 = u.getInt();
	允许修改名片 = u.getInt() == 1;
}

string GroupMemberInfo::tostring() const {
	string s = "{";
	s += "群号:";
	s += to_string(Group);
	s += " ,QQID:";
	s += to_string(QQID);
	s += " ,昵称:";
	s += 昵称;
	s += " ,名片:";
	s += 名片;
	s += " ,性别:";
	s += (
		性别 == 1 ? "男" : 性别 == 2 ? "女" : "未知");
	s += " ,年龄:";
	s += to_string(年龄);
	s += " ,地区:";
	s += 地区;
	s += " ,加群时间:";
	s += to_string(加群时间);
	s += " ,最后发言:";
	s += to_string(最后发言);
	s += " ,等级_名称:";
	s += 等级_名称;
	s += " ,管理权限:";
	s += (
		permissions == 3 ? "群主" : permissions == 2 ? "管理员" : permissions == 1 ? "群员" : "其他"
	);
	s += "(";
	s += to_string(permissions);
	s += ")";
	s += " ,不良记录成员:";
	s += to_string(不良记录成员);
	s += " ,专属头衔:";
	s += 专属头衔;
	s += " ,专属头衔过期时间:";
	s += to_string(专属头衔过期时间);
	s += " ,允许修改名片:";
	s += to_string(允许修改名片);
	s += "}";
	return s;
}
