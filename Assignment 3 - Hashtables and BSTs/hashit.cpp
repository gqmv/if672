/**
 * Except where otherwise noted, the following code is licensed under the Creative Commons Attribution 4.0 International license (CC BY 4.0):
 * http://creativecommons.org/licenses/by/4.0/
 * Copyright 2021 Gabriel Vieira
 * https://github.com/gqmv
 *
 * Whenever using, citing, or modifying this work, be sure to include a copy of the license and this notice.
 */

#include <bits/stdc++.h>
#include <sstream>

using namespace std;

/**
 * A fixed-size HashTable for storing strings. Uses open addressing to resolve collisions.
 */
class HashTable
{
private:
    struct Node
    {
        string key;

        Node(string key)
        {
            this->key = key;
        }
    };

    /**
     * Calculates the index at which a key should be stored.
     *
     * @param key The key to be hashed.
     * @param attempt The current attempt at hashing the key.
     * @return The index at which the key should be stored.
     */
    int calculate_index(string key, int attempt)
    {
        int hash_val = hash(key);
        int index = (hash_val + (attempt * attempt) + (23 * attempt)) % this->capacity;
        return index;
    }

    /**
     * Hashes a string.
     *
     * @param key The string to be hashed.
     * @return The hash value of the string.
     */
    int hash(string key)
    {
        long long int hash = 0;
        for (int i = 0; i < key.length(); i++)
        {
            hash = hash + (key[i] * (i + 1));
        }

        hash = (19 * hash) % this->capacity;

        return hash;
    }

    int size;
    Node **table;
    int capacity;

public:
    HashTable(int capacity)
    {
        this->capacity = capacity;
        this->size = 0;
        this->table = new Node *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            this->table[i] = nullptr;
        }
    }

    /**
     * Gets the number of elements in the HashTable.
     *
     * @return The number of elements in the HashTable.
     */
    int getSize()
    {
        return this->size;
    }

    /**
     * Finds a key in the HashTable.
     *
     * @param key The key to be found.
     * @return The index at which the key is stored, or -1 if the key is not found.
     */
    int find(string key)
    {
        for (int attempt = 0; attempt < 20; attempt++)
        {
            int index = calculate_index(key, attempt);

            if (this->table[index] != nullptr && this->table[index]->key == key)
            {
                return index;
            }
        }
        return -1;
    }

    /**
     * Inserts a key into the HashTable.
     *
     * @param key The key to be inserted.
     */
    void insert(string key)
    {
        if (find(key) != -1)
        {
            return;
        }

        for (int attempt = 0; attempt < 20; attempt++)
        {
            int index = calculate_index(key, attempt);

            if (this->table[index] == nullptr)
            {
                this->table[index] = new Node(key);
                this->size++;
                return;
            }
        }
    }

    /**
     * Removes a key from the HashTable.
     *
     * @param key The key to be removed.
     */
    void deleteKey(string key)
    {
        int index = this->find(key);

        if (index == -1)
        {
            return;
        }

        delete this->table[index];
        this->table[index] = nullptr;
        this->size--;
    }

    /**
     * Gets the HashTable in a human-readable format.
     *
     * @return A string representation of the HashTable.
     */
    string getStringRepresentation()
    {
        string result = "";
        for (int i = 0; i < this->capacity; i++)
        {
            if (this->table[i] != nullptr)
            {
                result += to_string(i) + ":" + this->table[i]->key + "\n";
            }
        }

        // Since a string representation should never end in a newline, we remode the last newline.
        return result.substr(0, result.length() - 1);
    }
};

int main()
{
    const int hashTableCapacity = 101;

    // This portion of code disables io sync, allowing the streams to buffer independently and consequently increasing performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test_cases;
    cin >> test_cases;

    for (int i = 0; i < test_cases; i++)
    {
        int operations_count;
        cin >> operations_count;

        HashTable hash_table = HashTable(hashTableCapacity);

        // Clear the buffer to avoid problems with the next input.
        cin.ignore();

        for (int j = 0; j < operations_count; j++)
        {
            // The command string houses the entire command, (eg. "ADD:test")
            string command;
            getline(cin, command);
            
            string operation;
            string key;
            stringstream ss(command);

            // The operation string houses the first word of the command (eg. "ADD")
            getline(ss, operation, ':');

            // The key string houses the second word of the command (eg. "test")
            getline(ss, key);

            if (operation == "ADD")
            {
                hash_table.insert(key);
            }
            else if (operation == "DEL")
            {
                hash_table.deleteKey(key);
            }
        }

        cout << hash_table.getSize() << endl;
        cout << hash_table.getStringRepresentation() << endl;
    }
}
