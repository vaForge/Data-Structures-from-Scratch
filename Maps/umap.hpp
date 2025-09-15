#include<iostream>
#include<vector>
#include<list>
//Chaining for collisions
template<typename K, typename V>
class UMap{
    static size_t SIZE = 10;
    vector<list<pair<K,V>> table;
    size_t hashing(K key){
        return hash<K>()(key) % SIZE;
    }
public:
    UMap() :table(SIZE){}
    void insert(K key, V value){
        int idx = hashing(key);
        for(auto &p : table[idx]){
            if(p.first==key) { p.second = value; return;}
        }
        table[idx].push_back({key,value});
    }
    bool contains(K key){
        int idx = hashing(key);
        for(auto &p: table[idx]){
            if(p.first == key) return true;
        }
        return false;
    }
};