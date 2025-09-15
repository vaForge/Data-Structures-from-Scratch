#include<iostream>
#include "Maps/map.hpp"

int main(){
    Map<string,int> mp;
    Map<int,int> mp2;
    mp.insert("A",10);
    mp.insert("B",20);
    mp.insert("C",30);
    mp.insert("D",40);
    mp.insert("E",50);
    mp2.insert(1,1);
    mp2.insert(2,1);
    mp2.insert(3,2);
    mp2.insert(4,5);
    mp2.insert(5,6);
    cout<<"Value at 'B' "<<mp.get("B")<<endl;
    cout<<"Value at 'E'"<<mp.get("E")<<endl;
    mp.erase("E");
    try{
        cout<<"Value at 'E'"<<mp.get("E")<<endl;
    }catch( exception &e){
        cout<<"Not found\n";
    }
    cout<<"Value at 2 and 4 :"<<mp2.get(2)<<" "<<mp2.get(4)<<endl;
    mp2.erase(2);
    try{
        cout<<"Value at '2'"<<mp2.get(2)<<endl;
    }catch( exception &e){
        cout<<"Not found\n";
    }
    return 0;
}