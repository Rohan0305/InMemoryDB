#ifndef INMEMORYDB_H
#define INMEMORYDB_H

#include <string>
#include <unordered_map>
#include <optional>

using namespace std;

class InMemoryDB {
public:

    optional<int> get(const string& key);
    void begin_transaction();
    void commit();
    void rollback();
    void put(const string& key, int value);
    bool inTransaction = false;

private:
    unordered_map<string, int> mainState; 
    unordered_map<string, int> transactionState; 
};

#endif 