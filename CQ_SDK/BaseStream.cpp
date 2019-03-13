#include "BaseStream.h"

#include "tool.h"

bool BaseStream::isRAW() { return raw; }

void BaseStream::clear() { buf.clear(); }

BaseStream& BaseStream::append(const string& s) {
	buf += (raw ? msg_encode(string(s)) : s);
	return *this;
}

BaseStream& BaseStream::operator<<(const string& s) { return (*this).append(s); }

BaseStream& BaseStream::append(const char* s) {
	buf += (raw ? msg_encode(string(s)) : s);
	return *this;
}

BaseStream& BaseStream::operator<<(const char* c) { return (*this).append(c); }

BaseStream& BaseStream::append(const bool& i) {
	buf += i ? "true" : "false";
	return *this;
}

BaseStream& BaseStream::operator<<(const bool& i) { return (*this).append(i); }

BaseStream& BaseStream::append(const int& i) {
	buf += to_string(i);
	return *this;
}

BaseStream& BaseStream::operator<<(const int& i) { return (*this).append(i); }

BaseStream& BaseStream::append(const size_t& i) {
	buf += to_string(i);
	return *this;
}

BaseStream& BaseStream::operator<<(const size_t& i) { return (*this).append(i); }

BaseStream& BaseStream::append(const double& i) {
	buf += to_string(i);
	return *this;
}

BaseStream& BaseStream::operator<<(const double& i) { return (*this).append(i); }

BaseStream& BaseStream::append(const long& i) {
	buf += to_string(i);
	return *this;
}

BaseStream& BaseStream::operator<<(const long& i) { return (*this).append(i); }

BaseStream& BaseStream::append(const long long& l) {
	buf += to_string(l);
	return *this;
}

BaseStream& BaseStream::operator<<(const long long& l) { return (*this).append(l); }

BaseStream& BaseStream::operator<<(void (*control)(BaseStream&)) {
	control(*this);
	return *this;
}

void BaseStream::FLUSH() { SEND(); }

BaseStream::~BaseStream() = default;
