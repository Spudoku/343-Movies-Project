#include "comedy.h"
#include "lineProcessor.h"
#include <sstream>
#include <string>
using namespace std;

string Comedy::genreName = "Comedy";
// return director
string Comedy::getDirector() const { return director; }

// return title
string Comedy::getTitle() const { return title; }

// return release
int Comedy::getRelease() const { return release; }

char Comedy::getGenreCode() const { return GENRE_CODE; }

// register 'F' as the code for this type of movie
ComedyFactory::ComedyFactory() {
  registerType('F', this);
  registerParser('F');
}

// F, 10, Nora Ephron, Sleepless in Seattle, 1993
// create a new Comedy
Movie *ComedyFactory::makeMovie(const string &line) const {
  vector<string> vs = LineProcessor::splitString(line);
  // format:
  // cout << "[Debug] trying to build a Comedy with " << line << endl;
  int num;
  string director;
  string title;
  int release;
  if (vs.size() < 5 || vs.size() > 5) {
    num = 0;
    director = "DEBUG";
    title = "DEBUG";
    release = 0000;
  } else {
    num = stoi(vs[1]);
    director = vs[2];
    title = vs[3];
    release = stoi(vs[4]);
  }
  // cout << "[Debug] trying to build a Comedy with " << line << endl;

  // cout << "printing movie!\n\t";
  // for (const string &s : vs) {
  //   cout << s << ", ";
  // }
  // cout << endl;
  return new Comedy(num, title, director, release);
}

// sorting by title
bool Comedy::operator<(const Movie &other) const {
  const Comedy &otherComedy = dynamic_cast<const Comedy &>(other);
  if (title != otherComedy.title) {
    // cout << "DEBUG COMEDY <" << title << " < " << otherComedy.title << "? "
    //      << (title < otherComedy.title) << endl;
    return title < otherComedy.title;
  }

  return release < otherComedy.release;
}

// get sorting attributes in a pair form
pair<string, string> Comedy::getSorters() const {
  return make_pair(title, to_string(release));
}

pair<string, string> Comedy::parseSorters(const string &line) const {
  // cout << "[Comedy] parsing sorters from " << line << endl;
  vector<string> vs = LineProcessor::splitString(line);

  return make_pair(vs[0], vs[1]);
}

void Comedy::print(ostream &os) const {

  os << title << ", " << release << ", " << director << " (" << count << ") - "
     << getGenreName();
}

// create object registers at runtime
ComedyFactory anonymousComedyFactory;