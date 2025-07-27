#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
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
    vector<unique_ptr<Item>> m_items;

    size_t getSize() const; //

    bool count(const string& key); //

    string* search(const string& key) const ;

    void insert(const string& key, const string& value);

    void remove(const string& key);

    HashTable();
    ~HashTable();

    private:
    size_t m_size;
    size_t m_count;
    int primeOne = 151;
    int primeTwo = 47;

    size_t hashOne(const string& s) const; //

    size_t hashTwo(const string& s) const; //
    
};






