#ifndef _HTTP_BASE_H_
#define _HTTP_BASE_H_

#include <string>

using namespace std;

namespace http {

  class Headers {
    private:
      map<string, vector<string>> headers;

    public:
      Headers(map<string, vector<string>>& headers);
      
      const vector<string>::const_iterator Begin(string key);

      const vector<string>::const_iterator End(string key);

      const string GetFirst(string key);
  };

  class Body {
    private:
      vector<char> body;

    public:
      Body(vector<char>& body);

      const vector<char>::const_iterator Begin();

      const vector<char>::const_iterator End();
  };

}

#endif
