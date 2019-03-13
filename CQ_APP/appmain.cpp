#include "appmain.h"


//请加上static,表示这个logger只有本cpp有效
static Logger logger("cpyWallPost");
static unsigned long adminQQs[] = { 3148207231, 209691492, 2792836033, 1297919135, 2144108161, 2776003343, 515673540, 2908338622, 1834678551 };
//                                    7			墙		   4           5           3           6           2          2           墙ex

EVE_Request_AddFriend_EX(RequestAddFriend) {
	auto qq = e.fromQQ;

	for (auto adminQQ : adminQQs) {
		if (qq == adminQQ) {
			e.pass();
			MsgSend message(qq, msgtype::好友);
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
			logger.Info("已接到消息√开始处理。。。");

			MsgCode code(e.message);
			if (code.find("image")) {
				message << "已接到消息√开始处理。。。"<< send;
				logger.Debug("消息为文件，进入处理流程");

				string img_name = code.get("file");
				string dir = getCQ_directory().append("\\image\\" + img_name + ".cqimg");
				logger.Debug("CQIMG 路径:" + dir);
				
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
				logger.Debug() << "解析出的图片地址为：" + url << send;
				img_conf.close();

				string postData = "{ \"post_data\": \"" + url + "\"}";
				logger.Debug() << "Json 构造完成" << postData << send;

				stringstream receive;
				URI uri("https://cpy.api.ttnaarashi.xyz/cpyPosts/add/");
				if (CPY::putRequest(uri, postData, receive)) {
					logger.Debug() << "服务器返回值： " + receive.str();
					message << "处理成功，请打开这个链接，发布其中的二维码" << send;
					message << "https://cpy.api.ttnaarashi.xyz/cpyPosts/qr/" + receive.str() + "/" << send;
				} else {
					logger.Error() << "服务器返回值： " + receive.str();
					message << receive.str() << send;
				}

				e.message_block();
			} else {
				if (e.message.find("del%") == 0) {
					string msg = e.message.substr(4);
					logger.Debug() << "删除请求，删除" << msg << send;
					URI uri("https://cpy.api.ttnaarashi.xyz/cpyPosts/del/" + msg + "/");
					stringstream out;

					if (CPY::delRequest(uri, out)) {
						logger.Info() << "删除单子" << msg << "成功" << send;
						message << "删除单子" << msg << "成功" << send;
					} else {
						logger.Error() << "服务器返回值： " + out.str();
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
			<< "管理员sama, 请直接发送图片来上传~ by 三三" << send;
}