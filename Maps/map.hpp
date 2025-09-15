#include<iostream>
using namespace std;
// Maps use Binary-Search trees to store elements in cpp
template<typename K, typename V>
class Map{
private:
    typedef struct Node{
        K key;
        V value;
        Node *left;
        Node *right;
        Node(K k, V v): key(k),value(v),left(NULL),right(NULL){}
    };
    
    Node *insert(Node *root,K key,V value){
        if(!root) return NULL;
        if(key < root->key){
            root->left = insert(root->left,key,value);
        }else if(key > root->key){
            root->right = insert(root->right,key,value);
        }else{
            root->value = value;
        }
        return root;
    }
    
    Node *find(Node *root, K key){
        if(!root) return NULL;
        if(key==root->key) return root;
        if(key < root->key) return find(root->left,key);
        return find(root->right,key);
    }
public:
    Map() : root(NULL) {}
    void insert(K key, V value){ root = insert(key,value); }
    V get(K key){
        Node *node = find(root,key){
            if(node) return node->value;
            throw runtime_error("Not found");
        }
    }
};