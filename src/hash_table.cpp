#include "hash_table.h"



size_t HashTable::getSize() const {
    return m_size;
}

HashTable::HashTable() : m_size(53), m_count(0), m_items(m_size) {}

HashTable::~HashTable() {}

size_t HashTable::hashOne(const string& s) const {
    long long hashIndex = 0;
    size_t n = s.length();
    for(size_t i = 0; i < n; i++) {
        hashIndex = (hashIndex * primeOne + s[i]) % m_size;
    }
    return static_cast<size_t>(hashIndex);
}

size_t HashTable::hashTwo(const string& s) const {
    long long hashIndex = 0;
    size_t n = s.length();
    for(size_t i = 0; i < n; i++) {
        hashIndex = (hashIndex * primeTwo + s[i]) % m_size;
    }

    return static_cast<size_t>(primeTwo - (hashIndex % primeTwo));
}

string* HashTable::search(const string& key) const {
    size_t initialIndex = hashOne(key);
    size_t stepSize = hashTwo(key);

    for(size_t i = 0; i < m_size; i++) {
        size_t currIndex = (initialIndex + i * stepSize) % m_size;

        if(m_items[currIndex] == nullptr) { //case 1: null
            return nullptr;
        } else if (m_items[currIndex]->deleted) { //case 2: tombstone
            continue;
        } else if (m_items[currIndex]->key == key) {
            string* res = &(m_items[currIndex]->value);
            return res;
        }
    }
    return nullptr;
}

void HashTable::insert(const string& key, const string& value) {
    size_t initialIndex = hashOne(key);
    size_t stepSize = hashTwo(key);

    size_t firstDeletedIndex = m_size;

    for(size_t i = 0; i < m_size; i++) {
        size_t currIndex = (initialIndex + i * stepSize) % m_size;

        if(m_items[currIndex] == nullptr) {
            size_t insertIndex = (firstDeletedIndex != m_size) ? firstDeletedIndex : currIndex;
            m_items[insertIndex] = make_unique<Item>(key, value);
            m_count++;
            return;
        } else if (m_items[currIndex]->key == key) {
            m_items[currIndex]->value = value;
            return;
        } else if (m_items[currIndex]->deleted) { //tombstone
            if(firstDeletedIndex == m_size) {
                firstDeletedIndex = currIndex;
            }
        }
    }

    if(firstDeletedIndex != m_size) {
        m_items[firstDeletedIndex] = make_unique<Item>(key, value);
        m_count++;
        //essentially the same as unique_ptr<Item> = unique_ptr<Item>(new Item(key, value));
        return;
    }

    std::cerr << "HT is full or cannot find a suitable spot for " << key << "." << "\n";
}

void HashTable::remove(const string& key) {
    size_t initialIndex = hashOne(key);
    size_t stepSize = hashTwo(key);

    for(size_t i = 0; i < m_size; i++) {
        size_t currIndex = (initialIndex + i * stepSize) % m_size;

        if(m_items[currIndex] == nullptr) {
            cerr << "Key not found (nullptr) \n";
            return;
        } else if (m_items[currIndex]->deleted) {
            continue;
        } else if (m_items[currIndex]->key == key) {
            m_items[currIndex]->deleted = true;
            m_count--;
            return;
        }
    }

    cerr << "Key not found" << "\n";
    return;
}





