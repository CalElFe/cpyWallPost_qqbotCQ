#include "CQMsgCode.h"
#include "tool.h"

using namespace CQ;

size_t strlen(string& s, size_t st) {
	size_t len = 0;
	while (s[st] != '\0' && st < s.size()) {
		st++;
		len++;
	}

	return len;
}

void MsgCode::decod() {
	bool key = false;

	bool δ��ʼ = true;
	for (size_t len = 0; len < txt.size(); len++) {
		switch (txt[len]) {
			default: //�ַ�����ʼ
				if (δ��ʼ) {
					δ��ʼ = false;
					msglist.push_back(CodeMsg(false, len));
				}
				break;
			case '[':         //code����ʼ
				txt[len] = 0; //ָ��[
				len += 3;     //����[CQ:ĩβ
				txt[len] = 0; //ָ��:
				msglist.push_back(CodeMsg(true, len + 1));
				δ��ʼ = false;
				break;
			case ',':
				if (msglist.rbegin()->isCode) {
					//ֻ����code���,���Ų�������
					key = true;
					txt[len] = 0;
					msglist.rbegin()->push_back(OneCodeMsg(len + 1));
				}
				break;
			case '=':
				if (key) {
					//���ں�ֻ�����key����
					key = false;
					txt[len] = 0;
					msglist.rbegin()->rbegin()->value = len + 1;
				}
				break;
			case ']': //������
				δ��ʼ = true;
				txt[len] = 0;
				break;
		}
	}
	//ͳ��keylen
	for (size_t i = 0; i < msglist.size(); i++) {
		auto& code = msglist[i];
		code.keylen = strlen(txt, code.key);
		if (code.isCode) {
			for (size_t k = 0; k < code.size(); k++) {
				auto& codearg = code[k];
				codearg.keylen = strlen(txt, codearg.key);
			}
		}
	}
	/*for each (auto &var in msglist)
	{
		var.keylen = strlen(txt, var.key);
		if (var.isCode)
		{
			for each (auto*var1 in var) {
				var1.keylen = strlen(txt, var1.key);
			}
		}
	}*/
}

MsgCode::MsgCode(std::string s) {
	txt = s;
	decod();
}

MsgCode& MsgCode::operator[](size_t i) {
	if (i >= 0 && i < msglist.size())
		thismsg = i;
	return *this;
}

MsgCode& MsgCode::operator++(int) {
	if (thismsg + 1 < msglist.size())
		++thismsg;
	return *this;
}

MsgCode& MsgCode::operator++() {
	if (thismsg + 1 < msglist.size())
		++thismsg;
	return *this;
}

MsgCode& MsgCode::operator--(int) {
	if (thismsg > 0)
		--thismsg;
	return *this;
}

MsgCode& MsgCode::operator--() {
	if (thismsg > 0)
		--thismsg;
	return *this;
}

MsgCode& MsgCode::operator-(size_t i) {
	if (thismsg - i >= 0)
		thismsg -= i;
	return *this;
}

MsgCode& MsgCode::operator+(size_t i) {
	if (thismsg + i < msglist.size())
		thismsg += i;
	return *this;
}

int MsgCode::pos() {
	return thismsg;
}

bool MsgCode::find(std::string& s, int k) {
	for (auto pos = thismsg; pos < msglist.size(); pos += k) {
		if (is(s, pos)) {
			thismsg = pos;
			return true;
		}
	}
	return false;
}

bool MsgCode::find(std::string s) {
	return find(s, 1);
}

bool MsgCode::lastfind(std::string s) {
	return find(s, -1);
}

bool MsgCode::isCQcode() {
	return msglist[thismsg].isCode;
}

bool MsgCode::is(std::string s) {
	return isCQcode() ? is(s, thismsg) : false;
}

std::string MsgCode::get() {
	string t(&txt[msglist[thismsg].key]);
	if (!isCQcode()) {
		t = msg_decode(t);
	}
	return t;
}

std::string MsgCode::get(std::string key) {
	auto& msg = msglist[thismsg];
	if (msg.isCode) {
		for (size_t i = 0; i < msg.size(); i++) {
			auto& codearg = msg[i];
			if (codearg.keylen == key.size()) {
				bool b = true;
				for (size_t i = 0; i < key.size(); i++) {
					if (key[i] != txt[codearg.key + i]) {
						b = false;
						break;
					}
				}
				if (b) {
					return msg_decode(string(&txt[codearg.value]), true);
				}
			}
		}
	}
	return string();
}

std::vector<std::string> MsgCode::keys() {
	std::vector<std::string> keys;
	auto& msg = msglist[thismsg];
	if (msg.isCode) {
		for each (OneCodeMsg var in msg) {
			keys.push_back(string(&txt[var.key]));
		}
	}
	return keys;
}

CodeMsgsFor MsgCode::begin() {
	return CodeMsgsFor(*this, 0);
}

CodeMsgsFor MsgCode::end() {
	return CodeMsgsFor(*this, msglist.size());
}

CodeMsg::CodeMsg(bool isCode, size_t key)
	:
	isCode(isCode),
	key(key) {}

OneCodeMsg::OneCodeMsg(size_t key)
	:
	key(key) {}

bool MsgCode::is(std::string& s, int pos) {
	CodeMsg& cm = msglist[pos];
	if (cm.isCode) {
		if (cm.keylen == s.size()) {
			for (size_t i = 0; i < s.size(); i++) {
				if (s[i] != txt[cm.key + i])
					return false;
			}
			return true;
		}
	}
	return false;
}

MsgCode& CodeMsgsFor::operator*() {
	return t[pos];
}

CodeMsgsFor& CodeMsgsFor::operator++() {
	++pos;
	return *this;
}

bool CodeMsgsFor::operator!=(CodeMsgsFor& t) {
	return t.pos != pos;
}

CodeMsgsFor::CodeMsgsFor(MsgCode& t, int pos)
	:
	t(t),
	pos(pos) {}

void MsgCode::debug() {
	for each (auto& var in msglist) {
		cout << var.keylen << "\t" << &txt[var.key] << endl;
		if (var.isCode) {
			for each (auto v in var) {
				cout << "\t" << v.keylen << "\t" << &txt[v.key] << "\t" << &txt[v.value] << endl;
			}
		}
	}
}
