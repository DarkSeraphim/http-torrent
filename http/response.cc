#include "response.h"

namespace http {

  Response::Response(int code, string reason, map<string, vector<string>> headers, vector<char> body)
      : headers(move(headers)), body(move(body)) {
	  this->code = code;
	  // TODO: fill in nullptr reason
	  this->reason = reason;
	  
	  
  }
  
  int Response::GetCode() {
  	  return this->code;
  }
  
  string Response::GetReason() {
  	  return this->reason;
  }
  
  
}
