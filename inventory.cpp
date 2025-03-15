#include "inventory.h"
#include "store.h"
using namespace std;

/*
  Represents a query to access the inventory of a Store object
*/

// access data from inventory and displays it
// map<char, vector<Movie *>, greater<char>> inventory;
bool Inventory::Execute() const {
  cout << "=====================================" << endl;
  cout << "[Inventory] Displaying Inventory!" << endl;
  if (store == nullptr) {
    cout << "[Inventory] no reference to store!" << endl;
    return false;
  }
  for (const auto &group : store->getInventory()) {
    // cout << group.first << endl;
    for (const Movie *movie : group.second) {
      cout << *movie << endl;
      pair<string, string> sorters = movie->getSorters();
      // /cout << "\t(" << sorters.first << ", " << sorters.second << ")" <<
      // endl;
    }
  }
  cout << "[Inventory] Done displaying Inventory!" << endl;
  cout << "=====================================" << endl;
  return true;
}

// register Inventory as a type
InventoryFactory::InventoryFactory(Store *s) : CommandFactory(s) {
  registerType('I', this);
  store = s;
}

// create a new Inventory command
Command *InventoryFactory::makeCommand(const string &line, Store *s) const {
  string l = line;
  return new Inventory(s);
}

// create object register at runtime
// extern unique_ptr<Store>
//     globalStore; // Ensure globalStore is declared somewhere
InventoryFactory anonymousInventoryFactory(globalStore.get());