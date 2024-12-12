#include "InMemoryDB.h"
#include <stdexcept>
void InMemoryDB::begin_transaction() {
    if (inTransaction) {
        throw runtime_error("Transaction already in progress");
    }
    inTransaction = true;
    transactionState.clear();
}

void InMemoryDB::commit() {
    if (!inTransaction) {
        throw runtime_error("No ongoing transaction to commit");
    }
    
    unordered_map<string, int>::iterator iter = transactionState.begin();
    for (; iter != transactionState.end(); ++iter) 
        mainState[iter->first] = iter->second;
    
    transactionState.clear();
    inTransaction = false;
}

void InMemoryDB::rollback() {
    if (!inTransaction) {
        throw runtime_error("No ongoing transaction to rollback");
    }
    transactionState.clear();
    inTransaction = false;
}

void InMemoryDB::put(const string& key, int value) {
    if (!inTransaction) {
        throw runtime_error("Transaction not in progress");
    }
    transactionState[key] = value;
}

optional<int> InMemoryDB::get(const string& key) {
    if (mainState.find(key) == mainState.end())
        return nullopt;
        
    return mainState[key];
}

