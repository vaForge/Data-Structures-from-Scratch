#pragma once
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
        int height;
        Node(K k, V v): key(k),value(v),height(1),left(NULL),right(NULL){}
    };
    Node *root;

    Node *insert(Node *root,K key,V value){
        if(!root) return new Node(key,value);
        if(key < root->key){
            root->left = insert(root->left,key,value);
        }else if(key > root->key){
            root->right = insert(root->right,key,value);
        }else{
            root->value = value;
            return root;
        }
        root->height = 1 + max(getHeight(root->left),getHeight(root->right));
        int balance = getBal(root);
        if(balance > 1 && key < root->left->key){      //left left 
            return rightRotate(root);
        }
        if(balance < -1 && key > root->right->key){    // right right
            return leftRotate(root);
        }
        if(balance > 1 && key > root->left->key){      //left right
            return rotateLeftRight(root);
        }
        if(balance < -1 && key < root->right->key){    //right left
            return rotateRightLeft(root);
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
        root->height = 1 + max(getHeight(root->left),getHeight(root->right));
        int balance = getBal(root);
        if(balance > 1 && key < root->left->key){      //left left 
            return rightRotate(root);
        }
        if(balance < -1 && key > root->right->key){    // right right
            return leftRotate(root);
        }
        if(balance > 1 && key > root->left->key){      //left right
            return rotateLeftRight(root);
        }
        if(balance < -1 && key < root->right->key){    //right left
            return rotateRightLeft(root);
        }
        return root;
    }

    int getHeight(Node *node){
        return node? node->height:0;
    }
    int getBal(Node *node){
        return node? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node *rightRotate(Node *y){
        Node *x = y->left;
        Node *temp = x->right;
        x->right = y;
        y->left = temp;
        y->height = 1 + max(getHeight(y->left),getHeight(y->right));
        x->height = 1 + max(getHeight(x->left),getHeight(x->right));
        return x;
    }
    Node* leftRotate(Node* x){
        Node* y = x->right;
        Node* temp = y->left;
        y->left = x;
        x->right = temp;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }
    Node *rotateLeftRight(Node *node){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    Node *rotateRightLeft(Node *node){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
public:
    Map() : root(NULL) {}
    void insert(K key, V value){ root = insert(root,key,value); }
    void erase(K key){
        root = erase(root,key);
    }
    V get(K key){
        Node *node = find(root,key);
        if(node) return node->value;
        throw runtime_error("Not found");
    }

};