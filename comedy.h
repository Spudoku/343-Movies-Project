#ifndef COMEDY
#define COMEDY

#include "movie.h"

class Comedy : public Movie {
public:
  Comedy(const int num, const string &title, const string &director,
         const int release)
      : Movie(num, title, director, release) {};
  string getTitle() const override;
  string getDirector() const override;
  int getRelease() const override;
  bool operator<(const Movie &other) const override;
  char getGenreCode() const override;

  static const char GENRE_CODE = 'F'; // Unique genre code for Comedy
  static string genreName;

  string getGenreName() const override { return genreName; }

  void print(ostream &os) const override;

  // return a pair of sorting attributes
  pair<string, string> parseSorters(const string &line) const override;

  // return title and release date
  pair<string, string> getSorters() const override;
};

// initialize hardcoded genreName

class ComedyFactory : public MovieFactory {
public:
  ComedyFactory();
  Movie *makeMovie(const string &line) const override;
};

#endif