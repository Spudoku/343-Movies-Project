#include "classic.h"
#include "lineProcessor.h"
#include <sstream>
#include <string>
using namespace std;

string Classic::genreName = "Classic";
// return director
string Classic::getDirector() const { return director; }

// return title
string Classic::getTitle() const { return title; }

// return release
int Classic::getRelease() const { return release; }

char Classic::getGenreCode() const { return GENRE_CODE; }

string Classic::getFamousActor() const { return famousActor; }

// register 'F' as the code for this type of movie
ClassicFactory::ClassicFactory() {
  registerType('C', this);
  registerParser('C');
}

// F, 10, Nora Ephron, Sleepless in Seattle, 1993
// create a new Classic
// C, 10, Stanley Kubrick, A Clockwork Orange, Malcolm McDowell 2 1971
Movie *ClassicFactory::makeMovie(const string &line) const {
  vector<string> vs = LineProcessor::splitString(line);
  // format:
  // cout << "[Debug] trying to build a Classic with " << line << endl;
  int num;
  string director;
  string title;
  int release;
  int month;
  string famousActor;
  if (vs.size() < 5 || vs.size() > 5) {
    num = 0;
    director = "DEBUG";
    title = "DEBUG";
    release = 0000;
    month = 1;
    famousActor = "DEBUG";
  } else {
    // cout << "[Debug] trying to build a Classic with " << line << endl;
    num = stoi(vs[1]);
    director = vs[2];
    title = vs[3];

    vector<string> vs2 = LineProcessor::splitString(vs[4], ' ');
    // cout << "printing vs2!\n\t";
    // for (const string &s : vs2) {
    //   cout << s << ", ";
    // }
    // cout << endl;
    famousActor = vs2[0] + " " + vs2[1];
    // cout << "Classic famous actor: " << famousActor << endl;
    month = stoi(vs2[2]);
    release = stoi(vs2[3]);
    // int release = 190000;
  }

  return new Classic(num, title, director, release, month, famousActor);
}

// sorting by title
bool Classic::operator<(const Movie &other) const {
  const Classic &otherClassic = dynamic_cast<const Classic &>(other);
  if (release != otherClassic.release) {
    // cout << "DEBUG Classic <" << title << " < " << otherClassic.title << "? "
    //      << (title < otherClassic.title) << endl;

    return release < otherClassic.release;
  }

  if (releaseMonth != otherClassic.releaseMonth) {
    // cout << "DEBUG Classic <" << title << " < " << otherClassic.title << "? "
    //      << (title < otherClassic.title) << endl;

    return releaseMonth < otherClassic.releaseMonth;
  }

  return famousActor < otherClassic.famousActor;
}

// get sorting attributes in a pair form
pair<string, string> Classic::getSorters() const {
  return make_pair(to_string(releaseMonth) + ' ' + to_string(release),
                   famousActor);
}

// print operator for Classic
// 1939 7, Judy Garland, Victor Fleming, The Wizard of Oz (10) - Classics
void Classic::print(ostream &os) const {

  os << release << " " << releaseMonth << ", " << director << ", "
     << famousActor << ", " << title << " (" << count << ") - "
     << getGenreName();
}

// create a pair of sorters
// format for classic: B <ID> D <release month> <release year> <actor>
pair<string, string> Classic::parseSorters(const string &line) const {
  // cout << "[Classic] parsing sorters from " << line << endl;

  istringstream is(line);
  string month;
  string year;
  string remaining;
  is >> month;
  is >> year;
  getline(is >> ws, remaining);
  // cout << "\t[Classic] Parsed into " << (month + " " + year) << ", "
  //      << remaining << endl;
  return make_pair(month + " " + year, remaining);
}

// create object registers at runtime
ClassicFactory anonymousClassicFactory;