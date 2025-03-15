#ifndef COMMAND
#define COMMAND

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
  Abstract Command class
*/

// forward declaration
class Store;
class Command;

// Abstact MovieFactory; each subclass of Movie represents a genre
class CommandFactory {
public:
  explicit CommandFactory(Store *s) { store = s; }
  // attempt to create a new command
  virtual Command *makeCommand(const string &line, Store *s) const = 0;

  //   // find movie factory and make the object
  static Command *create(char type, const string &line, Store *s);

  //   // print all character codes for genres
  static void printValidCommands();

protected:
  // register a factory with given name
  static void registerType(const char &type, CommandFactory *factory);
  Store *store;

private:
  // stores all command factories
  static map<char, CommandFactory *> &getMap();
};

/*
  Abstract Command class
*/

class Command {
public:
  explicit Command(Store *s);
  virtual ~Command() = default;

  // perform the command

  virtual bool Execute() const = 0;
  char getCommandCode() const { return commandCode; }

protected:
  string name;

  char commandCode;

  Store *store;
};
#endif