#include "history.h"
#include "store.h"
#include <sstream>
using namespace std;

/*
  Represents a query to access the History of a Store object
*/

// access data from History and displays it
// format:
// History for 1000 Mouse Minnie:
// Borrow Mouse Minnie Good Morning Vietnam
// Borrow Mouse Minnie The Philadelphia Story
// Borrow Mouse Minnie Good Will Hunting
// Borrow Mouse Minnie The Philadelphia Story
// Borrow Mouse Minnie Harold and Maude
// Debug: History for 1111 Mouse Mickey
bool History::Execute() const {

  Customer *customer = store->getCustomer(customerID);
  if (customer == nullptr) {
    cout << "History failed: customer " << customerID << " not found" << endl;
    return false;
  }
  string customerName = customer->shareName();
  cout << "=====================================" << endl;
  cout << "History for " << customerID << " " << customerName << ":" << endl;

  for (const auto &pair : customer->shareHistory()) {
    stringstream outputLine;
    if (pair.first == 'B') {
      outputLine << "Borrow ";
    } else if (pair.first == 'R') {
      outputLine << "Return ";
    } else {
      outputLine << "<unknown command> ";
    }

    outputLine << customerName << " " << pair.second->getTitle();

    cout << outputLine.str() << endl;
  }
  cout << "=====================================" << endl;
  return true;
}

// register History as a type
HistoryFactory::HistoryFactory(Store *s) : CommandFactory(s) {
  registerType('H', this);
  store = s;
}

// create a new History command
Command *HistoryFactory::makeCommand(const string &line, Store *s) const {
  istringstream is(line);
  string discard;
  int id;
  is >> discard;
  is >> id;
  return new History(s, id);
}

// create object register at runtime
// extern unique_ptr<Store>
//     globalStore; // Ensure globalStore is declared somewhere
HistoryFactory anonymousHistoryFactory(globalStore.get());