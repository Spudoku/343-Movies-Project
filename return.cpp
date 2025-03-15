#include "return.h"
#include "lineProcessor.h"
#include "store.h"
#include <iostream>
#include <sstream>
using namespace std;

/*
  Represents a query to access the Return of a Store object
*/

// attempt to let a customer Return a movie
bool Return::Execute() const {
  // search for customer
  Customer *customer = store->getCustomer(customerID);
  if (customer == nullptr) {
    cout << "Return failed; customer " << customerID << " not found" << endl;
    return false;
  }
  // search for movie
  Movie *movie = store->findInInventory(code, sorters);
  if (movie == nullptr) {
    cout << "Return failed; movie with info : " << code << ", ("
         << sorters.first << ", " << sorters.second << ") not found" << endl;
    return false;
  }

  // make sure it's in stock
  // if (!()) {
  //   cout << "Return failed; movie out of stock" << endl;
  //   return false;
  // }
  // movie->returnMovie();
  // take movie from customer I guess
  customer->returnMovie(movie);

  return true;
}

// register Return as a type
ReturnFactory::ReturnFactory(Store *s) : CommandFactory(s) {
  registerType('R', this);
  store = s;
}

// create a new Return command
Command *ReturnFactory::makeCommand(const string &line, Store *s) const {

  // cout << "[Return make-command] reading line " << line << endl;
  istringstream is(line);
  int id;
  char code;

  string discard;
  is >> discard;
  is >> id;
  is >> discard;
  is >> code;
  string remaining;
  getline(is >> ws, remaining);
  // cout << "\tid: " << id << ", code: " << code << ", remaining: " <<
  // remaining
  //      << endl;
  pair<string, string> sorters = Movie::parseFromType(code, remaining);
  // pair<string, string> sorters;
  return new Return(s, code, id, sorters);
}

// create object register at runtime
// extern unique_ptr<Store>
//     globalStore; // Ensure globalStore is declared somewhere
ReturnFactory anonymousReturnFactory(globalStore.get());