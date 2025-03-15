#ifndef DRAMA
#define DRAMA

#include "movie.h"

class Drama : public Movie {
public:
  Drama(const int num, const string &title, const string &director,
        const int release)
      : Movie(num, title, director, release) {};
  string getTitle() const override;
  string getDirector() const override;
  int getRelease() const override;
  bool operator<(const Movie &other) const override;
  char getGenreCode() const override;

  // return a pair of sorting attributes
  pair<string, string> parseSorters(const string &line) const override;

  // return director and title
  pair<string, string> getSorters() const override;

  static const char GENRE_CODE = 'D'; // Unique genre code for Drama
  static string genreName;

  string getGenreName() const override { return genreName; }

  void print(ostream &os) const override;
};

// initialize hardcoded genreName

class DramaFactory : public MovieFactory {
public:
  DramaFactory();
  Movie *makeMovie(const string &line) const override;
};

#endif