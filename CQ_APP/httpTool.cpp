#include "httpTool.h"

namespace CPY
{
	bool getRequest(URI& uri, std::ostream& out, bool https) {
		if (https) {
			return getRequest_https(uri, out);
		} else {
			return getRequest_http(uri, out);
		}
	}

	bool getRequest_https(URI& uri, std::ostream& out) {
		Poco::Net::initializeSSL();

		string path(uri.getPathAndQuery());
		if (path.empty())
			path = "/";

		Context::Ptr context = new Context(Context::Usage::TLSV1_2_CLIENT_USE, "", Context::VERIFY_NONE,0);

		HTTPSClientSession session(uri.getHost(), uri.getPort(), context);

		HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		HTTPResponse response;

		session.sendRequest(request);
		std::istream& receive = session.receiveResponse(response);

		if (response.getStatus() != HTTPResponse::HTTP_UNAUTHORIZED) {
			StreamCopier::copyStreamUnbuffered(receive, out);
			Poco::Net::uninitializeSSL();
			return true;
		}

		Poco::NullOutputStream null;
		StreamCopier::copyStreamUnbuffered(receive, null);
		Poco::Net::uninitializeSSL();
		return false;
	}
	bool getRequest_http(URI& uri, std::ostream& out) {
		string path(uri.getPathAndQuery());
		if (path.empty())
			path = "/";


		HTTPClientSession session(uri.getHost(), uri.getPort());

		HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		HTTPResponse response;


		session.sendRequest(request);
		std::istream& receive = session.receiveResponse(response);

		if (response.getStatus() != HTTPResponse::HTTP_UNAUTHORIZED) {
			StreamCopier::copyStreamUnbuffered(receive, out);
			return true;
		}

		Poco::NullOutputStream null;
		StreamCopier::copyStreamUnbuffered(receive, null);
		return false;
	}

	bool delRequest(URI uri, std::ostream& out) {
		Poco::Net::initializeSSL();

		string path(uri.getPathAndQuery());
		if (path.empty())
			path = "/";

		Context::Ptr context = new Context(Context::Usage::TLSV1_2_CLIENT_USE, "", Context::VERIFY_NONE,0);

		HTTPSClientSession session(uri.getHost(), uri.getPort(), context);

		HTTPRequest request(HTTPRequest::HTTP_DELETE, path, HTTPMessage::HTTP_1_1);
		HTTPResponse response;

		session.sendRequest(request);
		std::istream& receive = session.receiveResponse(response);

		StreamCopier::copyStream(receive, out);
		Poco::Net::uninitializeSSL();
		return (response.getStatus() == HTTPResponse::HTTP_OK);
	}

	bool putRequest(URI uri, string data, std::ostream& out) {
		Poco::Net::initializeSSL();

		string path(uri.getPathAndQuery());
		if (path.empty())
			path = "/";

		Context::Ptr context = new Context(Context::Usage::TLSV1_2_CLIENT_USE, "", Context::VERIFY_NONE,0);

		HTTPSClientSession session(uri.getHost(), uri.getPort(), context);

		HTTPRequest request(HTTPRequest::HTTP_PUT, path, HTTPMessage::HTTP_1_1);
		request.setKeepAlive(true);
		request.setContentLength(data.size());
		request.setContentType("application/json");
		HTTPResponse response;

		std::ostream& put = session.sendRequest(request);
		put << data;
		std::istream& receive = session.receiveResponse(response);

		StreamCopier::copyStream(receive, out);
		Poco::Net::uninitializeSSL();
		return (response.getStatus() == HTTPResponse::HTTP_OK);
	}
}
