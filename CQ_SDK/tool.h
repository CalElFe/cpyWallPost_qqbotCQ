#pragma once
#include "Base.h"
#include <vector>
#include <string>

using std::string;
using std::to_string;


//base64编码
string base64_encode(string const& s);

//base64解码
string base64_decode(string const& s);

//替换
string & msg_tihuan(string & s, string const old, string const New);

//CQcode编码
string & msg_encode(string & s, bool isCQ = false);

//CQcode解码
string & msg_decode(string & s, bool isCQ = false);

//类似调试输出字节集
string dump(void*t, int len);

//获取cpu启动后经历的周期..
inline unsigned __int64 GetCycleCount() {
	__asm _emit 0x0F
	__asm _emit 0x31
}
