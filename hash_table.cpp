#include "hash_table.h"



size_t HashTable::getSize() const noexcept{
    return m_size;
}

HashTable::HashTable() : m_size(53), m_count(0), m_items(m_size) {}

HashTable::~HashTable() noexcept {}

size_t HashTable::hashOne(const string& s) const noexcept {
    long long hashIndex = 0;
    size_t n = s.length();
    for(size_t i = 0; i < n; i++) {
        hashIndex = (hashIndex * primeOne + static_cast<unsigned char>(s[i])) % m_size;
    }
    return static_cast<size_t>(hashIndex);
}

size_t HashTable::hashTwo(const string& s) const noexcept {
    long long hashIndex = 0;
    size_t n = s.length();
    for(size_t i = 0; i < n; i++) {
        hashIndex = (hashIndex * primeTwo + static_cast<unsigned char>(s[i])) % m_size;
    }

    size_t safePrime = (m_size < primeTwo) ? 7 : primeTwo;
    size_t step = static_cast<size_t>(safePrime - (hashIndex % safePrime));
    return step == 0 ? 1 : step; //step can be zero?
}

bool HashTable::isValidKey(const string& key) const noexcept{
    return !key.empty() && key.length() < 10000;
}

string* HashTable::search(const string& key) const {
    if(!isValidKey(key)){
        throw invalid_argument("Invalid Key");
    }
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

bool HashTable::count(const string& key) const {
    try {
        return search(key) != nullptr;
    } catch (...){
        return false;
    }
}

void HashTable::insert(const string& key, const string& value) {
    if(!isValidKey(key)){
        throw invalid_argument("Invalid Key");
    }

    size_t initialIndex = hashOne(key);
    size_t stepSize = hashTwo(key);

    size_t firstDeletedIndex = m_size;

    for(size_t i = 0; i < m_size; i++) {
        size_t currIndex = (initialIndex + i * stepSize) % m_size;
        if(currIndex >= m_items.size()){
            throw runtime_error("Index out of bounds during insertion");
        }

        if(m_items[currIndex] == nullptr) {
            size_t insertIndex = (firstDeletedIndex != m_size) ? firstDeletedIndex : currIndex;
            try {
                m_items[insertIndex] = make_unique<Item>(key, value);
            } catch (std::bad_alloc&){
                throw runtime_error("Memory allocation failed during insert");
            }
            m_count++;
            if(getLoadFactor() > 0.7){
                resizeTable(nextPrime(m_size * 2));
            }
            return;
        } else if (m_items[currIndex]->key == key && !m_items[currIndex]->deleted) {
            m_items[currIndex]->value = value;
            return;
        } else if (m_items[currIndex]->deleted) { //tombstone
            if(firstDeletedIndex == m_size) {
                firstDeletedIndex = currIndex;
            }
        }
    }

    if(firstDeletedIndex != m_size) {
        try {
            m_items[firstDeletedIndex] = make_unique<Item>(key, value);
        } catch(...) {
            throw runtime_error("Memory allocation failed during insert");
        }
        m_count++;
        if(getLoadFactor() > 0.7) {
            resizeTable(nextPrime(m_size * 2));
        }
        //essentially the same as unique_ptr<Item> = unique_ptr<Item>(new Item(key, value));
        return;
    }

    throw runtime_error("HT is full or cannot find a suitable spot for " + key + ".\n");
}

void HashTable::remove(const string& key) {
    if(!isValidKey(key)){
        throw invalid_argument("Invalid Key");
    }

    size_t initialIndex = hashOne(key);
    size_t stepSize = hashTwo(key);

    for(size_t i = 0; i < m_size; i++) {
        size_t currIndex = (initialIndex + i * stepSize) % m_size;

        if(m_items[currIndex] == nullptr) {
            throw runtime_error("Key not found: " + key);
        } else if (m_items[currIndex]->deleted) {
            continue;
        } else if (m_items[currIndex]->key == key) {
            m_items[currIndex]->deleted = true;
            m_count--;
            if(getLoadFactor() < 0.2 && m_size > minimumSize * 2) {
                resizeTable(nextPrime(m_size / 2));
            }
            return;
        }
    }
}

double HashTable::getLoadFactor() const noexcept {
    if(m_size == 0) return 0.0;
    return static_cast<double>(m_count)/m_size;
}

size_t HashTable::nextPrime(size_t n) const {
    const size_t MAX_SIZE = numeric_limits<size_t>::max() / 2;
    while(!isPrime(n)){
        n++;
        if(n >= MAX_SIZE){
            throw runtime_error("Cannot find next prime within size limits");
        }
    }
    return n;
}

bool HashTable::isPrime(size_t n) const noexcept {
    if(n <= 1) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;

    size_t sqrtN = static_cast<size_t>(sqrt(n));
    for(size_t i = 3; i <= sqrtN; i++) {
        if(n % i == 0) return false;
    }
    return true;
}

void HashTable::resizeTable(size_t newSize){
    //copy old items into storage, make new vector of size newSize and insert each if not tombstone or deleted
    vector<unique_ptr<Item>> oldItems = std::move(m_items);
    size_t oldCount = m_count;

    m_size = newSize;
    m_count = 0;

    try {
        m_items = vector<unique_ptr<Item>>(m_size);
    } catch (const std::bad_alloc&){
        m_items = std::move(oldItems);
        m_size = oldItems.size();
        m_count = oldCount;
        throw runtime_error("Memory allocation failed during resize");
    }

    for(auto& item : oldItems){
        if(item != nullptr && !item->deleted){
            insert(item->key, item->value);
        }
    }
    cout << "Resizing table to size " << newSize << ".\n";
}




