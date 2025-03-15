/*
    Store.h
*/
#ifndef STORE
#define STORE

#include "command.h"
#include "customer.h"
#include "movie.h"
#include <map>
#include <memory> // for std::unique_ptr
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Command;

extern std::unique_ptr<Store> globalStore;
class Store {

public:
  // default constructor
  Store() = default;
  ~Store();

  // constructor that inputs and executes 3 files:
  // one for customer data, one for movie (inventory) data, one for commands
  Store(const string &customers, const string &movies, const string &commands);

  // add customers from given file
  bool readCustomersFromFile(const string &fileName);

  // load the Inventory from a given file name
  bool buildInventoryFromFile(const string &fileName);

  // attempt to run a file (using the command format) with given name
  bool runFile(const string &fileName);

  // inventory getter
  const map<char, vector<Movie *>, greater<char>> &getInventory() const;

  // return pointer to customer object,
  // or nullptr if not found
  Customer *getCustomer(int id);

  // return pointer to a Movie object if found in inventory map, or
  // nullptr if not found
  // takes a pair of strings to compare against each movie
  Movie *findInInventory(char code, pair<string, string> sorters) const;

private:
  queue<Command *> runList; // list of Command objects to execute
  // unordered_map<int, Customer*>    // map of customer objects

  // inventory needs to count genres, number of each movie, etc

  map<char, vector<Movie *>, greater<char>> inventory;

  // inserts a Movie into inventory
  void AddMovie(char genre, Movie *movie);

  void AddCustomer(int id, Customer *customer);

  unordered_map<int, Customer *> customers;
};
#endif