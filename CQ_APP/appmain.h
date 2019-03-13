#pragma once

#pragma comment(lib,"CQ_SDK.lib")
#include <CQSDK.h>
#include "CQMsgCode.h"
#include <fstream>
#include <sstream>

#include "httpTool.h"

//----我为什么要修改这个ID----
//这是您的插件名称,一个独一无二的名称

//----我应该如何修改这个ID----
//首先您应该修改下方的CQAPPID
//然后修改项目名称      (它会指引VS使用这个名称生成文件)
//最后修改json文件名称

//----我应该修改成什么----
//请查阅 http://d.cqp.me/Pro/开发/基础信息
#define CQAPPID "cpy.api.ttnaarashi.xyz"

#define CQAPPINFO CQAPIVERTEXT "," CQAPPID

//最重要的一句话
MUST_AppInfo_RETURN(CQAPPID)

using std::ifstream;
using std::ofstream;
using std::stringstream;

string getCQ_directory();

void sendHelp(MsgSend);