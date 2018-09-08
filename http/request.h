#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

#include <map>
#include <memory>
#include <vector>

#include "body.h"
#include "header.h"

namespace http {
	
	class Request {
	 private:
	   string method;
	   
	   string path;
	   
	   map<string, vector<string>> headers;
	   
	   vector<char> body;
	 
	 public:
	   Request(string method, string path, map<string, vector<string>> headers, vector<char> body);
	   ~Request();
	   
	   const string GetMethod() const;
	   
	   const string GetPath() const;
	   
	   const Header GetHeader(const string& key) const;
	   
       const Body GetBody() const;
	};
}

#endif
