#include "command.h"
#include "store.h"
#include <map>
#include <string>

using namespace std;

// storage place for CommandFactories

map<char, CommandFactory *> &CommandFactory::getMap() {
  static map<char, CommandFactory *> commands;
  return commands;
}

Command *CommandFactory::create(char type, const string &line, Store *s) {
  if (getMap().count(type) == 0) {
    cout << "Can't create " << type << "; discarding line " << line << endl;
    return nullptr;
  }

  // newCommand;
  return getMap().at(type)->makeCommand(line, s);
}

void CommandFactory::printValidCommands() {
  cout << "List of commands: ";
  for (const auto &pair : getMap()) {
    cout << pair.first << ", ";
  }
  cout << endl;
}

Command::Command(Store *s) { store = s; }

ostream &operator<<(ostream &os, const Command &item) {
  os << item.getCommandCode();

  return os;
}

void CommandFactory::registerType(const char &type, CommandFactory *factory) {
  getMap()[type] = factory;
}
