#pragma once

#pragma comment(lib,"CQ_SDK.lib")
#include <CQSDK.h>
#include "CQMsgCode.h"
#include <fstream>
#include <sstream>

#include "httpTool.h"

//----��ΪʲôҪ�޸����ID----
//�������Ĳ������,һ����һ�޶�������

//----��Ӧ������޸����ID----
//������Ӧ���޸��·���CQAPPID
//Ȼ���޸���Ŀ����      (����ָ��VSʹ��������������ļ�)
//����޸�json�ļ�����

//----��Ӧ���޸ĳ�ʲô----
//����� http://d.cqp.me/Pro/����/������Ϣ
#define CQAPPID "cpy.api.ttnaarashi.xyz"

#define CQAPPINFO CQAPIVERTEXT "," CQAPPID

//����Ҫ��һ�仰
MUST_AppInfo_RETURN(CQAPPID)

using std::ifstream;
using std::ofstream;
using std::stringstream;

string getCQ_directory();

void sendHelp(MsgSend);