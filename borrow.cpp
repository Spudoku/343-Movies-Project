#include "borrow.h"
#include "lineProcessor.h"
#include "store.h"
#include <iostream>
#include <sstream>
using namespace std;

/*
  Represents a query to access the Borrow of a Store object
*/

// attempt to let a customer borrow a movie
bool Borrow::Execute() const {
  // search for customer
  Customer *customer = store->getCustomer(customerID);
  if (customer == nullptr) {
    cout << "Borrow failed; customer " << customerID << " not found" << endl;
    return false;
  }
  // search for movie
  Movie *movie = store->findInInventory(code, sorters);
  if (movie == nullptr) {
    cout << "Borrow failed; movie with info : " << code << ", ("
         << sorters.first << ", " << sorters.second << ") not found" << endl;
    return false;
  }

  // make sure it's in stock
  if (!(movie->tryBorrow())) {
    // cout << "Borrow failed; movie out of stock" << endl;
    // Witch Wicked could NOT borrow Harold and Maude, out of stock:
    cout << customer->shareName() << " could NOT borrow " << sorters.first
         << " " << sorters.second << ", out of stock!" << endl;
    return false;
  }

  // give movie to customer
  customer->borrowMovie(movie);

  return true;
}

// register Borrow as a type
BorrowFactory::BorrowFactory(Store *s) : CommandFactory(s) {
  registerType('B', this);
  store = s;
}

// create a new Borrow command
Command *BorrowFactory::makeCommand(const string &line, Store *s) const {

  // cout << "[Borrow make-command] reading line " << line << endl;
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
  return new Borrow(s, code, id, sorters);
}

// create object register at runtime
// extern unique_ptr<Store>
//     globalStore; // Ensure globalStore is declared somewhere
BorrowFactory anonymousBorrowFactory(globalStore.get());