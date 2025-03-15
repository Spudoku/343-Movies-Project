#ifndef CLASSIC
#define CLASSIC

#include "movie.h"

class Classic : public Movie {
public:
  Classic(const int num, const string &title, const string &director,
          const int release, const int releaseMonth, const string &famousActor)
      : Movie(num, title, director, release) {
    this->releaseMonth = releaseMonth;
    this->famousActor = famousActor;
  };

  // getters
  string getTitle() const override;

  //
  string getDirector() const override;

  //
  int getRelease() const override;

  //
  string getFamousActor() const;

  //
  bool operator<(const Movie &other) const override;

  //
  char getGenreCode() const override;

  // return a pair of sorting attributes
  pair<string, string> parseSorters(const string &line) const override;

  // return release month + release year and actor
  pair<string, string> getSorters() const override;

  static const char GENRE_CODE = 'C'; // Unique genre code for Classic
  static string genreName;

  string getGenreName() const override { return genreName; }

  void print(ostream &os) const override;

private:
  string famousActor;
  int releaseMonth;
};

// initialize hardcoded genreName

class ClassicFactory : public MovieFactory {
public:
  ClassicFactory();
  Movie *makeMovie(const string &line) const override;
};

#endif