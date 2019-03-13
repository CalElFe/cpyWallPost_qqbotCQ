#include "code.h"

#include "tool.h"

string code::image(string file) {
	return string("[CQ:image,file=") + msg_encode(file, true) + "]";
}

string     code::record(string fileurl, bool magic) {
	string s = string("[CQ:record,file=") + msg_encode(fileurl, true);
	if (magic)
		s += ",magic=true";
	return s += "]";
}

//string CQ::code::record(string fileurl, string wantSpeak, bool magic)
//{
//	if (!Speak_to_wav_file(fileurl, wantSpeak))return string("");
//
//	string s = string("[CQ:record,file=") + msg_encode(fileurl, true);
//	if (magic)s += ",magic=true";
//	return s += "]";
//}

string code::face(int faceid) {
	return string("[CQ:face,id=") + to_string(faceid) + "]";
}

string code::face(CQ::face face) {
	return code::face(static_cast<int>(face));
}

string code::at(long long QQ) {
	return string("[CQ:at,qq=") + to_string(QQ) + "]";
}

string code::effect(string type, int id, string content) {
	return string("[CQ:effect,type=") + type + ",id=" + to_string(id) + ",content=" + msg_encode(content, true) + "]";
}

string code::sign(string title, string imageUrl) {
	return string("[CQ:sign,title=") + msg_encode(title, true) + ",image=" + msg_encode(imageUrl, true) + "]";
}

string code::anonymous(bool ignore) {
	return string(ignore ? "[CQ:anonymous,ignore=true]" : "[CQ:anonymous]");
}
