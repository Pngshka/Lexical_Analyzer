#pragma once
#include "analyzer.h"

#include <list>
#include <fstream>
#include <set>
using namespace std;
ofstream ofst("C://e//output.txt");

class Node {
public:
    string Name, Type;
};

class HashTable
{
    int capacity;
    list <Node>* table;
public:

    HashTable(int V);
    void insertItem(string key, Node data);

    int checkPrime(int n)
    {
        int i;
        if (n == 1 || n == 0)
        {
            return 0;
        }
        for (i = 2; i < n / 2; i++)
        {
            if (n % i == 0)
            {
                return 0;
            }
        }
        return 1;
    }
    /*int getPrime(int n)
    {
        if (n % 2 == 0)
        {
            n++;
        }
        while (!checkPrime(n))
        {
            n += 2;
        }
        return n;
    }*/

    int hashFunction(string word)
    {
        long long key = 0;
        for (int i = 0; word[i] != '\0'; i++) {
            //key = 31 * key + word[i];
            key = key + word[i];
        }
        return (key % capacity);
    }
    void displayHash();
};
HashTable::HashTable(int c)
{
    //int size = getPrime(c);
    //this->capacity = size;
    this->capacity = c;
    table = new list <Node>[capacity];
}
void HashTable::insertItem(string key, Node data)
{
    int index = hashFunction(key);

    bool t = true;
    for (auto x : table[index]) {
        if (x.Name == data.Name) {
            t = false;
            break;
        }
    }
    if (t==true) table[index].push_back(data);
}

void HashTable::displayHash()
{
    for (int i = 0; i < capacity; i++)
    {
        if (!table[i].empty()) {
            cout << "table[" << i << "]: " << endl;
            ofst << "table[" << i << "]: " << endl;
        }
        for (auto x : table[i]) {
            cout << x.Type << " | " << x.Name << endl;
            ofst << x.Type << " | " << x.Name << endl;
        }
        if (!table[i].empty())  cout << endl;
    }
}
