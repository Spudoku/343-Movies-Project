#include "store.h"
#include "lineProcessor.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>

#include <sstream>
#include <string>
using namespace std;

// unique pointer. AAAAAAHHH
unique_ptr<Store> globalStore(new Store());

// runs 3 files when instantiated
Store::Store(const string &customers, const string &movies,
             const string &commands) {

  readCustomersFromFile(customers);
  buildInventoryFromFile(movies);
  runFile(commands);
}

// deallocate dynamic memory
Store::~Store() {

  // clear inventory
  for (auto &group : inventory) {
    // cout << group.first << endl;
    for (int i = 0; i < group.second.size(); i++) {
      Movie *old = group.second[i];
      group.second[i] = nullptr;
      delete old;
    }
  }

  // clear customers

  // unordered_map<int, Customer *> customers;
  for (auto &pair : customers) {
    Customer *old = pair.second;
    pair.second = nullptr;

    delete old;
  }

  while (!runList.empty()) {
    Command *cmd = runList.front();
    delete cmd; // Ensure cleanup
    runList.pop();
  }
}

// add customers based on a file
bool Store::readCustomersFromFile(const string &fileName) {
  ifstream fs(fileName);
  string line;
  if (fs.is_open()) {
    while (getline(fs, line)) {
      if (line.empty()) {
        std::cerr << "Warning: Empty line in file!" << std::endl;
        continue; // Prevents accessing line[0] if empty
      }
      // format: 3333 Witch Wicked
      vector<string> vs = LineProcessor::splitString(line, ' ');
      int id = stoi(vs[0]);
      string name = vs[1] + " " + vs[2];
      // cout << "[Customer] created customer with " << id << ", " << name <<
      // endl;

      AddCustomer(id, new Customer(id, name));
    }
    return true;
  }
  return false;
}

// add movies based on a text file
bool Store::buildInventoryFromFile(const string &fileName) {
  // for each line in the file, try to build a movie

  ifstream fs(fileName);
  string line;
  if (fs.is_open()) {

    // iterate over each line
    while (getline(fs, line)) {
      if (line.empty()) {
        std::cerr << "Warning: Empty line in file!" << std::endl;
        continue; // Prevents accessing line[0] if empty
      }
      // get vector of strings from the line
      // cout << "[Inventory Build] extracting line: " << line << endl;
      vector<string> vs = LineProcessor::splitString(line);
      // cout << "[Inventory Build] extracted line: ";
      // for (const string &item : vs) {
      //   // cout << item << ", ";
      // }
      // cout << endl;
      char command = vs[0][0];

      // try to create a new movie
      Movie *newMovie = MovieFactory::create(command, line);

      // failure case
      if (newMovie == nullptr) {
        // cout << "; build failed";
      } else {
        // cout << "; build succeeded";

        AddMovie(newMovie->getGenreCode(), newMovie);
      }
      // cout << endl;
    }
    return true;
  }
  return false;
}

// build and run a queue of Command objects
bool Store::runFile(const string &fileName) {

  ifstream fs(fileName);
  string line;
  if (fs.is_open()) {
    while (getline(fs, line)) {
      Command *newCommand = CommandFactory::create(line[0], line, this);
      if (newCommand != nullptr) {
        runList.push(newCommand);
      }
    }
    cout << "[Store-Runfile] DEBUG: there are " << runList.size()
         << " commands to execute " << endl;
    // iterate over all commands in queue
    while (!runList.empty()) {
      Command *cur = runList.front();

      cur->Execute();
      runList.pop();
      delete cur;
    }
    return true;
  }
  return false;
}

// insert a movie into the correct position in inventory
void Store::AddMovie(char genre, Movie *movie) {
  if (inventory.find(genre) == inventory.end()) {
    // create new vector
    inventory.emplace(genre, vector<Movie *>{});
  }
  inventory.at(genre).push_back(movie);

  // call sorting algorithm
  vector<Movie *> &list = inventory.at(genre);
  // cout << "Sorting set of movies at " << genre << "!" << endl;

  // sort has to dereference the pointers of movies
  sort(list.begin(), list.end(), [](Movie *a, Movie *b) { return *a < *b; });
}

// getter for inventory
const map<char, vector<Movie *>, greater<char>> &Store::getInventory() const {
  return inventory;
}

// adds a customer to customer map
void Store::AddCustomer(int id, Customer *customer) {

  customers.emplace(id, customer);
}

// return pointer to customer object,
// or nullptr if not found
Customer *Store::getCustomer(int id) {
  return customers.find(id) != customers.end() ? customers.at(id) : nullptr;
}

Movie *Store::findInInventory(char code, pair<string, string> sorters) const {
  if (inventory.find(code) == inventory.end()) {
    return nullptr;
  }
  vector<Movie *> set = inventory.at(code);
  // linear search I guess
  for (Movie *movie : set) {
    if (movie->getSorters() == sorters) {
      return movie;
    }
  }
  return nullptr;
}