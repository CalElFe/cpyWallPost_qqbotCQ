#include "appmain.h"


//�����static,��ʾ���loggerֻ�б�cpp��Ч
static Logger logger("cpyWallPost");
static unsigned long adminQQs[] = { 3148207231, 209691492, 2792836033, 1297919135, 2144108161, 2776003343, 515673540, 2908338622, 1834678551 };
//                                    7			ǽ		   4           5           3           6           2          2           ǽex

EVE_Request_AddFriend_EX(RequestAddFriend) {
	auto qq = e.fromQQ;

	for (auto adminQQ : adminQQs) {
		if (qq == adminQQ) {
			e.pass();
			MsgSend message(qq, msgtype::����);
			sendHelp(message);
			e.message_block();
		}
	}
}

EVE_PrivateMsg_EX(PrivateMsg) {
	auto qq = e.fromQQ;
	for (auto adminQQ : adminQQs) {
		if (qq == adminQQ) {
			auto message = e.sendMsg();
			logger.Info("�ѽӵ���Ϣ�̿�ʼ��������");

			MsgCode code(e.message);
			if (code.find("image")) {
				message << "�ѽӵ���Ϣ�̿�ʼ��������"<< send;
				logger.Debug("��ϢΪ�ļ������봦������");

				string img_name = code.get("file");
				string dir = getCQ_directory().append("\\image\\" + img_name + ".cqimg");
				logger.Debug("CQIMG ·��:" + dir);
				
				ifstream img_conf(dir);
				string buffer;
				string url = "none";

				if (img_conf.is_open()) {
					while (!img_conf.eof()) {
						img_conf >> buffer;
						url += buffer;
					}
					url = url.substr(url.find("url=") + 4);
					url = url.substr(0, url.find("addtime="));
				}
				logger.Debug() << "��������ͼƬ��ַΪ��" + url << send;
				img_conf.close();

				string postData = "{ \"post_data\": \"" + url + "\"}";
				logger.Debug() << "Json �������" << postData << send;

				stringstream receive;
				URI uri("https://cpy.api.ttnaarashi.xyz/cpyPosts/add/");
				if (CPY::putRequest(uri, postData, receive)) {
					logger.Debug() << "����������ֵ�� " + receive.str();
					message << "����ɹ������������ӣ��������еĶ�ά��" << send;
					message << "https://cpy.api.ttnaarashi.xyz/cpyPosts/qr/" + receive.str() + "/" << send;
				} else {
					logger.Error() << "����������ֵ�� " + receive.str();
					message << receive.str() << send;
				}

				e.message_block();
			} else {
				if (e.message.find("del%") == 0) {
					string msg = e.message.substr(4);
					logger.Debug() << "ɾ������ɾ��" << msg << send;
					URI uri("https://cpy.api.ttnaarashi.xyz/cpyPosts/del/" + msg + "/");
					stringstream out;

					if (CPY::delRequest(uri, out)) {
						logger.Info() << "ɾ������" << msg << "�ɹ�" << send;
						message << "ɾ������" << msg << "�ɹ�" << send;
					} else {
						logger.Error() << "����������ֵ�� " + out.str();
						message << out.str() << send;
					}
				} else if (e.message.find("help") == 0) {
					sendHelp(message);
				}
			}
		}
	}
}

string getCQ_directory() {
	string dir = getAppDirectory();
	dir = dir.substr(0, dir.find_last_of("\\"));
	dir = dir.substr(0, dir.find_last_of("\\"));
	return dir.substr(0, dir.find_last_of("\\"));
}

void sendHelp(MsgSend message) {
	message << "CPY Post system v1.0" << endl
			<< "����Աsama, ��ֱ�ӷ���ͼƬ���ϴ�~ by ����" << send;
}