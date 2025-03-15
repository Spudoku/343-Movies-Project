#ifndef BORROW
#define BORROW
#include "command.h"

class Store;

class Borrow : public Command {
public:
  explicit Borrow(Store *s, char code, int customerID,
                  pair<string, string> sorters)
      : Command(s) {
    this->code = code;
    this->customerID = customerID;
    this->sorters = sorters;
  }

  bool Execute() const override;
  static string genreName;

private:
  // borrow format: B CustomerID MediaType MovieType (movie sorting
  // attributes)
  // example: B 8000 D F You've Got Mail, 1998
  // B ID DVD Comedy Title, release

  // B 1000 D D Barry Levinson, Good Morning Vietnam,
  // B ID DVD Drama Director, Title

  // B 1000 D C 5 1940 Katherine Hepburn
  // B ID DVD Classic Major Actor

  // pattern:

  char code;
  int customerID;
  pair<string, string> sorters;
};

class BorrowFactory : public CommandFactory {
public:
  explicit BorrowFactory(Store *s);
  Command *makeCommand(const string &line, Store *s) const override;
};

string Borrow::genreName = "Borrow";
#endif