#pragma once
#include "Base.h"
#include <vector>
#include <string>

using std::string;
using std::to_string;


//base64����
string base64_encode(string const& s);

//base64����
string base64_decode(string const& s);

//�滻
string & msg_tihuan(string & s, string const old, string const New);

//CQcode����
string & msg_encode(string & s, bool isCQ = false);

//CQcode����
string & msg_decode(string & s, bool isCQ = false);

//���Ƶ�������ֽڼ�
string dump(void*t, int len);

//��ȡcpu��������������..
inline unsigned __int64 GetCycleCount() {
	__asm _emit 0x0F
	__asm _emit 0x31
}
