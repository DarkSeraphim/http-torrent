#include "request.h"

namespace http {

	Request::Request(string method, string path, map<string, vector<string>> headers, vector<char> body)
	  : headers(move(headers)), body(move(body)) {
	    this->method = method;
	    this->path = path;
	}
	
    Request::~Request() {
    }
   
    const string Request::GetMethod() const {
    	  return this->method;
    }
   
    const string Request::GetPath() const {
    	  return this->path;
    }

    const Header Request::GetHeader(const string& key) const {
        map<string, vector<string>>::const_iterator it;
        it = this->headers.find(key);
        if (it != this->headers.end()) {
            return Header(it->second);
        }
        return Header({});
    }

    const Body Request::GetBody() const {
        return Body(this->body);
    }
}
