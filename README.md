# Double Hashing Hash Table
This project implements a hash table using a technique called double hashing for collision resolution. The hash table stores key-value pairs where both the key and the value are strings.

# Key Features
## Double Hashing: 
This method uses two different hash functions to determine the probing sequence for an item in the hash table. This helps to distribute data more evenly and prevent clustering, which is a common issue with linear probing.

## Dynamic Resizing: 
The hash table automatically resizes itself to maintain optimal performance. It grows when the load factor (the ratio of items to the table size) exceeds a certain threshold (0.7) and shrinks when it falls below another (0.2), as long as it stays above a minimum size.

## Tombstones: 
To handle deletions efficiently, the implementation uses "tombstones" (marked items as deleted). This is crucial for maintaining the integrity of the probing sequence in an open-addressing hash table.

## Error Handling: 
The implementation includes robust error handling, throwing exceptions for invalid keys, memory allocation failures, or when a key is not found during a removal operation.

## Prime Sized Table: 
The hash table size is always a prime number. This is a best practice for hashing as it helps to ensure a uniform distribution of keys and avoids issues with common divisors.
