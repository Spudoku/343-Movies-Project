#ifndef LINE_PROCESSOR
#define LINE_PROCESSOR
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class LineProcessor {
public:
  // helper - get rid of spaces before and after string
  static string trimString(const string &str) {
    return str.substr(str.find_first_not_of(' '),
                      str.find_last_not_of(' ') + 1);
  }

  // helper - split string into multiple based on delimiter
  static vector<string> splitString(const string &str, char delimiter = ',') {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
      tokens.push_back(trimString(token));
    }
    return tokens;
  }
};
#endif