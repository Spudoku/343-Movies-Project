#ifndef CUSTOMER
#define CUSTOMER
#include "movie.h"
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Customer {
public:
  // overloaded constructor
  Customer(int id, string name) : id(id), name(name) {}

  // destructor
  ~Customer();
  // return true if this customer is borrowing the given movie
  bool isBorrowing(Movie *movie);

  // return true if the movie was successfully returned
  bool returnMovie(Movie *movie);

  // return true if this movie was successfully borrowed
  bool borrowMovie(Movie *movie);

  const vector<pair<char, Movie *>> &shareHistory() const;

  string shareName() const;

private:
  int id;
  string name;
  unordered_set<Movie *> borrowing;

  // format: char represents command (either Borrow ('B') or Return ('R))
  // Movie* shows movie involved;
  vector<pair<char, Movie *>> history;
};
#endif