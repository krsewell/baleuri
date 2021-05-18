/*
 * URI.h
 *
 *  Created on: May 17, 2021
 *      Author: kris
 */

#ifndef UNIFORMRESOURCEIDENTIFIER_H_
#define UNIFORMRESOURCEIDENTIFIER_H_

#include <string>
#include <boost/regex.hpp>

class URI {
private:
	auto static const pattern =
			boost::regex(
					"^(?<scheme>[a-zA-Z][a-zA-Z0-9+\-.]*):"
							"(?<authority>\/\/(?<userinfo>[\w-~.!$&'()*+,;=:]*@)?(?<host>(?:[\w-~.!$&'()*+,;=]*)|(?:\[[\da-fA-F:]*\]))+(?<port>:\d+)?)?"
							"(?<path>\/*[\w-~.!$&'()*+,;=@]*(?:\/[\w-~.!$&'()*+,;=@]*)*)?"
							"(?<query>\?[\w-~.!$&'()*+,;=@\/\?]*)?(?<fragment>#[\w-~.!$&'()*+,;=@\/\?]*)?$",
					static_cast<boost::regex::flag_type>(boost::regex::ECMAScript
							| boost::regex::optimize));
	boost::smatch matches;
	std::string raw;

public:
	URI();
	virtual ~URI();
	URI& operator=(URI &&other);
	URI& operator=(const URI &other);
	URI(URI &&other);
	URI(const URI &other);

	const std::string& scheme();
	const std::string& userinfo();
	const std::string& host();
	const std::string& port();
	const std::string& path();
	const std::string& query();
	const std::string& fragment();
};

#endif /* UNIFORMRESOURCEIDENTIFIER_H_ */

// unreserved = \w-~.
// subdelimiter = !$&'()*+,;=
// pchar = unreserved / pct-encoded / sub-delims / ":" / "@"
