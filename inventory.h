#ifndef INVENTORY
#define INVENTORY
#include "command.h"

class Store;

class Inventory : public Command {
public:
  explicit Inventory(Store *s) : Command(s) {}

  bool Execute() const override;
  static string genreName;
};

class InventoryFactory : public CommandFactory {
public:
  explicit InventoryFactory(Store *s);
  Command *makeCommand(const string &line, Store *s) const override;
};

string Inventory::genreName = "Inventory";
#endif