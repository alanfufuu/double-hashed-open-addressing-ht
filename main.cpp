#include "hash_table.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

//AI GENERATED TESTCASES

int main() {
    HashTable ht;

    // Test insert and search
    for (int i = 0; i < 100; ++i) {
        ht.insert("key" + to_string(i), "value" + to_string(i));
    }

    cout << "After 100 inserts: size = " << ht.getSize() 
         << ", load factor = " << ht.getLoadFactor() << endl;

    // Confirm all items are searchable
    for (int i = 0; i < 100; ++i) {
        string key = "key" + to_string(i);
        string* val = ht.search(key);
        assert(val != nullptr);
        assert(*val == "value" + to_string(i));
    }

    // Trigger deletions to test resize down
    for (int i = 0; i < 90; ++i) {
        ht.remove("key" + to_string(i));
    }

    cout << "After deleting 90 items: size = " << ht.getSize()
         << ", load factor = " << ht.getLoadFactor() << endl;

    // Confirm remaining items are still there
    for (int i = 90; i < 100; ++i) {
        string key = "key" + to_string(i);
        string* val = ht.search(key);
        assert(val != nullptr);
        assert(*val == "value" + to_string(i));
    }

    // Check deleted items are gone
    for (int i = 0; i < 90; ++i) {
        string key = "key" + to_string(i);
        string* val = ht.search(key);
        assert(val == nullptr);
    }

    // Insert again to test tombstone reuse
    for (int i = 0; i < 30; ++i) {
        ht.insert("key" + to_string(i), "newVal" + to_string(i));
    }

    cout << "After reinserting 30 keys: size = " << ht.getSize()
         << ", load factor = " << ht.getLoadFactor() << endl;

    // Check inserted values
    for (int i = 0; i < 30; ++i) {
        string key = "key" + to_string(i);
        string* val = ht.search(key);
        assert(val != nullptr);
        assert(*val == "newVal" + to_string(i));
    }

    cout << "\n✅ All tests passed successfully!\n";

    return 0;
}