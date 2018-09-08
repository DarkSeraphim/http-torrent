#include "response.h"

namespace http {

    Response::Response(int code, string reason, map<string, vector<string>> headers, vector<char> body)
      : headers(move(headers)), body(move(body)) {
	      this->code = code;
	      // TODO: fill in nullptr reason
        this->reason = reason;
    }
  
    const int Response::GetCode() {
       return this->code;
    }
  
    const string Response::GetReason() {
        return this->reason;
    }

    const Header Response::GetHeader(const string& key) const {
        map<string, vector<string>>::const_iterator it;
        it = this->headers.find(key);
        if (it != this->headers.end()) {
            // Handle empty headers?
            return Header(it->second);
        }
        return Header({});
    }

    const ::http::Body Response::GetBody() const {
        return Body(this->body);
    }
}
