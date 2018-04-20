#include "request.h"

namespace http {

	Request::Request(string method, string path, map<string, string> headers, vector<char> body)
	  : headers(move(headers)), body(move(body)) {
	    this->method = method;
	    this->path = path;
	}
	
    Request::~Request() {
    }
   
    const string Request::GetMethod() {
    	  return this->method;
    }
   
    const string Request::GetPath() {
    	  return this->path;
    }
   
    const string Request::GetHeader(string key) {
        map<string, string>::iterator it;
        it = this->headers.find(key);
        if (it != this->headers.end()) {
            return it->second;
        }
        return nullptr;
    }
   
    vector<char>::const_iterator Request::BodyBegin() const {
        return this->body.cbegin();
    }
       
    vector<char>::const_iterator Request::BodyEnd() const {
        return this->body.cend();
    }
}
