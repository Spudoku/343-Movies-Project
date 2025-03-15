#include "movie.h"
#include <map>
#include <memory>
#include <string>
using namespace std;

// storage place for MovieFactories
string Movie::genreName = "unknown";
// map<char, MovieFactory *> &MovieFactory::getMap() {
//   static map<char, MovieFactory *> factories;
//   return factories;
// }

void MovieFactory::printValidGenres() {
  cout << "List of genres: ";
  // for (const auto &pair : getHashTable()) {
  //   cout << pair.first << ", ";
  // }
  for (const char &key : getHashTable().getKeys()) {
    cout << key << " ";
  }
  cout << endl;
}

// register a factory
void MovieFactory::registerType(const char &type, MovieFactory *factory) {
  // cout << "[MovieFactory] registering type " << type << endl;
  getHashTable().insert(type, factory);
  // printValidGenres();
}

void MovieFactory::registerParser(const char &type) {
  // cout << "[MovieFactory] registering parser " << type << endl;
  // if (getParserTable().containsKey(type)) {
  //   cout << "[MovieFactory] parserTable already has key " << type << endl;
  // }

  shared_ptr<Movie> staticMovie(MovieFactory::create(type, ""));
  // cout << "[Parsers] inserting parser of type " << type
  //      << "; movie: " << *staticMovie << endl;
  getParserTable().insert(type, staticMovie);
}

// destructor
MovieFactory::~MovieFactory() {
  // for (char key : getParserTable().getKeys()) {
  //   if (getParserTable().at(key)) {
  //     delete getParserTable().at(key); // Free allocated movies
  //   }
  // }
}

// find corresponding movie factory and get it to create the object
// line might be validated before being passed to this function
Movie *MovieFactory::create(char type, const string &line) {
  // get character

  if (!getHashTable().containsKey(type)) {
    cout << "Can't create " << type << "; discarding line " << line << endl;
    return nullptr;
  }
  return getHashTable().at(type)->makeMovie(line);
}

// GenreCode = 0
Movie::Movie(const int count, const string &title, const string &director,
             const int release)
    : director(director), title(title), release(release), count(count),
      genreCode('0') {}

// print a good way to read Movies
ostream &operator<<(ostream &os, const Movie &item) {
  item.print(os);
  return os;
}

// attempt to borrow a movie
bool Movie::tryBorrow() {
  if (count > 0) {
    count--;
    return true;
  }
  count = 0;
  return false;
}

// change the count when returned
void Movie::returnMovie() { count++; }

// get sorting attributes in a pair form
pair<string, string> Movie::getSorters() const {
  return make_pair(title, director);
}
