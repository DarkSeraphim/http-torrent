#ifndef __HTTP_RESPONSE_H_
#define __HTTP_RESPONSE_H_

#include <map>
#include <vector>

#include "body.h"
#include "header.h"

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

          const Header GetHeader(const string& key) const;

          const Body GetBody() const;
    };
}

#endif
