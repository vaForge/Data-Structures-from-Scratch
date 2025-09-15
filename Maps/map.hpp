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
    Node *root;
    
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
    Node *findMin(Node *root){
        while(root && root->left){ root = root->left;}
        return root;
    }
    Node *erase(Node *root,K key){
        if(!root) return NULL;
        if(key < root->key){
            root->left = erase(root->left,key);
        }else if(key > root->key){
            root->right = erase(root->right,key);
        }else{
            //no children
            if(!root->left && !root->right){
                delete root;
                return NULL;
            }else if(!root->left){    //left child isn't there
                Node *temp = root->right;
                delete root;
                return temp;
            }else if(!root->right){   //right child isn't there
                Node *temp = root->left;
                delete root;
                return temp;
            }else{                    // Both children alive
                Node *next = findMin(root->right);
                root->key = next->key;
                root->value = next->value;
                root->right = erase(root->right,next->key);
            }
        }
        return root;
    }
public:
    Map() : root(NULL) {}
    void insert(K key, V value){ root = insert(key,value); }
    void erase(K key){
        root = erase(root,key);
    }
    V get(K key){
        Node *node = find(root,key);
        if(node) return node->value;
        throw runtime_error("Not found");
    }
    

};