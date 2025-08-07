#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <limits>
using namespace std;

class Item {
    public:
    string key;
    string value;
    bool deleted;

    Item(const string& k, const string& v) : key(k), value(v), deleted(false) {}
    Item(const string& k) : Item(k, "") {}
    Item() : Item("", "") {}

};

class HashTable {
    public:
    size_t getSize() const noexcept; //
    bool count(const string& key) const; //
    string* search(const string& key) const;
    void insert(const string& key, const string& value);
    void remove(const string& key);
    double getLoadFactor() const noexcept; 
    bool isValidKey(const string& key) const noexcept;

    HashTable();
    ~HashTable() noexcept;

    private:
    const size_t minimumSize = 53;
    size_t m_size;
    size_t m_count;
    vector<unique_ptr<Item>> m_items;
    const size_t primeOne = 151;
    const size_t primeTwo = 47;

    size_t hashOne(const string& s) const noexcept; //
    size_t hashTwo(const string& s) const noexcept; //

    void resizeTable(size_t newSize);
    bool isPrime(size_t n) const noexcept;
    size_t nextPrime(size_t currSize) const;
    
};






