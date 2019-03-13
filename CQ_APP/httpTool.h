#pragma once

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPCredentials.h>

#include <Poco/Net/HTTPSClientSession.h>

#include <Poco/StreamCopier.h>
#include <Poco/NullStream.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/Net/Context.h>

#include <iostream>
#include <fstream>

using Poco::Net::HTTPSClientSession;
using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::HTTPCredentials;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;
using Poco::Net::Context;

using std::string;

namespace CPY {
	bool getRequest_https(URI&, std::ostream&);
	bool getRequest_http(URI&, std::ostream&);
	bool getRequest(URI&, std::ostream&, bool);
	bool delRequest(URI, std::ostream&);
	bool putRequest(URI, string, std::ostream&);
}