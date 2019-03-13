#pragma once

#include <Windows.h>
#include <list>
#include <dbghelp.h>

#define CQTry __try{
#define CQTryEnd(evename,msg) }__except(dump(GetExceptionInformation(),#evename,#msg)){}

using std::list;

int dump(EXCEPTION_POINTERS* ep, const char*evename, const char*msg);