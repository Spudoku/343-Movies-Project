/*
    Superclass for movie objects
    Children will be referred to by their genre
*/
#ifndef MOVIE
#define MOVIE

#include "alphaHash.h"
#include "lineProcessor.h"
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// forward declaration
class Movie;

// Abstact MovieFactory; each subclass of Movie represents a genre
class MovieFactory {
public:
  ~MovieFactory();
  // attempt to make a movie if a valid line is passed, return nullptr if failed
  virtual Movie *makeMovie(const string &line) const = 0;

  // find movie factory and make the object
  static Movie *create(char type, const string &line);

  // print all character codes for genres
  static void printValidGenres();

  // generate a table of Movies that will parse something
  static AlphaHash<shared_ptr<Movie>> &getParserTable() {
    static AlphaHash<shared_ptr<Movie>> parsers;
    return parsers;
  }

protected:
  // register a factory with given name
  static void registerType(const char &type, MovieFactory *factory);
  static void registerParser(const char &type);

private:
  // stores all movie factories
  // static map<char, MovieFactory *> &getMap();
  static AlphaHash<MovieFactory *> &getHashTable() {
    static AlphaHash<MovieFactory *> factories;
    return factories;
  }
};

/*
  Abstract movie class
  Stores all sorting data
*/

class Movie {
public:
  Movie(int count, const string &title, const string &director, int release);

  // print a Movie object
  friend ostream &operator<<(ostream &os, const Movie &item);

  // getter for title
  virtual string getTitle() const = 0;
  // getter for director
  virtual string getDirector() const = 0;

  // getter for release date
  virtual int getRelease() const = 0;

  // comaparator
  virtual bool operator<(const Movie &other) const = 0;

  // destructor
  virtual ~Movie() = default;

  virtual char getGenreCode() const = 0;

  static string genreName;
  virtual string getGenreName() const { return genreName; }

  // attempt to borrow this movie if there is at least 1 copy of it
  bool tryBorrow();

  // increase count by 1;
  void returnMovie();

  // call the parser from parserTable
  static pair<string, string> parseFromType(char type, string &line) {
    // cout << "[Movie parse-from-type] trying to parse " << type << ", " <<
    // line
    //      << endl;
    if (!MovieFactory::getParserTable().containsKey(type)) {
      cout << "[Movie parse-from-type] parser of type " << type
           << " not found !" << endl;
      return make_pair("fail", "fail");
    }
    return MovieFactory::getParserTable().at(type)->parseSorters(line);
  }

  // return a pair of sorting attributes
  virtual pair<string, string> parseSorters(const string &line) const = 0;

  virtual pair<string, string> getSorters() const = 0;

  virtual void print(ostream &os) const {
    os << title << ", " << release << ", " << director << " (" << count
       << ") - " << getGenreName();
  }
  virtual int getCount() { return count; }

protected:
  string director, title;
  int release, count; // number in the Store
  char genreCode;

  // 'string major actor' will only be tracked in Classic movies
};

#endif