#ifndef HISTORY
#define HISTORY
#include "command.h"

class Store;

class History : public Command {
public:
  explicit History(Store *s, int id) : Command(s), customerID(id) {}

  bool Execute() const override;
  static string genreName;

private:
  int customerID;
};

class HistoryFactory : public CommandFactory {
public:
  explicit HistoryFactory(Store *s);
  Command *makeCommand(const string &line, Store *s) const override;
};

string History::genreName = "History";
#endif