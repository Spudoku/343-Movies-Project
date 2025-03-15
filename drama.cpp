#include "drama.h"
#include "lineProcessor.h"
#include <sstream>
#include <string>
using namespace std;

string Drama::genreName = "Drama";
// return director
string Drama::getDirector() const { return director; }

// return title
string Drama::getTitle() const { return title; }

// return release
int Drama::getRelease() const { return release; }

char Drama::getGenreCode() const { return GENRE_CODE; }

// register 'F' as the code for this type of movie
DramaFactory::DramaFactory() {
  registerType('D', this);
  registerParser('D');
}

// F, 10, Nora Ephron, Sleepless in Seattle, 1993
// create a new Drama
Movie *DramaFactory::makeMovie(const string &line) const {
  vector<string> vs = LineProcessor::splitString(line);
  // format:
  // cout << "[Debug] trying to build a Drama with " << line << endl;
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
    // cout << "[Debug] trying to build a Drama with " << line << endl;
    num = stoi(vs[1]);
    director = vs[2];
    title = vs[3];
    release = stoi(vs[4]);
    // cout << "printing movie!\n\t";
    // for (const string &s : vs) {
    //   cout << s << ", ";
    // }
    // cout << endl;
  }

  return new Drama(num, title, director, release);
}

// sorting by title
bool Drama::operator<(const Movie &other) const {
  const Drama &otherDrama = dynamic_cast<const Drama &>(other);
  // cout << "DEBUG DRAMA <" << director << " < " << otherDrama.director << "? "
  //      << (director < otherDrama.director) << endl;
  if (director != otherDrama.director) {
    // cout << "DEBUG DRAMA <" << director << " < " << otherDrama.director << "?
    // "
    //      << (director < otherDrama.director) << endl;
    return director < otherDrama.director;
  }
  // cout << "\tDEBUG DRAMA <" << title << " < " << otherDrama.title << "? "
  //      << (title < otherDrama.title) << endl;
  return title < otherDrama.title;
}

// get sorting attributes in a pair form
pair<string, string> Drama::getSorters() const {
  return make_pair(director, title);
}

void Drama::print(ostream &os) const {

  os << director << ", " << title << ", " << release << " (" << count << ") - "
     << getGenreName();
}

// create a pair of sorters
//  format for drama: B <ID> D D <director>, <title>,
pair<string, string> Drama::parseSorters(const string &line) const {
  // cout << "[Drama] parsing sorters from " << line << endl;
  vector<string> vs = LineProcessor::splitString(line);

  return make_pair(vs[0], vs[1]);
}

// create object registers at runtime
DramaFactory anonymousDramaFactory;