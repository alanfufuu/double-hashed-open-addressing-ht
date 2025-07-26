#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

class Item {
    public:
    string key;
    string value;

    Item(const string& k, const string& v) : key(k), value(v) {}

    Item(const string& k) : Item(k, "") {}

    Item() : Item("", "") {}

};

class HashTable {
    public:
    unique_ptr<vector<Item>> items;

    size_t getSize() {
        return (*items).size();
    }
    bool count(const string& key);{
        auto pt = find((*items).begin(), (*items).end(), key);
        return (pt != (*items).end());
    }
    string* search(const string& key);
    void insert(const string& key, const string& value);
    void remove(const string& key);

    HashTable();
    ~HashTable();

    private:
    size_t hash(const string& s, const int& num_buckets) {
        long long hashIndex = 0;
        int n = s.length();
        for(size_t i = 0; i < n; i++) {
            hashIndex = (hashIndex * 151 + s[i]) % num_buckets;
        }
        return static_cast<size_t>(hashIndex);
    }
    
};










int main() {

    return 0;
}

