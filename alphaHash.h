#ifndef ALPHA_HASH
#define ALPHA_HASH

#include <iostream>
#include <memory>
#include <unordered_set>
#include <utility> // For std::pair
#include <vector>
using namespace std;
template <typename T> class AlphaHash {
public:
  // constructor
  AlphaHash() { hashTable.assign(tableSize, {'#', T{}}); }

  // insert a key into the table.
  // return false if key is already inside.
  bool insert(const char &key, const T &value);

  // returns true if key is in the table
  bool containsKey(const char &key) const;

  // return the value with key
  T &at(const char &key);

  const unordered_set<char> &getKeys() const;

  // attempt to remove a key-value pair, replacing it with a '#' for key and
  // blank T for value
  bool removeKey(const char &key);
  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, AlphaHash<U> table);

private:
  static size_t tableSize;
  static char blank;

  // keys are characters
  vector<pair<char, T>> hashTable;

  // return an index for the key to go to
  int hash(const char &key);

  unordered_set<char> keys;
};

#include "alphaHash.h"
#include <ostream>

// template <typename T> const vector<pair<char, T>> &AlphaHash<T>::table()
// const {
//   return hashTable;
// }
template <typename T> size_t AlphaHash<T>::tableSize = 26;

template <typename T> char AlphaHash<T>::blank = '#';

// insert a key-value pair
template <typename T>
bool AlphaHash<T>::insert(const char &key, const T &value) {
  // cout << "[Alphahash] attempting to insert " << key << endl;
  if (containsKey(key)) {
    cout << "[Alphahash] insert failed; key " << key
         << " is already in the table!" << endl;
    return false;
  }
  int index = hash(key);
  // cout << "\t[AlphaHash] key at index " << index << ": "
  //      << hashTable[index].first << endl;

  if (hashTable[index].first != blank) {
    // cout << "[Alphahash] insert failed; index " << index
    //      << " already occupied by " << hashTable[index] << endl;
    return false;
  }
  hashTable[index] = make_pair(key, value);
  keys.insert(key);
  // cout << "[Alphahash] inserting " << key << " and " << value << "!" << endl;
  // cout << *this << endl;
  return true;
}

// remove a key-value pair
// replace they key with '#' and value with T()
template <typename T> bool AlphaHash<T>::removeKey(const char &key) {
  int index = hash(key);
  if (hashTable[index].first == key) {
    hashTable[index] = make_pair(blank, T());
    keys.erase(key);
    return true;
  }
  return false;
}

// return set of keys
template <typename T> const unordered_set<char> &AlphaHash<T>::getKeys() const {
  return keys;
}

// return true if key is somewhere in the table
template <typename T> bool AlphaHash<T>::containsKey(const char &key) const {
  return keys.find(key) != keys.end();
}

// return value in a key-value pair
template <typename T> T &AlphaHash<T>::at(const char &key) {

  int index = hash(key);
  return hashTable[index].second;
}

// return index of where the key is/ should go
template <typename T> int AlphaHash<T>::hash(const char &key) {
  return key % tableSize;
}

// print key-value pairs
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::pair<char, T> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

// operator<< overload
template <typename U>
ostream &operator<<(ostream &os, const AlphaHash<U> table) {
  for (int i = 0; i < AlphaHash<U>::tableSize; i++) {
    if (table.hashTable[i].first != table.blank) {
      os << table.hashTable[i].first << ": " << table.hashTable[i].second
         << "\n";
    }
  }
  return os;
}
#endif