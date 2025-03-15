#include "customer.h"

// destructor
// vector<pair<char, Movie *>> history;
// unordered_set<Movie *> borrowing;
Customer::~Customer() {
  borrowing.clear();

  // for (auto &pair : history) {
  //   Movie *movie = pair.second;
  //   pair.second = nullptr;
  //   delete movie;
  // }
}
// return true if this customer is borrowing the given movie
bool Customer::isBorrowing(Movie *movie) {
  return borrowing.find(movie) != borrowing.end();
}

bool Customer::borrowMovie(Movie *movie) {

  borrowing.insert(movie);
  history.push_back(make_pair('B', movie));
  return true;
}

// return true if the movie was successfully returned
bool Customer::returnMovie(Movie *movie) {
  if (!isBorrowing(movie)) {
    cout << "Return failed; customer " << id << " " << name
         << " is not borrowing " << movie->getTitle() << endl;
    return false;
  }
  borrowing.erase(movie);
  history.push_back(make_pair('R', movie));
  return true;
}

const vector<pair<char, Movie *>> &Customer::shareHistory() const {
  return history;
}

string Customer::shareName() const { return name; }