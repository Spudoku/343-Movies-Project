/**
 * Testing ass4 movie store functions
 *
 * @author Yusuf Pisan
 * @date 19 Jan 2019
 */

#include "alphaHash.h"
#include "store.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
using namespace std;

void testStore1() {
  cout << "=====================================" << endl;
  cout << "Start testStore1" << endl;

  // attempt to run the file "testcommands-1.txt"
  cout << "[TestStore1] testing with data4singlecomedy.txt" << endl;
  Store s;
  s.buildInventoryFromFile("data4singlecomedy.txt");
  // s.runFile("testcommands-1.txt");
  // s.printInventory();
  cout << endl;
  cout << "[TestStore1] testing with data4comedytest.txt" << endl;
  Store b;
  b.buildInventoryFromFile("data4comedytest.txt");
  cout << "[TestStore1] built inventory without issues" << endl;
  // b.printInventory();

  MovieFactory::printValidGenres();
  cout << "[TestStore1] testing command printing" << endl;
  CommandFactory::printValidCommands();

  b.runFile("data4simplecommands.txt");

  cout << "End testStore1" << endl;
  cout << "=====================================" << endl;
}

void testStore2() {
  cout << "=====================================" << endl;
  cout << "Start testStore2" << endl;

  Store s;
  s.buildInventoryFromFile("data4singlecomedy.txt");
  s.runFile("data4simplecommands.txt");

  Store b;
  b.buildInventoryFromFile("data4fewcomedy.txt");
  b.runFile("data4simplecommands.txt");

  Store c;
  c.buildInventoryFromFile("data4movies.txt");
  c.runFile("data4simplecommands.txt");
  cout << "End testStore2" << endl;
  cout << "=====================================" << endl;
}

void testStoreBorrow() {
  cout << "=====================================" << endl;
  cout << "Start testStoreBorrow" << endl;

  Store s("data4customers.txt", "data4movies.txt", "basicborrow.txt");
  // s.buildInventoryFromFile("data4movies.txt");
  // s.runFile("basicborrow.txt");
  cout << "End testStoreBorrow" << endl;
  cout << "=====================================" << endl;
}

void testStoreFinal() {
  cout << "=====================================" << endl;
  cout << "Start testStoreFinal" << endl;

  Store s("data4customers.txt", "data4movies.txt", "data4commands.txt");
  cout << "End testStoreFinal" << endl;
  cout << "=====================================" << endl;
}

void hashTableTest() {
  cout << "=====================================" << endl;
  cout << "Start AlphaHashTest" << endl;
  AlphaHash<int> test;
  test.insert('A', 1000);
  test.insert('C', 1100);
  test.insert('D', 13);
  test.insert('Z', 9990);
  cout << test << endl;
  test.removeKey('D');
  cout << test << endl;
  cout << "Keys in test table " << endl;
  for (char key : test.getKeys()) {
    cout << "\t" << key << endl;
  }
  cout << "End AlphaHashTest" << endl;
  cout << "=====================================" << endl;
}

void testAll() {
  // testStore1();
  //  testStore2();
  // testStoreBorrow();
  testStoreFinal();
  // hashTableTest();
}
