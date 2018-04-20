#ifndef __HTTP_RESPONSE_H_
#define __HTTP_RESPONSE_H_

#include "base.h"

#include <map>
#include <vector>

namespace http {
    class Response {
        private:
            int code;
            string reason;
            map<string, vector<string>> headers;
            vector<char> body;

        public:
          Response(int code, map<string, vector<string>> headers, vector<char> body)
            : Response(code, nullptr, headers, body) {}

          Response(int code, string reason, map<string, vector<string>> headers, vector<char> body);
          ~Response();

          const int GetCode();

          const string GetReason();

          const vector<string>::const_iterator GetHeadersBegin(string key);
          
          const vector<string>::const_iterator GetHeadersEnd(string key);
          
          const string GetFirstHeader(string key);

          const vector<char>::const_iterator GetBody();
    };
}

#endif
